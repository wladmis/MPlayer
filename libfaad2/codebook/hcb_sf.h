/*
** FAAD2 - Freeware Advanced Audio (AAC) Decoder including SBR decoding
** Copyright (C) 2003 M. Bakker, Ahead Software AG, http://www.nero.com
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** Any non-GPL usage of this software or parts of this software is strictly
** forbidden.
**
** Commercial non-GPL licensing of this software is possible.
** For more info contact Ahead Software through Mpeg4AAClicense@nero.com.
**
** Initially modified for use with MPlayer by Arpad Gere�ffy on 2003/08/30
** $Id: hcb_sf.h,v 1.2 2004/06/23 13:50:53 diego Exp $
** detailed CVS changelog at http://www.mplayerhq.hu/cgi-bin/cvsweb.cgi/main/
**/

/* Binary search huffman table HCB_SF */


static uint8_t hcb_sf[][2] = {
    { /*  0 */  1, 2 },
    { /*  1 */  60, 0 },
    { /*  2 */  1, 2 },
    { /*  3 */  2, 3 },
    { /*  4 */  3, 4 },
    { /*  5 */  59, 0 },
    { /*  6 */  3, 4 },
    { /*  7 */  4, 5 },
    { /*  8 */  5, 6 },
    { /*  9 */  61, 0 },
    { /* 10 */  58, 0 },
    { /* 11 */  62, 0 },
    { /* 12 */  3, 4 },
    { /* 13 */  4, 5 },
    { /* 14 */  5, 6 },
    { /* 15 */  57, 0 },
    { /* 16 */  63, 0 },
    { /* 17 */  4, 5 },
    { /* 18 */  5, 6 },
    { /* 19 */  6, 7 },
    { /* 20 */  7, 8 },
    { /* 21 */  56, 0 },
    { /* 22 */  64, 0 },
    { /* 23 */  55, 0 },
    { /* 24 */  65, 0 },
    { /* 25 */  4, 5 },
    { /* 26 */  5, 6 },
    { /* 27 */  6, 7 },
    { /* 28 */  7, 8 },
    { /* 29 */  66, 0 },
    { /* 30 */  54, 0 },
    { /* 31 */  67, 0 },
    { /* 32 */  5, 6 },
    { /* 33 */  6, 7 },
    { /* 34 */  7, 8 },
    { /* 35 */  8, 9 },
    { /* 36 */  9, 10 },
    { /* 37 */  53, 0 },
    { /* 38 */  68, 0 },
    { /* 39 */  52, 0 },
    { /* 40 */  69, 0 },
    { /* 41 */  51, 0 },
    { /* 42 */  5, 6 },
    { /* 43 */  6, 7 },
    { /* 44 */  7, 8 },
    { /* 45 */  8, 9 },
    { /* 46 */  9, 10 },
    { /* 47 */  70, 0 },
    { /* 48 */  50, 0 },
    { /* 49 */  49, 0 },
    { /* 50 */  71, 0 },
    { /* 51 */  6, 7 },
    { /* 52 */  7, 8 },
    { /* 53 */  8, 9 },
    { /* 54 */  9, 10 },
    { /* 55 */  10, 11 },
    { /* 56 */  11, 12 },
    { /* 57 */  72, 0 },
    { /* 58 */  48, 0 },
    { /* 59 */  73, 0 },
    { /* 60 */  47, 0 },
    { /* 61 */  74, 0 },
    { /* 62 */  46, 0 },
    { /* 63 */  6, 7 },
    { /* 64 */  7, 8 },
    { /* 65 */  8, 9 },
    { /* 66 */  9, 10 },
    { /* 67 */  10, 11 },
    { /* 68 */  11, 12 },
    { /* 69 */  76, 0 },
    { /* 70 */  75, 0 },
    { /* 71 */  77, 0 },
    { /* 72 */  78, 0 },
    { /* 73 */  45, 0 },
    { /* 74 */  43, 0 },
    { /* 75 */  6, 7 },
    { /* 76 */  7, 8 },
    { /* 77 */  8, 9 },
    { /* 78 */  9, 10 },
    { /* 79 */  10, 11 },
    { /* 80 */  11, 12 },
    { /* 81 */  44, 0 },
    { /* 82 */  79, 0 },
    { /* 83 */  42, 0 },
    { /* 84 */  41, 0 },
    { /* 85 */  80, 0 },
    { /* 86 */  40, 0 },
    { /* 87 */  6, 7 },
    { /* 88 */  7, 8 },
    { /* 89 */  8, 9 },
    { /* 90 */  9, 10 },
    { /* 91 */  10, 11 },
    { /* 92 */  11, 12 },
    { /* 93 */  81, 0 },
    { /* 94 */  39, 0 },
    { /* 95 */  82, 0 },
    { /* 96 */  38, 0 },
    { /* 97 */  83, 0 },
    { /* 98 */  7, 8 },
    { /* 99 */  8, 9 },
    { /* 00 */  9, 10 },
    { /* 01 */  10, 11 },
    { /* 02 */  11, 12 },
    { /* 03 */  12, 13 },
    { /* 04 */  13, 14 },
    { /* 05 */  37, 0 },
    { /* 06 */  35, 0 },
    { /* 07 */  85, 0 },
    { /* 08 */  33, 0 },
    { /* 09 */  36, 0 },
    { /* 10 */  34, 0 },
    { /* 11 */  84, 0 },
    { /* 12 */  32, 0 },
    { /* 13 */  6, 7 },
    { /* 14 */  7, 8 },
    { /* 15 */  8, 9 },
    { /* 16 */  9, 10 },
    { /* 17 */  10, 11 },
    { /* 18 */  11, 12 },
    { /* 19 */  87, 0 },
    { /* 20 */  89, 0 },
    { /* 21 */  30, 0 },
    { /* 22 */  31, 0 },
    { /* 23 */  8, 9 },
    { /* 24 */  9, 10 },
    { /* 25 */  10, 11 },
    { /* 26 */  11, 12 },
    { /* 27 */  12, 13 },
    { /* 28 */  13, 14 },
    { /* 29 */  14, 15 },
    { /* 30 */  15, 16 },
    { /* 31 */  86, 0 },
    { /* 32 */  29, 0 },
    { /* 33 */  26, 0 },
    { /* 34 */  27, 0 },
    { /* 35 */  28, 0 },
    { /* 36 */  24, 0 },
    { /* 37 */  88, 0 },
    { /* 38 */  9, 10 },
    { /* 39 */  10, 11 },
    { /* 40 */  11, 12 },
    { /* 41 */  12, 13 },
    { /* 42 */  13, 14 },
    { /* 43 */  14, 15 },
    { /* 44 */  15, 16 },
    { /* 45 */  16, 17 },
    { /* 46 */  17, 18 },
    { /* 47 */  25, 0 },
    { /* 48 */  22, 0 },
    { /* 49 */  23, 0 },
    { /* 50 */  15, 16 },
    { /* 51 */  16, 17 },
    { /* 52 */  17, 18 },
    { /* 53 */  18, 19 },
    { /* 54 */  19, 20 },
    { /* 55 */  20, 21 },
    { /* 56 */  21, 22 },
    { /* 57 */  22, 23 },
    { /* 58 */  23, 24 },
    { /* 59 */  24, 25 },
    { /* 60 */  25, 26 },
    { /* 61 */  26, 27 },
    { /* 62 */  27, 28 },
    { /* 63 */  28, 29 },
    { /* 64 */  29, 30 },
    { /* 65 */  90, 0 },
    { /* 66 */  21, 0 },
    { /* 67 */  19, 0 },
    { /* 68 */   3, 0 },
    { /* 69 */   1, 0 },
    { /* 70 */   2, 0 },
    { /* 71 */   0, 0 },
    { /* 72 */  23, 24 },
    { /* 73 */  24, 25 },
    { /* 74 */  25, 26 },
    { /* 75 */  26, 27 },
    { /* 76 */  27, 28 },
    { /* 77 */  28, 29 },
    { /* 78 */  29, 30 },
    { /* 79 */  30, 31 },
    { /* 80 */  31, 32 },
    { /* 81 */  32, 33 },
    { /* 82 */  33, 34 },
    { /* 83 */  34, 35 },
    { /* 84 */  35, 36 },
    { /* 85 */  36, 37 },
    { /* 86 */  37, 38 },
    { /* 87 */  38, 39 },
    { /* 88 */  39, 40 },
    { /* 89 */  40, 41 },
    { /* 90 */  41, 42 },
    { /* 91 */  42, 43 },
    { /* 92 */  43, 44 },
    { /* 93 */  44, 45 },
    { /* 94 */  45, 46 },
    { /* 95 */   98, 0 },
    { /* 96 */   99, 0 },
    { /* 97 */  100, 0 },
    { /* 98 */  101, 0 },
    { /* 99 */  102, 0 },
    { /* 00 */  117, 0 },
    { /* 01 */   97, 0 },
    { /* 02 */   91, 0 },
    { /* 03 */   92, 0 },
    { /* 04 */   93, 0 },
    { /* 05 */   94, 0 },
    { /* 06 */   95, 0 },
    { /* 07 */   96, 0 },
    { /* 08 */  104, 0 },
    { /* 09 */  111, 0 },
    { /* 10 */  112, 0 },
    { /* 11 */  113, 0 },
    { /* 12 */  114, 0 },
    { /* 13 */  115, 0 },
    { /* 14 */  116, 0 },
    { /* 15 */  110, 0 },
    { /* 16 */  105, 0 },
    { /* 17 */  106, 0 },
    { /* 18 */  107, 0 },
    { /* 19 */  108, 0 },
    { /* 20 */  109, 0 },
    { /* 21 */  118, 0 },
    { /* 22 */    6, 0 },
    { /* 23 */    8, 0 },
    { /* 24 */    9, 0 },
    { /* 25 */   10, 0 },
    { /* 26 */    5, 0 },
    { /* 27 */  103, 0 },
    { /* 28 */  120, 0 },
    { /* 29 */  119, 0 },
    { /* 30 */    4, 0 },
    { /* 31 */    7, 0 },
    { /* 32 */   15, 0 },
    { /* 33 */   16, 0 },
    { /* 34 */   18, 0 },
    { /* 35 */   20, 0 },
    { /* 36 */   17, 0 },
    { /* 37 */   11, 0 },
    { /* 38 */   12, 0 },
    { /* 39 */   14, 0 },
    { /* 40 */   13, 0 }
};
