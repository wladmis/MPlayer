/*
 * huffyuv codec for libavcodec
 *
 * Copyright (c) 2002 Michael Niedermayer <michaelni@gmx.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * see http://www.pcisys.net/~melanson/codecs/huffyuv.txt for a description of
 * the algorithm used 
 */

#include "common.h"
#include "avcodec.h"
#include "dsputil.h"

#ifndef MAX_INT64
#define MAX_INT64 9223372036854775807LL
#endif

#define VLC_BITS 11
  
typedef enum Predictor{
    LEFT= 0,
    PLANE,
    MEDIAN,
} Predictor;
 
typedef struct HYuvContext{
    AVCodecContext *avctx;
    Predictor predictor;
    GetBitContext gb;
    PutBitContext pb;
    int interlaced;
    int decorrelate;
    int bitstream_bpp;
    int version;
    int yuy2;                               //use yuy2 instead of 422P
    int bgr32;                              //use bgr32 instead of bgr24
    int width, height;
    int flags;
    int picture_number;
    int linesize[3];
    uint8_t __align8 temp[3][2500];
    uint64_t stats[3][256];
    uint8_t len[3][256];
    uint32_t bits[3][256];
    VLC vlc[3];
    uint8_t __align8 *picture[3];
    uint8_t __align8 bitstream_buffer[1024*1024*3]; //FIXME dynamic alloc or some other solution
    DSPContext dsp; 
}HYuvContext;

static inline void bswap_buf(uint32_t *dst, uint32_t *src, int w){
    int i;
    
    for(i=0; i+8<=w; i+=8){
        dst[i+0]= bswap_32(src[i+0]);
        dst[i+1]= bswap_32(src[i+1]);
        dst[i+2]= bswap_32(src[i+2]);
        dst[i+3]= bswap_32(src[i+3]);
        dst[i+4]= bswap_32(src[i+4]);
        dst[i+5]= bswap_32(src[i+5]);
        dst[i+6]= bswap_32(src[i+6]);
        dst[i+7]= bswap_32(src[i+7]);
    }
    for(;i<w; i++){
        dst[i+0]= bswap_32(src[i+0]);
    }
}

static inline int add_left_prediction(uint8_t *dst, uint8_t *src, int w, int acc){
    int i;

    for(i=0; i<w-1; i++){
        acc+= src[i];
        dst[i]= acc;
        i++;
        acc+= src[i];
        dst[i]= acc;
    }

    for(; i<w; i++){
        acc+= src[i];
        dst[i]= acc;
    }

    return acc;
}

static inline void add_median_prediction(uint8_t *dst, uint8_t *src1, uint8_t *diff, int w, int *left, int *left_top){
    int i;
    uint8_t l, lt;

    l= *left;
    lt= *left_top;

    for(i=0; i<w; i++){
        l= mid_pred(l, src1[i], (l + src1[i] - lt)&0xFF) + diff[i];
        lt= src1[i];
        dst[i]= l;
    }    

    *left= l;
    *left_top= lt;
}
//FIXME optimize
static inline void sub_median_prediction(uint8_t *dst, uint8_t *src1, uint8_t *src2, int w, int *left, int *left_top){
    int i;
    uint8_t l, lt;

    l= *left;
    lt= *left_top;

    for(i=0; i<w; i++){
        const int pred= mid_pred(l, src1[i], (l + src1[i] - lt)&0xFF);
        lt= src1[i];
        l= src2[i];
        dst[i]= l - pred;
    }    

    *left= l;
    *left_top= lt;
}


static inline void add_left_prediction_bgr32(uint8_t *dst, uint8_t *src, int w, int *red, int *green, int *blue){
    int i;
    int r,g,b;
    r= *red;
    g= *green;
    b= *blue;

    for(i=0; i<w; i++){
        b+= src[4*i+0];
        g+= src[4*i+1];
        r+= src[4*i+2];
        
        dst[4*i+0]= b;
        dst[4*i+1]= g;
        dst[4*i+2]= r;
    }

    *red= r;
    *green= g;
    *blue= b;
}

//FIXME optimize
static inline int sub_left_prediction(uint8_t *dst, uint8_t *src, int w, int left){
    int i;
    for(i=0; i<w; i++){
        const int temp= src[i];
        dst[i]= temp - left;
        left= temp;
    }
    return left;
}

static void read_len_table(uint8_t *dst, GetBitContext *gb){
    int i, val, repeat;
  
    for(i=0; i<256;){
        repeat= get_bits(gb, 3);
        val   = get_bits(gb, 5);
        if(repeat==0)
            repeat= get_bits(gb, 8);
//printf("%d %d\n", val, repeat);
        while (repeat--)
            dst[i++] = val;
    }
}

static int generate_bits_table(uint32_t *dst, uint8_t *len_table){
    int len, index;
    uint32_t bits=0;

    for(len=32; len>0; len--){
        int bit= 1<<(32-len);
        for(index=0; index<256; index++){
            if(len_table[index]==len){
                if(bits & (bit-1)){
                    fprintf(stderr, "Error generating huffman table\n");
                    return -1;
                }
                dst[index]= bits>>(32-len);
                bits+= bit;
            }
        }
    }
    return 0;
}

static void generate_len_table(uint8_t *dst, uint64_t *stats, int size){
    uint64_t counts[2*size];
    int up[2*size];
    int offset, i, next;
    
    for(offset=1; ; offset<<=1){
        for(i=0; i<size; i++){
            counts[i]= stats[i] + offset - 1;
        }
        
        for(next=size; next<size*2; next++){
            uint64_t min1, min2;
            int min1_i, min2_i;
            
            min1=min2= INT64_MAX;
            min1_i= min2_i=-1;
            
            for(i=0; i<next; i++){
                if(min2 > counts[i]){
                    if(min1 > counts[i]){
                        min2= min1;
                        min2_i= min1_i;
                        min1= counts[i];
                        min1_i= i;
                    }else{
                        min2= counts[i];
                        min2_i= i;
                    }
                }
            }
            
            if(min2==INT64_MAX) break;
            
            counts[next]= min1 + min2;
            counts[min1_i]=
            counts[min2_i]= MAX_INT64;
            up[min1_i]=
            up[min2_i]= next;
            up[next]= -1;
        }
        
        for(i=0; i<size; i++){
            int len;
            int index=i;
            
            for(len=0; up[index] != -1; len++)
                index= up[index];
                
            if(len > 32) break;
            
            dst[i]= len;
        }
        if(i==size) break;
    }
}

static int read_huffman_tables(HYuvContext *s, uint8_t *src, int length){
    GetBitContext gb;
    int i;
    
    init_get_bits(&gb, src, length);
    
    for(i=0; i<3; i++){
        read_len_table(s->len[i], &gb);
        
        if(generate_bits_table(s->bits[i], s->len[i])<0){
            return -1;
        }
#if 0
for(j=0; j<256; j++){
printf("%6X, %2d,  %3d\n", s->bits[i][j], s->len[i][j], j);
}
#endif
        init_vlc(&s->vlc[i], VLC_BITS, 256, s->len[i], 1, 1, s->bits[i], 4, 4);
    }
    
    return 0;
}

static int read_old_huffman_tables(HYuvContext *s){
#if 0    
    GetBitContext gb;
    int i;

    init_get_bits(&gb, classic_shift_luma, sizeof(classic_shift_luma));
    read_len_table(s->len[0], &gb);
    init_get_bits(&gb, classic_shift_chroma, sizeof(classic_shift_chroma));
    read_len_table(s->len[1], &gb);
    
    for(i=0; i<256; i++) s->bits[0][i] = classic_add_luma  [i];
    for(i=0; i<256; i++) s->bits[1][i] = classic_add_chroma[i];

    if(s->bitstream_bpp >= 24){
        memcpy(s->bits[1], s->bits[0], 256*sizeof(uint32_t));
        memcpy(s->len[1] , s->len [0], 256*sizeof(uint8_t));
    }
    memcpy(s->bits[2], s->bits[1], 256*sizeof(uint32_t));
    memcpy(s->len[2] , s->len [1], 256*sizeof(uint8_t));
    
    for(i=0; i<3; i++)
        init_vlc(&s->vlc[i], VLC_BITS, 256, s->len[i], 1, 1, s->bits[i], 4, 4);
    
    return 0;
#else
    fprintf(stderr, "v1 huffyuv is not supported \n");
    return -1;
#endif
}

static int decode_init(AVCodecContext *avctx)
{
    HYuvContext *s = avctx->priv_data;
    int width, height, y_size, c_size, stride;

    s->avctx= avctx;
    s->flags= avctx->flags;
        
    dsputil_init(&s->dsp, avctx->dsp_mask);
    
    width= s->width= avctx->width;
    height= s->height= avctx->height;
s->bgr32=1;
    assert(width && height);
//if(avctx->extradata)
//  printf("extradata:%X, extradata_size:%d\n", *(uint32_t*)avctx->extradata, avctx->extradata_size);
    if(avctx->extradata_size){
        if(avctx->bits_per_sample&7)
            s->version=1; // do such files exist at all?
        else
            s->version=2;
    }else
        s->version=0;
    
    if(s->version==2){
        int method;

        method= ((uint8_t*)avctx->extradata)[0];
        s->decorrelate= method&64 ? 1 : 0;
        s->predictor= method&63;
        s->bitstream_bpp= ((uint8_t*)avctx->extradata)[1];
        if(s->bitstream_bpp==0) 
            s->bitstream_bpp= avctx->bits_per_sample&~7;
            
        if(read_huffman_tables(s, ((uint8_t*)avctx->extradata)+4, avctx->extradata_size) < 0)
            return -1;
    }else{
        switch(avctx->bits_per_sample&7){
        case 1:
            s->predictor= LEFT;
            s->decorrelate= 0;
            break;
        case 2:
            s->predictor= LEFT;
            s->decorrelate= 1;
            break;
        case 3:
            s->predictor= PLANE;
            s->decorrelate= avctx->bits_per_sample >= 24;
            break;
        case 4:
            s->predictor= MEDIAN;
            s->decorrelate= 0;
            break;
        default:
            s->predictor= LEFT; //OLD
            s->decorrelate= 0;
            break;
        }
        s->bitstream_bpp= avctx->bits_per_sample & ~7;
        
        if(read_old_huffman_tables(s) < 0)
            return -1;
    }
    
    s->interlaced= height > 288;
    
    c_size= 0;
    switch(s->bitstream_bpp){
    case 12:
        avctx->pix_fmt = PIX_FMT_YUV420P;
        stride= (width+15)&~15;
        c_size= height*stride/4;
        break;
    case 16:
        if(s->yuy2){
            avctx->pix_fmt = PIX_FMT_YUV422;
            stride= (width*2+15)&~15;
        }else{
            avctx->pix_fmt = PIX_FMT_YUV422P;
            stride= (width+15)&~15;
            c_size= height*stride/2;
        }
        break;
    case 24:
    case 32:
        if(s->bgr32){
            avctx->pix_fmt = PIX_FMT_BGRA32;
            stride= (width*4+15)&~15;
        }else{
            avctx->pix_fmt = PIX_FMT_BGR24;
            stride= (width*3+15)&~15;
        }
        break;
    default:
        assert(0);
        stride=0; //gcc fix
    }
    
    y_size= height*stride;
    
    s->linesize[0]= stride;
    s->picture[0]= av_mallocz(y_size);
 
    if(c_size){
        s->picture[1]= av_mallocz(c_size);
        s->picture[2]= av_mallocz(c_size);
        s->linesize[1]= s->linesize[2]= stride/2;
        
        memset(s->picture[1], 128, c_size);
        memset(s->picture[2], 128, c_size);
    }
    
//    printf("pred:%d bpp:%d hbpp:%d il:%d\n", s->predictor, s->bitstream_bpp, avctx->bits_per_sample, s->interlaced);
    
    return 0;
}

static void store_table(HYuvContext *s, uint8_t *len){
    int i;
    int index= s->avctx->extradata_size;

    for(i=0; i<256;){
        int cur=i;
        int val= len[i];
        int repeat;
        
        for(; i<256 && len[i]==val; i++);
        
        repeat= i - cur;
        
        if(repeat>7){
            ((uint8_t*)s->avctx->extradata)[index++]= val;
            ((uint8_t*)s->avctx->extradata)[index++]= repeat;
        }else{
            ((uint8_t*)s->avctx->extradata)[index++]= val | (repeat<<5);
        }
    }
    
    s->avctx->extradata_size= index;
}

static int encode_init(AVCodecContext *avctx)
{
    HYuvContext *s = avctx->priv_data;
    int i, j, width, height;

    s->avctx= avctx;
    s->flags= avctx->flags;
        
    dsputil_init(&s->dsp, avctx->dsp_mask);
    
    width= s->width= avctx->width;
    height= s->height= avctx->height;
    
    assert(width && height);
    
    avctx->extradata= av_mallocz(1024*10);
    avctx->stats_out= av_mallocz(1024*10);
    s->version=2;
    
    switch(avctx->pix_fmt){
    case PIX_FMT_YUV422P:
        s->bitstream_bpp= 16;
        break;
    default:
        fprintf(stderr, "format not supported\n");
        return -1;
    }
    avctx->bits_per_sample= s->bitstream_bpp;
    s->decorrelate= s->bitstream_bpp >= 24;
    s->predictor= avctx->prediction_method;
    
    ((uint8_t*)avctx->extradata)[0]= s->predictor;
    ((uint8_t*)avctx->extradata)[1]= s->bitstream_bpp;
    ((uint8_t*)avctx->extradata)[2]=
    ((uint8_t*)avctx->extradata)[3]= 0;
    s->avctx->extradata_size= 4;
    
    if(avctx->stats_in){
        char *p= avctx->stats_in;
    
        for(i=0; i<3; i++)
            for(j=0; j<256; j++)
                s->stats[i][j]= 1;

        for(;;){
            for(i=0; i<3; i++){
                char *next;

                for(j=0; j<256; j++){
                    s->stats[i][j]+= strtol(p, &next, 0);
                    if(next==p) return -1;
                    p=next;
                }        
            }
            if(p[0]==0 || p[1]==0 || p[2]==0) break;
        }
    }else{
        for(i=0; i<3; i++)
            for(j=0; j<256; j++){
                int d= FFMIN(j, 256-j);
                
                s->stats[i][j]= 100000000/(d+1);
            }
    }
    
    for(i=0; i<3; i++){
        generate_len_table(s->len[i], s->stats[i], 256);

        if(generate_bits_table(s->bits[i], s->len[i])<0){
            return -1;
        }
        
        store_table(s, s->len[i]);
    }

    for(i=0; i<3; i++)
        for(j=0; j<256; j++)
            s->stats[i][j]= 0;
    
    s->interlaced= height > 288;
    
//    printf("pred:%d bpp:%d hbpp:%d il:%d\n", s->predictor, s->bitstream_bpp, avctx->bits_per_sample, s->interlaced);
    
    s->picture_number=0;
    
    return 0;
}

static void decode_422_bitstream(HYuvContext *s, int count){
    int i;
    
    count/=2;
    
    for(i=0; i<count; i++){
        s->temp[0][2*i  ]= get_vlc2(&s->gb, s->vlc[0].table, VLC_BITS, 3); 
        s->temp[1][  i  ]= get_vlc2(&s->gb, s->vlc[1].table, VLC_BITS, 3); 
        s->temp[0][2*i+1]= get_vlc2(&s->gb, s->vlc[0].table, VLC_BITS, 3); 
        s->temp[2][  i  ]= get_vlc2(&s->gb, s->vlc[2].table, VLC_BITS, 3); 
    }
}

static void encode_422_bitstream(HYuvContext *s, int count){
    int i;
    
    count/=2;
    if(s->flags&CODEC_FLAG_PASS1){
        for(i=0; i<count; i++){
            s->stats[0][ s->temp[0][2*i  ] ]++;
            s->stats[1][ s->temp[1][  i  ] ]++;
            s->stats[0][ s->temp[0][2*i+1] ]++;
            s->stats[2][ s->temp[2][  i  ] ]++;
        }
    }else{
        for(i=0; i<count; i++){
            put_bits(&s->pb, s->len[0][ s->temp[0][2*i  ] ], s->bits[0][ s->temp[0][2*i  ] ]);
            put_bits(&s->pb, s->len[1][ s->temp[1][  i  ] ], s->bits[1][ s->temp[1][  i  ] ]);
            put_bits(&s->pb, s->len[0][ s->temp[0][2*i+1] ], s->bits[0][ s->temp[0][2*i+1] ]);
            put_bits(&s->pb, s->len[2][ s->temp[2][  i  ] ], s->bits[2][ s->temp[2][  i  ] ]);
        }
    }
}

static void decode_bgr_bitstream(HYuvContext *s, int count){
    int i;
    
    if(s->decorrelate){
        if(s->bitstream_bpp==24){
            for(i=0; i<count; i++){
                s->temp[0][4*i+1]= get_vlc2(&s->gb, s->vlc[1].table, VLC_BITS, 3); 
                s->temp[0][4*i  ]= get_vlc2(&s->gb, s->vlc[0].table, VLC_BITS, 3) + s->temp[0][4*i+1];
                s->temp[0][4*i+2]= get_vlc2(&s->gb, s->vlc[2].table, VLC_BITS, 3) + s->temp[0][4*i+1];
            }
        }else{
            for(i=0; i<count; i++){
                s->temp[0][4*i+1]= get_vlc2(&s->gb, s->vlc[1].table, VLC_BITS, 3); 
                s->temp[0][4*i  ]= get_vlc2(&s->gb, s->vlc[0].table, VLC_BITS, 3) + s->temp[0][4*i+1];
                s->temp[0][4*i+2]= get_vlc2(&s->gb, s->vlc[2].table, VLC_BITS, 3) + s->temp[0][4*i+1]; 
                                   get_vlc2(&s->gb, s->vlc[2].table, VLC_BITS, 3); //?!
            }
        }
    }else{
        if(s->bitstream_bpp==24){
            for(i=0; i<count; i++){
                s->temp[0][4*i  ]= get_vlc2(&s->gb, s->vlc[0].table, VLC_BITS, 3);
                s->temp[0][4*i+1]= get_vlc2(&s->gb, s->vlc[1].table, VLC_BITS, 3); 
                s->temp[0][4*i+2]= get_vlc2(&s->gb, s->vlc[2].table, VLC_BITS, 3); 
            }
        }else{
            for(i=0; i<count; i++){
                s->temp[0][4*i  ]= get_vlc2(&s->gb, s->vlc[0].table, VLC_BITS, 3);
                s->temp[0][4*i+1]= get_vlc2(&s->gb, s->vlc[1].table, VLC_BITS, 3); 
                s->temp[0][4*i+2]= get_vlc2(&s->gb, s->vlc[2].table, VLC_BITS, 3); 
                                   get_vlc2(&s->gb, s->vlc[2].table, VLC_BITS, 3); //?!
            }
        }
    }
}

static int decode_frame(AVCodecContext *avctx, void *data, int *data_size, uint8_t *buf, int buf_size){
    HYuvContext *s = avctx->priv_data;
    const int width= s->width;
    const int width2= s->width>>1;
    const int height= s->height;
    const int fake_ystride= s->interlaced ? s->linesize[0]*2  : s->linesize[0];
    const int fake_ustride= s->interlaced ? s->linesize[1]*2  : s->linesize[1];
    const int fake_vstride= s->interlaced ? s->linesize[2]*2  : s->linesize[2];
    int i;

    AVPicture *picture = data;

    *data_size = 0;

    /* no supplementary picture */
    if (buf_size == 0)
        return 0;

    bswap_buf((uint32_t*)s->bitstream_buffer, (uint32_t*)buf, buf_size/4);
    
    init_get_bits(&s->gb, s->bitstream_buffer, buf_size);
    
    if(s->bitstream_bpp<24){
        int y;
        int lefty, leftu, leftv;
        int lefttopy, lefttopu, lefttopv;
        
        if(s->yuy2){
            s->picture[0][3]= get_bits(&s->gb, 8);
            s->picture[0][2]= get_bits(&s->gb, 8);
            s->picture[0][1]= get_bits(&s->gb, 8);
            s->picture[0][0]= get_bits(&s->gb, 8);
            
            fprintf(stderr, "YUY2 output isnt implemenetd yet\n");
            return -1;
        }else{
        
            leftv= s->picture[2][0]= get_bits(&s->gb, 8);
            lefty= s->picture[0][1]= get_bits(&s->gb, 8);
            leftu= s->picture[1][0]= get_bits(&s->gb, 8);
                   s->picture[0][0]= get_bits(&s->gb, 8);
        
            switch(s->predictor){
            case LEFT:
            case PLANE:
                decode_422_bitstream(s, width-2);
                lefty= add_left_prediction(s->picture[0] + 2, s->temp[0], width-2, lefty);
                if(!(s->flags&CODEC_FLAG_GRAY)){
                    leftu= add_left_prediction(s->picture[1] + 1, s->temp[1], width2-1, leftu);
                    leftv= add_left_prediction(s->picture[2] + 1, s->temp[2], width2-1, leftv);
                }

                for(y=1; y<s->height; y++){
                    uint8_t *ydst, *udst, *vdst;
                    decode_422_bitstream(s, width);
                    
                    ydst= s->picture[0] + s->linesize[0]*y;
                    udst= s->picture[1] + s->linesize[1]*y;
                    vdst= s->picture[2] + s->linesize[2]*y;

                    lefty= add_left_prediction(ydst, s->temp[0], width, lefty);
                    if(!(s->flags&CODEC_FLAG_GRAY)){
                        leftu= add_left_prediction(udst, s->temp[1], width2, leftu);
                        leftv= add_left_prediction(vdst, s->temp[2], width2, leftv);
                    }
                    if(s->predictor == PLANE){
                        if(y>s->interlaced){
                            s->dsp.add_bytes(ydst, ydst - fake_ystride, width);
                            if(!(s->flags&CODEC_FLAG_GRAY)){
                                s->dsp.add_bytes(udst, udst - fake_ustride, width2);
                                s->dsp.add_bytes(vdst, vdst - fake_vstride, width2);
                            }
                        }
                    }
                }
                break;
            case MEDIAN:
                /* first line except first 2 pixels is left predicted */
                decode_422_bitstream(s, width-2);
                lefty= add_left_prediction(s->picture[0] + 2, s->temp[0], width-2, lefty);
                if(!(s->flags&CODEC_FLAG_GRAY)){
                    leftu= add_left_prediction(s->picture[1] + 1, s->temp[1], width2-1, leftu);
                    leftv= add_left_prediction(s->picture[2] + 1, s->temp[2], width2-1, leftv);
                }
                
                y=1;
                
                /* second line is left predicted for interlaced case */
                if(s->interlaced){
                    decode_422_bitstream(s, width);
                    lefty= add_left_prediction(s->picture[0] + s->linesize[0], s->temp[0], width, lefty);
                    if(!(s->flags&CODEC_FLAG_GRAY)){
                        leftu= add_left_prediction(s->picture[1] + s->linesize[2], s->temp[1], width2, leftu);
                        leftv= add_left_prediction(s->picture[2] + s->linesize[1], s->temp[2], width2, leftv);
                    }
                    y++;
                }

                /* next 4 pixels are left predicted too */
                decode_422_bitstream(s, 4);
                lefty= add_left_prediction(s->picture[0] + fake_ystride, s->temp[0], 4, lefty);
                if(!(s->flags&CODEC_FLAG_GRAY)){
                    leftu= add_left_prediction(s->picture[1] + fake_ustride, s->temp[1], 2, leftu);
                    leftv= add_left_prediction(s->picture[2] + fake_vstride, s->temp[2], 2, leftv);
                }

                /* next line except the first 4 pixels is median predicted */
                lefttopy= s->picture[0][3];
                decode_422_bitstream(s, width-4);
                add_median_prediction(s->picture[0] + fake_ystride+4, s->picture[0]+4, s->temp[0], width-4, &lefty, &lefttopy);
                if(!(s->flags&CODEC_FLAG_GRAY)){
                    lefttopu= s->picture[1][1];
                    lefttopv= s->picture[2][1];
                    add_median_prediction(s->picture[1] + fake_ustride+2, s->picture[1]+2, s->temp[1], width2-2, &leftu, &lefttopu);
                    add_median_prediction(s->picture[2] + fake_vstride+2, s->picture[2]+2, s->temp[2], width2-2, &leftv, &lefttopv);
                }
                y++;

                for(; y<height; y++){
                    uint8_t *ydst, *udst, *vdst;
                    decode_422_bitstream(s, width);
                    
                    ydst= s->picture[0] + s->linesize[0]*y;
                    udst= s->picture[1] + s->linesize[1]*y;
                    vdst= s->picture[2] + s->linesize[2]*y;

                    add_median_prediction(ydst, ydst - fake_ystride, s->temp[0], width, &lefty, &lefttopy);
                    if(!(s->flags&CODEC_FLAG_GRAY)){
                        add_median_prediction(udst, udst - fake_ustride, s->temp[1], width2, &leftu, &lefttopu);
                        add_median_prediction(vdst, vdst - fake_vstride, s->temp[2], width2, &leftv, &lefttopv);
                    }
                }
                break;
            }
        }
    }else{
        int y;
        int leftr, leftg, leftb;
        const int last_line= (height-1)*s->linesize[0];
        
        if(s->bitstream_bpp==32){
                   s->picture[0][last_line+3]= get_bits(&s->gb, 8);
            leftr= s->picture[0][last_line+2]= get_bits(&s->gb, 8);
            leftg= s->picture[0][last_line+1]= get_bits(&s->gb, 8);
            leftb= s->picture[0][last_line+0]= get_bits(&s->gb, 8);
        }else{
            leftr= s->picture[0][last_line+2]= get_bits(&s->gb, 8);
            leftg= s->picture[0][last_line+1]= get_bits(&s->gb, 8);
            leftb= s->picture[0][last_line+0]= get_bits(&s->gb, 8);
            skip_bits(&s->gb, 8);
        }
        
        if(s->bgr32){
            switch(s->predictor){
            case LEFT:
            case PLANE:
                decode_bgr_bitstream(s, width-1);
                add_left_prediction_bgr32(s->picture[0] + last_line+4, s->temp[0], width-1, &leftr, &leftg, &leftb);

                for(y=s->height-2; y>=0; y--){ //yes its stored upside down
                    decode_bgr_bitstream(s, width);
                    
                    add_left_prediction_bgr32(s->picture[0] + s->linesize[0]*y, s->temp[0], width, &leftr, &leftg, &leftb);
                    if(s->predictor == PLANE){
                        if((y&s->interlaced)==0){
                            s->dsp.add_bytes(s->picture[0] + s->linesize[0]*y, 
                                             s->picture[0] + s->linesize[0]*y + fake_ystride, fake_ystride);
                        }
                    }
                }
                break;
            default:
                fprintf(stderr, "prediction type not supported!\n");
            }
        }else{

            fprintf(stderr, "BGR24 output isnt implemenetd yet\n");
            return -1;
        }
    }
    emms_c();
    
    for(i=0;i<3;i++) {
        picture->data[i] = s->picture[i];
        picture->linesize[i]= s->linesize[i];
    }

    *data_size = sizeof(AVPicture);
    
    return (get_bits_count(&s->gb)+7)>>3;
}

static int decode_end(AVCodecContext *avctx)
{
    HYuvContext *s = avctx->priv_data;
    int i;
    
    for(i=0; i<3; i++){
        av_freep(&s->picture[i]);
        free_vlc(&s->vlc[i]);
    }

    return 0;
}

static int encode_frame(AVCodecContext *avctx, unsigned char *buf, int buf_size, void *data){
    HYuvContext *s = avctx->priv_data;
    AVPicture *pict = data;
    const int width= s->width;
    const int width2= s->width>>1;
    const int height= s->height;
    const int fake_ystride= s->interlaced ? pict->linesize[0]*2  : pict->linesize[0];
    const int fake_ustride= s->interlaced ? pict->linesize[1]*2  : pict->linesize[1];
    const int fake_vstride= s->interlaced ? pict->linesize[2]*2  : pict->linesize[2];
    int i, size;

    init_put_bits(&s->pb, buf, buf_size, NULL, NULL);
    
    for(i=0; i<3; i++){
        s->picture[i]= pict->data[i];
        s->linesize[i]= pict->linesize[i];
    }
    
    if(avctx->pix_fmt == PIX_FMT_YUV422P){
        int lefty, leftu, leftv, y;

        put_bits(&s->pb, 8, leftv= s->picture[2][0]);
        put_bits(&s->pb, 8, lefty= s->picture[0][1]);
        put_bits(&s->pb, 8, leftu= s->picture[1][0]);
        put_bits(&s->pb, 8,        s->picture[0][0]);
        
        lefty= sub_left_prediction(s->temp[0], s->picture[0]+2, width-2 , lefty);
        leftu= sub_left_prediction(s->temp[1], s->picture[1]+1, width2-1, leftu);
        leftv= sub_left_prediction(s->temp[2], s->picture[2]+1, width2-1, leftv);
        
        encode_422_bitstream(s, width-2);
        
        if(s->predictor==MEDIAN){
            int lefttopy, lefttopu, lefttopv;
            y=1;
            if(s->interlaced){
                lefty= sub_left_prediction(s->temp[0], s->picture[0]+s->linesize[0], width , lefty);
                leftu= sub_left_prediction(s->temp[1], s->picture[1]+s->linesize[1], width2, leftu);
                leftv= sub_left_prediction(s->temp[2], s->picture[2]+s->linesize[2], width2, leftv);
        
                encode_422_bitstream(s, width);
                y++;
            }
            
            lefty= sub_left_prediction(s->temp[0], s->picture[0]+fake_ystride, 4, lefty);
            leftu= sub_left_prediction(s->temp[1], s->picture[1]+fake_ystride, 2, leftu);
            leftv= sub_left_prediction(s->temp[2], s->picture[2]+fake_ystride, 2, leftv);
        
            encode_422_bitstream(s, 4);
                        
            lefttopy= s->picture[0][3];
            lefttopu= s->picture[1][1];
            lefttopv= s->picture[2][1];
            sub_median_prediction(s->temp[0], s->picture[0]+4, s->picture[0] + fake_ystride+4, width-4 , &lefty, &lefttopy);
            sub_median_prediction(s->temp[1], s->picture[1]+2, s->picture[1] + fake_ustride+2, width2-2, &leftu, &lefttopu);
            sub_median_prediction(s->temp[2], s->picture[2]+2, s->picture[2] + fake_vstride+2, width2-2, &leftv, &lefttopv);
            encode_422_bitstream(s, width-4);
            y++;

            for(; y<height; y++){
                uint8_t *ydst, *udst, *vdst;
                    
                ydst= s->picture[0] + s->linesize[0]*y;
                udst= s->picture[1] + s->linesize[1]*y;
                vdst= s->picture[2] + s->linesize[2]*y;

                sub_median_prediction(s->temp[0], ydst - fake_ystride, ydst, width , &lefty, &lefttopy);
                sub_median_prediction(s->temp[1], udst - fake_ustride, udst, width2, &leftu, &lefttopu);
                sub_median_prediction(s->temp[2], vdst - fake_vstride, vdst, width2, &leftv, &lefttopv);

                encode_422_bitstream(s, width);
            }
        }else{
            for(y=1; y<height; y++){
                uint8_t *ydst, *udst, *vdst;
                    
                ydst= s->picture[0] + s->linesize[0]*y;
                udst= s->picture[1] + s->linesize[1]*y;
                vdst= s->picture[2] + s->linesize[2]*y;

                if(s->predictor == PLANE && s->interlaced < y){
                    s->dsp.diff_bytes(s->temp[0], ydst, ydst - fake_ystride, width);
                    s->dsp.diff_bytes(s->temp[1], udst, udst - fake_ustride, width2);
                    s->dsp.diff_bytes(s->temp[2], vdst, vdst - fake_vstride, width2);

                    lefty= sub_left_prediction(s->temp[0], s->temp[0], width , lefty);
                    leftu= sub_left_prediction(s->temp[1], s->temp[1], width2, leftu);
                    leftv= sub_left_prediction(s->temp[2], s->temp[2], width2, leftv);
                }else{
                    lefty= sub_left_prediction(s->temp[0], ydst, width , lefty);
                    leftu= sub_left_prediction(s->temp[1], udst, width2, leftu);
                    leftv= sub_left_prediction(s->temp[2], vdst, width2, leftv);
                }

                encode_422_bitstream(s, width);
            }
        }        
    }else{
        fprintf(stderr, "Format not supported!\n");
    }
    emms_c();
    
    size= (get_bit_count(&s->pb)+31)/32;
    
    if((s->flags&CODEC_FLAG_PASS1) && (s->picture_number&31)==0){
        int j;
        char *p= avctx->stats_out;
        for(i=0; i<3; i++){
            for(j=0; j<256; j++){
                sprintf(p, "%Ld ", s->stats[i][j]);
                p+= strlen(p);
                s->stats[i][j]= 0;
            }
            sprintf(p, "\n");
            p++;
        }
    }else{
        bswap_buf((uint32_t*)buf, (uint32_t*)buf, size);
    }
    
    avctx->key_frame= 1;
    avctx->pict_type= I_TYPE;
    
    s->picture_number++;
    
    return size*4;
}

static int encode_end(AVCodecContext *avctx)
{
//    HYuvContext *s = avctx->priv_data;

    av_freep(&avctx->extradata);
    av_freep(&avctx->stats_out);
    
    return 0;
}

AVCodec huffyuv_decoder = {
    "huffyuv",
    CODEC_TYPE_VIDEO,
    CODEC_ID_HUFFYUV,
    sizeof(HYuvContext),
    decode_init,
    NULL,
    decode_end,
    decode_frame,
    0,
    NULL
};

AVCodec huffyuv_encoder = {
    "huffyuv",
    CODEC_TYPE_VIDEO,
    CODEC_ID_HUFFYUV,
    sizeof(HYuvContext),
    encode_init,
    encode_frame,
    encode_end,
};
