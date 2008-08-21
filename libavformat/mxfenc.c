/*
 * MXF muxer
 * Copyright (c) 2008 GUCAS, Zhentan Feng <spyfeng at gmail dot com>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
 * References
 * SMPTE 336M KLV Data Encoding Protocol Using Key-Length-Value
 * SMPTE 377M MXF File Format Specifications
 * SMPTE 379M MXF Generic Container
 * SMPTE 381M Mapping MPEG Streams into the MXF Generic Container
 * SMPTE RP210: SMPTE Metadata Dictionary
 * SMPTE RP224: Registry of SMPTE Universal Labels
 */

//#define DEBUG

#include "mxf.h"

typedef struct {
    int local_tag;
    UID uid;
} MXFLocalTagPair;

typedef struct {
    UID track_essence_element_key;
} MXFStreamContext;

typedef struct MXFContext {
    int64_t header_byte_count;
    int64_t header_byte_count_offset;
    int64_t header_footer_partition_offset;
    int essence_container_count;
} MXFContext;

typedef struct {
    const UID key;
    int (*write)();
    enum CodecType type;
} MXFDescriptorWriteTableEntry;

static const uint8_t uuid_base[]            = { 0xAD,0xAB,0x44,0x24,0x2f,0x25,0x4d,0xc7,0x92,0xff,0x29,0xbd };
static const uint8_t umid_base[]            = { 0x06,0x0A,0x2B,0x34,0x01,0x01,0x01,0x01,0x01,0x01,0x0F,0x00,0x13,0x00,0x00,0x00 };

/**
 * complete key for operation pattern, partitions, and primer pack
 */
static const uint8_t op1a_ul[]              = { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x01,0x01,0x00 };
static const uint8_t header_partition_key[] = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x02,0x04,0x00 }; // ClosedComplete
static const uint8_t footer_partition_key[] = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x04,0x04,0x00 }; // ClosedComplete
static const uint8_t primer_pack_key[]      = { 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x02,0x01,0x01,0x05,0x01,0x00 };

/**
 * partial key for header metadata
 */
static const uint8_t header_metadata_key[]  = { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0D,0x01,0x01,0x01,0x01 };

static const MXFCodecUL mxf_essence_element_key[] = {
    { { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x15,0x01,0x05,0x00 }, 14, CODEC_ID_MPEG2VIDEO},
    { { 0x06,0x0E,0x2B,0x34,0x01,0x02,0x01,0x01,0x0D,0x01,0x03,0x01,0x16,0x01,0x01,0x00 }, 14, CODEC_ID_PCM_S16LE},
    { { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }, 0, CODEC_ID_NONE},
};

static const uint8_t multiple_desc_ul[] = { 0x06,0x0E,0x2B,0x34,0x04,0x01,0x01,0x03,0x0D,0x01,0x03,0x01,0x02,0x7F,0x01,0x00 };

static void mxf_write_uuid(ByteIOContext *pb, enum CodecID type, int value)
{
    put_buffer(pb, uuid_base, 12);
    put_be16(pb, type);
    put_be16(pb, value);
}

static void mxf_write_umid(ByteIOContext *pb, enum CodecID type, int value)
{
    put_buffer(pb, umid_base, 16);
    mxf_write_uuid(pb, type, value);
}

static void mxf_write_refs_count(ByteIOContext *pb, int ref_count)
{
    put_be32(pb, ref_count);
    put_be32(pb, 16);
}

static int klv_encode_ber_length(ByteIOContext *pb, uint64_t len)
{
    // Determine the best BER size
    int size;
    if (len < 128) {
        //short form
        put_byte(pb, len);
        return 1;
    }

    size = (av_log2(len) >> 3) + 1;

    // long form
    put_byte(pb, 0x80 + size);
    while(size) {
        size --;
        put_byte(pb, len >> 8 * size & 0xff);
    }
    return 0;
}

static const MXFCodecUL *mxf_get_essence_container_ul(enum CodecID type)
{
    const MXFCodecUL *uls = ff_mxf_essence_container_uls;
    while (uls->id != CODEC_ID_NONE) {
        if (uls->id == type)
            break;
        uls++;
    }
    return uls;
}

static int mxf_write_primer_pack(AVFormatContext *s)
{
    ByteIOContext *pb = s->pb;
    int local_tag_number, i = 0;

    local_tag_number = sizeof(mxf_local_tag_batch) / sizeof(MXFLocalTagPair);

    put_buffer(pb, primer_pack_key, 16);
    klv_encode_ber_length(pb, local_tag_number * 18 + 8);

    put_be32(pb, local_tag_number); // local_tag num
    put_be32(pb, 18); // item size, always 18 according to the specs

    for (i = 0; i < local_tag_number; i++) {
        put_be16(pb, mxf_local_tag_batch[i].local_tag);
        put_buffer(pb, mxf_local_tag_batch[i].uid, 16);
    }
    return 0;
}

static void mxf_write_local_tag(ByteIOContext *pb, int value_size, int tag)
{
    put_be16(pb, tag);
    put_be16(pb, value_size);
}

static void mxf_write_metadata_key(ByteIOContext *pb, unsigned int value)
{
    put_buffer(pb, header_metadata_key, 13);
    put_be24(pb, value);
}

static void mxf_free(AVFormatContext *s)
{
    AVStream *st;
    int i;

    for (i = 0; i < s->nb_streams; i++) {
        st = s->streams[i];
        av_freep(&st->priv_data);
    }
}

static const MXFDataDefinitionUL *mxf_get_data_definition_ul(enum CodecType type)
{
    const MXFDataDefinitionUL *uls = ff_mxf_data_definition_uls;
    while (uls->type != CODEC_TYPE_DATA) {
        if (type == uls->type)
            break;
        uls ++;
    }
    return uls;
}

static void mxf_write_common_fields(    ByteIOContext *pb, AVStream *st)
{
    const MXFDataDefinitionUL * data_def_ul;

    // find data define uls
    data_def_ul = mxf_get_data_definition_ul(st->codec->codec_type);
    mxf_write_local_tag(pb, 16, 0x0201);
    put_buffer(pb, data_def_ul->uid, 16);

    // write duration
    mxf_write_local_tag(pb, 8, 0x0202);
    put_be64(pb, st->duration);
}

static int mux_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    ByteIOContext *pb = s->pb;
    AVStream *st = s->streams[pkt->stream_index];
    MXFStreamContext *sc = st->priv_data;

    put_buffer(pb, sc->track_essence_element_key, 16); // write key
    klv_encode_ber_length(pb, pkt->size); // write length
    put_buffer(pb, pkt->data, pkt->size); // write value

    put_flush_packet(pb);
    return 0;
}

static void mxf_write_header_desc(ByteIOContext *pb, const MXFDescriptorWriteTableEntry *desc_tbl, AVStream *st)
{
    const MXFCodecUL *codec_ul;

    put_buffer(pb, desc_tbl->key, 16);
    klv_encode_ber_length(pb, 96);

    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, SubDescriptor, st->index);

    mxf_write_local_tag(pb, 4, 0x3006);
    put_be32(pb, st->index);

    codec_ul = mxf_get_essence_container_ul(st->codec->codec_id);
    mxf_write_local_tag(pb, 16, 0x3004);
    put_buffer(pb, codec_ul->uid, 16);
}

static int mxf_write_mpeg_video_desc(AVFormatContext *s, const MXFDescriptorWriteTableEntry *desc_tbl, int stream_index)
{
    ByteIOContext *pb = s->pb;
    AVStream *st;

    st = s->streams[stream_index];
    mxf_write_header_desc(pb, desc_tbl, st);

    mxf_write_local_tag(pb, 4, 0x3203);
    put_be32(pb, st->codec->width);

    mxf_write_local_tag(pb, 4, 0x3202);
    put_be32(pb, st->codec->height);

    mxf_write_local_tag(pb, 8, 0x320E);
    put_be32(pb, st->codec->height * st->codec->sample_aspect_ratio.den);
    put_be32(pb, st->codec->width * st->codec->sample_aspect_ratio.num);

    // tmp write, will modified later
    mxf_write_local_tag(pb, 16, 0x3201);
    put_buffer(pb, ff_mxf_codec_uls->uid, 16);
    return 0;
}

static int mxf_write_wav_desc(AVFormatContext *s, const MXFDescriptorWriteTableEntry *desc_tbl, int stream_index)
{
    ByteIOContext *pb = s->pb;
    AVStream *st;

    st = s->streams[stream_index];
    mxf_write_header_desc(pb, desc_tbl, st);

    // write audio sampling rate
    mxf_write_local_tag(pb, 8, 0x3D03);
    put_be32(pb, st->codec->sample_rate);
    put_be32(pb, 1);

    mxf_write_local_tag(pb, 4, 0x3D07);
    put_be32(pb, st->codec->channels);

    mxf_write_local_tag(pb, 4, 0x3D01);
    put_be32(pb, st->codec->bits_per_sample);

    // tmp write, will modified later
    mxf_write_local_tag(pb, 16, 0x3201);
    put_buffer(pb, (ff_mxf_codec_uls + 8) ->uid, 16);
    return 0;
}

static const MXFDescriptorWriteTableEntry mxf_descriptor_write_table[] = {
    { { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x01,0x01,0x01,0x01,0x51,0x00 }, mxf_write_mpeg_video_desc, CODEC_ID_MPEG2VIDEO},
    { { 0x06,0x0E,0x2B,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x01,0x01,0x01,0x01,0x48,0x00 }, mxf_write_wav_desc, CODEC_ID_PCM_S16LE},
    { { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }, NULL, CODEC_ID_NONE},
};

static int mxf_build_structural_metadata(AVFormatContext *s, enum MXFMetadataSetType type)
{
    int i;
    const MXFDescriptorWriteTableEntry *desc = NULL;
    int track_number_sign[sizeof(mxf_essence_element_key)/sizeof(MXFCodecUL)] = { 0 };

    if (mxf_write_package(s, type) < 0)
        return -1;
    if (type == SourcePackage) {
        if (mxf_write_multi_descriptor(s) < 0)
            return -1;
    }

    for (i = 0;i < s->nb_streams; i++) {
        if ( mxf_write_track(s, i, type, track_number_sign) < 0)
            return -1;
        if ( mxf_write_sequence(s, i, type) < 0)
            return -1;
        if ( mxf_write_structural_component(s, i, type) < 0)
            return -1;

        if (type == SourcePackage) {
            for (desc = mxf_descriptor_write_table; desc->write; desc++) {
                if (s->streams[i]->codec->codec_id == desc->type) {
                    if ( desc->write(s, desc, i) < 0) {
                        av_log(s, AV_LOG_ERROR, "error writing descriptor\n");
                        return -1;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}

static int mxf_write_header_metadata_sets(AVFormatContext *s)
{
    AVStream *st;
    MXFStreamContext *sc = NULL;
    int i;
    if (mxf_write_preface(s) < 0)
        return -1;

    if (mxf_write_identification(s) < 0)
        return -1;

    if (mxf_write_content_storage(s) < 0)
        return -1;

    for (i = 0; i < s->nb_streams; i++) {
        st = s->streams[i];
        sc = av_mallocz(sizeof(MXFStreamContext));
        if (!sc)
            return AVERROR(ENOMEM);
        st->priv_data = sc;
        // set pts information
        if (st->codec->codec_type == CODEC_TYPE_VIDEO) {
            av_set_pts_info(st, 64, 1, st->codec->time_base.den);
        } else if (st->codec->codec_type == CODEC_TYPE_AUDIO) {
            av_set_pts_info(st, 64, 1, st->codec->sample_rate);
        }
    }

    if (mxf_build_structural_metadata(s, MaterialPackage) < 0)
        return -1;

    if (mxf_build_structural_metadata(s, SourcePackage) < 0)
        return -1;
    return 0;
}

static int mxf_update_header_partition(AVFormatContext *s, int64_t footer_partition_offset)
{
    MXFContext *mxf = s->priv_data;
    ByteIOContext *pb = s->pb;

    url_fseek(pb, mxf->header_byte_count_offset, SEEK_SET);
    put_be64(pb, mxf->header_byte_count);
    put_flush_packet(pb);

    url_fseek(pb, mxf->header_footer_partition_offset, SEEK_SET);
    put_be64(pb, footer_partition_offset);
    put_flush_packet(pb);
    return 0;
}
AVOutputFormat mxf_muxer = {
    "mxf",
    NULL_IF_CONFIG_SMALL("Material eXchange Format"),
    NULL,
    "mxf",
    sizeof(MXFContext),
    CODEC_ID_PCM_S16LE,
    CODEC_ID_MPEG2VIDEO,
    mux_write_header,
    mux_write_packet,
    mux_write_footer,
};