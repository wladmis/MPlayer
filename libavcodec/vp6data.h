/**
 * @file vp6data.h
 * VP6 compatible video decoder
 *
 * Copyright (C) 2006  Aurelien Jacobs <aurel@gnuage.org>
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef VP6DATA_H
#define VP6DATA_H

#include "vp56data.h"

static const uint8_t vp6_def_fdv_vector_model[2][8] = {
    { 247, 210, 135, 68, 138, 220, 239, 246 },
    { 244, 184, 201, 44, 173, 221, 239, 253 },
};

static const uint8_t vp6_def_pdv_vector_model[2][7] = {
    { 225, 146, 172, 147, 214,  39, 156 },
    { 204, 170, 119, 235, 140, 230, 228 },
};

static const uint8_t vp6_def_coeff_reorder[] = {
     0,  0,  1,  1,  1,  2,  2,  2,
     2,  2,  2,  3,  3,  4,  4,  4,
     5,  5,  5,  5,  6,  6,  7,  7,
     7,  7,  7,  8,  8,  9,  9,  9,
     9,  9,  9, 10, 10, 11, 11, 11,
    11, 11, 11, 12, 12, 12, 12, 12,
    12, 13, 13, 13, 13, 13, 14, 14,
    14, 14, 15, 15, 15, 15, 15, 15,
};

static const uint8_t vp6_def_runv_coeff_model[2][14] = {
    { 198, 197, 196, 146, 198, 204, 169, 142, 130, 136, 149, 149, 191, 249 },
    { 135, 201, 181, 154,  98, 117, 132, 126, 146, 169, 184, 240, 246, 254 },
};

static const uint8_t vp6_sig_dct_pct[2][2] = {
    { 237, 246 },
    { 231, 243 },
};

static const uint8_t vp6_pdv_pct[2][7] = {
    { 253, 253, 254, 254, 254, 254, 254 },
    { 245, 253, 254, 254, 254, 254, 254 },
};

static const uint8_t vp6_fdv_pct[2][8] = {
    { 254, 254, 254, 254, 254, 250, 250, 252 },
    { 254, 254, 254, 254, 254, 251, 251, 254 },
};

static const uint8_t vp6_dccv_pct[2][11] = {
    { 146, 255, 181, 207, 232, 243, 238, 251, 244, 250, 249 },
    { 179, 255, 214, 240, 250, 255, 244, 255, 255, 255, 255 },
};

static const uint8_t vp6_coeff_reorder_pct[] =  {
    255, 132, 132, 159, 153, 151, 161, 170,
    164, 162, 136, 110, 103, 114, 129, 118,
    124, 125, 132, 136, 114, 110, 142, 135,
    134, 123, 143, 126, 153, 183, 166, 161,
    171, 180, 179, 164, 203, 218, 225, 217,
    215, 206, 203, 217, 229, 241, 248, 243,
    253, 255, 253, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255,
};

static const uint8_t vp6_runv_pct[2][14] = {
  { 219, 246, 238, 249, 232, 239, 249, 255, 248, 253, 239, 244, 241, 248 },
  { 198, 232, 251, 253, 219, 241, 253, 255, 248, 249, 244, 238, 251, 255 },
};

static const uint8_t vp6_ract_pct[3][2][6][11] = {
  { { { 227, 246, 230, 247, 244, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 209, 231, 231, 249, 249, 253, 255, 255, 255 },
      { 255, 255, 225, 242, 241, 251, 253, 255, 255, 255, 255 },
      { 255, 255, 241, 253, 252, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 248, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 } },
    { { 240, 255, 248, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 240, 253, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 } } },
  { { { 206, 203, 227, 239, 247, 255, 253, 255, 255, 255, 255 },
      { 207, 199, 220, 236, 243, 252, 252, 255, 255, 255, 255 },
      { 212, 219, 230, 243, 244, 253, 252, 255, 255, 255, 255 },
      { 236, 237, 247, 252, 253, 255, 255, 255, 255, 255, 255 },
      { 240, 240, 248, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 } },
    { { 230, 233, 249, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 238, 238, 250, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 248, 251, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 } } },
  { { { 225, 239, 227, 231, 244, 253, 243, 255, 255, 253, 255 },
      { 232, 234, 224, 228, 242, 249, 242, 252, 251, 251, 255 },
      { 235, 249, 238, 240, 251, 255, 249, 255, 253, 253, 255 },
      { 249, 253, 251, 250, 255, 255, 255, 255, 255, 255, 255 },
      { 251, 250, 249, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 } },
    { { 243, 244, 250, 250, 255, 255, 255, 255, 255, 255, 255 },
      { 249, 248, 250, 253, 255, 255, 255, 255, 255, 255, 255 },
      { 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
      { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 } } }
};

static const int vp6_dccv_lc[3][5][2] = {
  { { 122, 133 }, { 0, 1 }, { 78,  171 }, { 139, 117 }, { 168, 79 } },
  { { 133,  51 }, { 0, 1 }, { 169,  71 }, { 214,  44 }, { 210, 38 } },
  { { 142, -16 }, { 0, 1 }, { 221, -30 }, { 246,  -3 }, { 203, 17 } },
};

static const uint8_t vp6_coeff_groups[] = {
    0, 0, 1, 1, 1, 2, 2, 2,
    2, 2, 2, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
};

static const int16_t vp6_block_copy_filter[16][8][4] = {
  { {   0, 128,   0,   0  },  /* 0 */
    {  -3, 122,   9,   0  },
    {  -4, 109,  24,  -1  },
    {  -5,  91,  45,  -3  },
    {  -4,  68,  68,  -4  },
    {  -3,  45,  91,  -5  },
    {  -1,  24, 109,  -4  },
    {   0,   9, 122,  -3  } },
  { {   0, 128,   0,   0  },  /* 1 */
    {  -4, 124,   9,  -1  },
    {  -5, 110,  25,  -2  },
    {  -6,  91,  46,  -3  },
    {  -5,  69,  69,  -5  },
    {  -3,  46,  91,  -6  },
    {  -2,  25, 110,  -5  },
    {  -1,   9, 124,  -4  } },
  { {   0, 128,   0,   0  },  /* 2 */
    {  -4, 123,  10,  -1  },
    {  -6, 110,  26,  -2  },
    {  -7,  92,  47,  -4  },
    {  -6,  70,  70,  -6  },
    {  -4,  47,  92,  -7  },
    {  -2,  26, 110,  -6  },
    {  -1,  10, 123,  -4  } },
  { {   0, 128,   0,   0  },  /* 3 */
    {  -5, 124,  10,  -1  },
    {  -7, 110,  27,  -2  },
    {  -7,  91,  48,  -4  },
    {  -6,  70,  70,  -6  },
    {  -4,  48,  92,  -8  },
    {  -2,  27, 110,  -7  },
    {  -1,  10, 124,  -5  } },
  { {   0, 128,   0,   0  },  /* 4 */
    {  -6, 124,  11,  -1  },
    {  -8, 111,  28,  -3  },
    {  -8,  92,  49,  -5  },
    {  -7,  71,  71,  -7  },
    {  -5,  49,  92,  -8  },
    {  -3,  28, 111,  -8  },
    {  -1,  11, 124,  -6  } },
  { {  0,  128,   0,   0  },  /* 5 */
    {  -6, 123,  12,  -1  },
    {  -9, 111,  29,  -3  },
    {  -9,  93,  50,  -6  },
    {  -8,  72,  72,  -8  },
    {  -6,  50,  93,  -9  },
    {  -3,  29, 111,  -9  },
    {  -1,  12, 123,  -6  } },
  { {   0, 128,   0,   0  },  /* 6 */
    {  -7, 124,  12,  -1  },
    { -10, 111,  30,  -3  },
    { -10,  93,  51,  -6  },
    {  -9,  73,  73,  -9  },
    {  -6,  51,  93, -10  },
    {  -3,  30, 111, -10  },
    {  -1,  12, 124,  -7  } },
  { {   0, 128,   0,   0  },  /* 7 */
    {  -7, 123,  13,  -1  },
    { -11, 112,  31,  -4  },
    { -11,  94,  52,  -7  },
    { -10,  74,  74, -10  },
    {  -7,  52,  94, -11  },
    {  -4,  31, 112, -11  },
    {  -1,  13, 123,  -7  } },
  { {   0, 128,   0,  0  },  /* 8 */
    {  -8, 124,  13,  -1  },
    { -12, 112,  32,  -4  },
    { -12,  94,  53,  -7  },
    { -10,  74,  74, -10  },
    {  -7,  53,  94, -12  },
    {  -4,  32, 112, -12  },
    {  -1,  13, 124,  -8  } },
  { {   0, 128,   0,   0  },  /* 9 */
    {  -9, 124,  14,  -1  },
    { -13, 112,  33,  -4  },
    { -13,  95,  54,  -8  },
    { -11,  75,  75, -11  },
    {  -8,  54,  95, -13  },
    {  -4,  33, 112, -13  },
    {  -1,  14, 124,  -9  } },
  { {   0, 128,   0,   0  },  /* 10 */
    {  -9, 123,  15,  -1  },
    { -14, 113,  34,  -5  },
    { -14,  95,  55,  -8  },
    { -12,  76,  76, -12  },
    {  -8,  55,  95, -14  },
    {  -5,  34, 112, -13  },
    {  -1,  15, 123,  -9  } },
  { {   0, 128,   0,   0  },  /* 11 */
    { -10, 124,  15,  -1  },
    { -14, 113,  34,  -5  },
    { -15,  96,  56,  -9  },
    { -13,  77,  77, -13  },
    {  -9,  56,  96, -15  },
    {  -5,  34, 113, -14  },
    {  -1,  15, 124, -10  } },
  { {   0, 128,   0,   0  },  /* 12 */
    { -10, 123,  16,  -1  },
    { -15, 113,  35,  -5  },
    { -16,  98,  56, -10  },
    { -14,  78,  78, -14  },
    { -10,  56,  98, -16  },
    {  -5,  35, 113, -15  },
    {  -1,  16, 123, -10  } },
  { {   0, 128,   0,   0  },  /* 13 */
    { -11, 124,  17,  -2  },
    { -16, 113,  36,  -5  },
    { -17,  98,  57, -10  },
    { -14,  78,  78, -14  },
    { -10,  57,  98, -17  },
    {  -5,  36, 113, -16  },
    {  -2,  17, 124, -11  } },
  { {   0, 128,   0,   0  },  /* 14 */
    { -12, 125,  17,  -2  },
    { -17, 114,  37,  -6  },
    { -18,  99,  58, -11  },
    { -15,  79,  79, -15  },
    { -11,  58,  99, -18  },
    {  -6,  37, 114, -17  },
    {  -2,  17, 125, -12  } },
  { {   0, 128,   0,   0  },  /* 15 */
    { -12, 124,  18,  -2  },
    { -18, 114,  38,  -6  },
    { -19,  99,  59, -11  },
    { -16,  80,  80, -16  },
    { -11,  59,  99, -19  },
    {  -6,  38, 114, -18  },
    {  -2,  18, 124, -12  } },
};

const vp56_tree_t vp6_pcr_tree[] = {
    { 8, 0},
    { 4, 1},
    { 2, 2}, {-1}, {-2},
    { 2, 3}, {-3}, {-4},
    { 8, 4},
    { 4, 5},
    { 2, 6}, {-5}, {-6},
    { 2, 7}, {-7}, {-8},
             {-0},
};

static const uint8_t vp6_coord_div[] = { 4, 4, 4, 4, 8, 8 };

#endif /* VP6DATA_H */
