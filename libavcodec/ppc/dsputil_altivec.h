/*
 * Copyright (c) 2002 Brian Foley
 * Copyright (c) 2002 Dieter Shirley
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
 */

extern int pix_abs16x16_x2_altivec(uint8_t *pix1, uint8_t *pix2, int line_size);
extern int pix_abs16x16_y2_altivec(uint8_t *pix1, uint8_t *pix2, int line_size);
extern int pix_abs16x16_xy2_altivec(uint8_t *pix1, uint8_t *pix2, int line_size);
extern int pix_abs16x16_altivec(uint8_t *pix1, uint8_t *pix2, int line_size);
extern int pix_abs8x8_altivec(uint8_t *pix1, uint8_t *pix2, int line_size);
extern int sad16x16_altivec(void *s, uint8_t *a, uint8_t *b, int stride);
extern int sad8x8_altivec(void *s, uint8_t *a, uint8_t *b, int stride);
extern int pix_norm1_altivec(uint8_t *pix, int line_size);
extern int sse8_altivec(void *v, uint8_t *pix1, uint8_t *pix2, int line_size);
extern int sse16_altivec(void *v, uint8_t *pix1, uint8_t *pix2, int line_size);
extern int pix_sum_altivec(UINT8 * pix, int line_size);
extern void diff_pixels_altivec(DCTELEM* block, const UINT8* s1, const UINT8* s2, int stride);
extern void get_pixels_altivec(DCTELEM* block, const UINT8 * pixels, int line_size);

extern void add_bytes_altivec(uint8_t *dst, uint8_t *src, int w);
extern void put_pixels_clamped_altivec(const DCTELEM *block, UINT8 *restrict pixels, int line_size);
void put_pixels16_altivec(uint8_t *block, const uint8_t *pixels, int line_size, int h);
void avg_pixels16_altivec(uint8_t *block, const uint8_t *pixels, int line_size, int h);

extern void gmc1_altivec(UINT8 *dst, UINT8 *src, int stride, int h, int x16, int y16, int rounder);

extern int has_altivec(void);

#ifdef HAVE_ALTIVEC

// used to build registers permutation vectors (vcprm)
// the 's' are for words in the _s_econd vector
#define WORD_0 0x00,0x01,0x02,0x03
#define WORD_1 0x04,0x05,0x06,0x07
#define WORD_2 0x08,0x09,0x0a,0x0b
#define WORD_3 0x0c,0x0d,0x0e,0x0f
#define WORD_s0 0x10,0x11,0x12,0x13
#define WORD_s1 0x14,0x15,0x16,0x17
#define WORD_s2 0x18,0x19,0x1a,0x1b
#define WORD_s3 0x1c,0x1d,0x1e,0x1f

#define vcprm(a,b,c,d) (const vector unsigned char)(WORD_ ## a, WORD_ ## b, WORD_ ## c, WORD_ ## d)

// vcprmle is used to keep the same index as in the SSE version.
// it's the same as vcprm, with the index inversed
// ('le' is Little Endian)
#define vcprmle(a,b,c,d) vcprm(d,c,b,a)

// used to build inverse/identity vectors (vcii)
// n is _n_egative, p is _p_ositive
#define FLOAT_n -1.
#define FLOAT_p 1.

#define vcii(a,b,c,d) (const vector float)(FLOAT_ ## a, FLOAT_ ## b, FLOAT_ ## c, FLOAT_ ## d)

#ifdef ALTIVEC_TBL_PERFORMANCE_REPORT
void altivec_display_perf_report(void);
/* if you add to the enum below, also add to the perfname array
   in dsputil_altivec.c */
enum altivec_perf_index {
  altivec_fft_num = 0,
  altivec_gmc1_num,
  altivec_dct_unquantize_h263_num,
  altivec_idct_add_num,
  altivec_idct_put_num,
  altivec_put_pixels_clamped_num,
  altivec_put_pixels16_num,
  altivec_avg_pixels16_num,
  altivec_perf_total
};
enum altivec_data_index {
  altivec_data_min = 0,
  altivec_data_max,
  altivec_data_sum,
  altivec_data_num,
  altivec_data_total
};
extern unsigned long long perfdata[altivec_perf_total][altivec_data_total];
#define ALTIVEC_TBL_DECLARE(a, cond) register unsigned long tbl_start, tbl_stop
#define ALTIVEC_TBL_START_COUNT(a, cond) do { asm("mftb %0" : "=r" (tbl_start)); } while (0)
#define ALTIVEC_TBL_STOP_COUNT(a, cond) do {     \
  asm volatile("mftb %0" : "=r" (tbl_stop));              \
  if (tbl_stop > tbl_start)                      \
  {                                              \
    unsigned long diff =  tbl_stop - tbl_start;  \
    if (cond)                                    \
    {                                            \
      if (diff < perfdata[a][altivec_data_min])  \
        perfdata[a][altivec_data_min] = diff;    \
      if (diff > perfdata[a][altivec_data_max])  \
        perfdata[a][altivec_data_max] = diff;    \
      perfdata[a][altivec_data_sum] += diff;     \
      perfdata[a][altivec_data_num] ++;          \
    }                                            \
  }                                              \
} while (0)
#else /* ALTIVEC_TBL_PERFORMANCE_REPORT */
#define ALTIVEC_TBL_DECLARE(a, cond)
#define ALTIVEC_TBL_START_COUNT(a, cond)
#define ALTIVEC_TBL_STOP_COUNT(a, cond)
#endif /* ALTIVEC_TBL_PERFORMANCE_REPORT */

#else /* HAVE_ALTIVEC */
#ifdef ALTIVEC_USE_REFERENCE_C_CODE
#error "I can't use ALTIVEC_USE_REFERENCE_C_CODE if I don't use HAVE_ALTIVEC"
#endif /* ALTIVEC_USE_REFERENCE_C_CODE */
#ifdef ALTIVEC_TBL_PERFORMANCE_REPORT
#error "I can't use ALTIVEC_TBL_PERFORMANCE_REPORT if I don't use HAVE_ALTIVEC"
#endif /* ALTIVEC_TBL_PERFORMANCE_REPORT */
#endif /* HAVE_ALTIVEC */
