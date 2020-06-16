/* ===================================================================== *
 *   _|_                                                                 *
 *  (E|3)   r1b.h                                                        *
 *   v v                                                                 *
 * A thermal-printer-oriented, 1 bit graphics renderer for 2D and 3D     *
 * A Header-only C99 library                                             *
 * MIT LICENSE     (c) Lingdong Huang 2020                               *
 * ===================================================================== */

#ifndef R1B_HDR
#define R1B_HDR

// ---------------
// CONFIGS
// ---------------

#ifndef R1B_CONFIG_LINE3D_EPSILON
  #define R1B_CONFIG_LINE3D_EPSILON 0.015
#endif

#ifndef R1B_CONFIG_UP2X_FLOAT_EPSILON
  #define R1B_CONFIG_UP2X_FLOAT_EPSILON 0.1
#endif

#ifndef R1B_CONFIG_STBI_PATH
  #define R1B_CONFIG_STBI_PATH "external/stb_image.h"
#endif

#ifndef R1B_CONFIG_STBIW_PATH
  #define R1B_CONFIG_STBIW_PATH "external/stb_image_write.h"
#endif

// ---------------
// MORE CONFIGS
// ---------------
// R1B_CONFIG_NO_FG8X12
// R1B_CONFIG_NO_STBI

#define _GNU_SOURCE // for getline
// TODO: cvsweb.netbsd.org/bsdweb.cgi/pkgsrc/pkgtools/libnbcompat/files/getdelim.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define STB_IMAGE_IMPLEMENTATION
#include R1B_CONFIG_STBI_PATH

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include R1B_CONFIG_STBIW_PATH


// ---------------
// ENUMS
// ---------------

#define R1B_INFER         -42

#define R1B_DTHR_ORD       1
#define R1B_DTHR_FS        2

#define R1B_SMPL_NN        11
#define R1B_SMPL_BILINEAR  12

#define R1B_BRDR_COPY      21
#define R1B_BRDR_ZERO      22
#define R1B_BRDR_NONE      23
#define R1B_BRDR_WRAP      24

#define R1B_FONT_HEX       31

#define R1B_BLIT_OR        41
#define R1B_BLIT_ADD       42
#define R1B_BLIT_FLIP      43
#define R1B_BLIT_SET       44

#define R1B_POLY_CONVEX    51
#define R1B_POLY_CONCAVE   52

#define R1B_WIRE_NONE      61
#define R1B_WIRE_FRONT     62
#define R1B_WIRE_ALL       63

#define R1B_SHDR_NONE      70
#define R1B_SHDR_FLAT      71
#define R1B_SHDR_NDOTL     72
#define R1B_SHDR_NDOTLF    73

#define R1B_UP2X_SAA5050   81
#define R1B_UP2X_EPX       82
#define R1B_UP2X_EAGLE     83
#define R1B_UP2X_HQX       84

#define R1B_KERN_ELLIPSE   91
#define R1B_KERN_GAUSS     92
#define R1B_KERN_GAUSS1D   93
#define R1B_KERN_CROSS     94
#define R1B_KERN_RECT      95

#define R1B_BLUR_GAUSS     111
#define R1B_BLUR_BOX       112

#define R1B_FLAG_SORTED    1


/** 
 * @brief datatype for a (1-channel grayscale or binary) image
 */
typedef struct {
  int w;        /**< width  */
  int h;        /**< height */
  float* data;  /**< image data: row-major array of floats */
} r1b_im_t;

/** 
 * @brief datatype for a bitmap font                           
 */
typedef struct {
  int h;             /**< height of font */
  char* glyphs;      /**< number of glyphs */     
  int n;             /**< pointer to data for glyphs */     
  uint32_t* offsets; /**< array of data offsets for each glyph  */
  uint8_t*  sizes;   /**< array of sizes (width/4) for each glyph  */ 
  uint16_t* cmap;    /**< array of unicode code points for each glyph */  
  int flags;         /**< bitwise OR of flags:
                            R1B_FLAG_SORTED: whether the glyphs are sorted by codepoint
                      */
} r1b_font_t;

/** 
 * @brief datatype for a 3D mesh
 */
typedef struct {
  float* X;     /**< array of x coordinate of vertices */
  float* Y;     /**< array of y coordinate of vertices */
  float* Z;     /**< array of z coordinate of vertices */
  int* tris;    /**< array of triangles (using vertex index) */
  float* norms; /**< array of vertex normals (optional, can be NULL) */
  int n_vtx;    /**< number of vertices */
  int n_tri;    /**< number of triangles */
} r1b_mesh_t;

static const float r1b_dither_ord_idx[16] = {
  0.0/16.0,8.0/16.0,2.0/16.0,10.0/16.0,
  12.0/16.0,4.0/16.0,14.0/16.0,6.0/16.0,
  3.0/16.0,11.0/16.0,1.0/16.0,9.0/16.0,
  15.0/16.0,7.0/16.0,13.0/16.0,5.0/16.0};

#define R1B_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define R1B_MIN(x, y) (((x) < (y)) ? (x) : (y))

static float r1b_pttn_data_SOLID[] = {1};
static float r1b_pttn_data_GRAY5[] = {1,1,0,1,  1,1,1,1,  0,1,1,1,  1,1,1,1,  };
static float r1b_pttn_data_GRAY4[] = {1,1,0,1,  0,1,1,1,  1,1,0,1,  0,1,1,1,  };
static float r1b_pttn_data_GRAY3[] = {1,0,  0,1,  };
static float r1b_pttn_data_GRAY2[] = {0,0,1,0,  1,0,0,0,  0,0,1,0,  1,0,0,0,  };
static float r1b_pttn_data_GRAY1[] = {0,0,1,0,  0,0,0,0,  1,0,0,0,  0,0,0,0,  };
static float r1b_pttn_data_EMPTY[] = {0};
static float r1b_pttn_data_GRID1[] = {0,1,  1,1,  };
static float r1b_pttn_data_GRID2[] = {0,0,0,1,  0,0,0,1,  0,0,0,1,  1,1,1,1,  };
static float r1b_pttn_data_DOTS1[] = {1,0,  0,0,  };
static float r1b_pttn_data_DOTS2[] = {1,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  };
static float r1b_pttn_data_DOTSR[] = {0,0,0,0,0,1,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,1,0,0,0,0,0,0,0,0,0,1,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,1,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,1,0,0,0,0,0,1,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,1,0,0,0,0,0,0,1,0,0,  };
static float r1b_pttn_data_HRZL1[] = {1,  0,  };
static float r1b_pttn_data_VRTL1[] = {1,0,  };
static float r1b_pttn_data_HRZL2[] = {1,  0,  0,  0,  };
static float r1b_pttn_data_VRTL2[] = {1,0,0,0,  };
static float r1b_pttn_data_DGNLL[] = {0,0,0,1,  0,0,1,0,  0,1,0,0,  1,0,0,0,  };
static float r1b_pttn_data_DGNLR[] = {1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1,  };
static float r1b_pttn_data_CROSS[] = {1,0,0,0,  0,1,0,1,  0,0,1,0,  0,1,0,1,  };
static float r1b_pttn_data_BRICK[] = {1,1,1,1,1,1,1,1,  0,0,0,0,1,0,0,0,  0,0,0,0,1,0,0,0,  0,0,0,0,1,0,0,0,  1,1,1,1,1,1,1,1,  1,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,  };
static float r1b_pttn_data_SCALE[] = {0,0,0,0,1,0,0,0,  0,0,0,1,0,1,0,0,  1,1,1,0,0,0,1,1,  1,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,  0,1,0,0,0,0,0,1,  0,0,1,1,1,1,1,0,  0,0,0,0,1,0,0,0,  };
static float r1b_pttn_data_WAVES[] = {0,0,0,0,0,0,1,0,  0,0,0,0,0,1,0,1,  1,0,0,0,1,0,0,0,  1,0,0,0,1,0,0,0,  1,0,0,0,1,0,0,0,  1,0,0,0,1,0,0,0,  0,1,0,1,0,0,0,0,  0,0,1,0,0,0,0,0,  };
static float r1b_pttn_data_CHESS[] = {1,1,0,0,  1,1,0,0,  0,0,1,1,  0,0,1,1,  };
static float r1b_pttn_data_DMOND[] = {0,0,0,0,1,0,0,0,  0,0,0,1,0,1,0,0,  0,0,1,0,1,0,1,0,  0,1,0,1,0,1,0,1,  0,0,1,0,1,0,1,0,  0,0,0,1,0,1,0,0,  0,0,0,0,1,0,0,0,  0,0,0,0,0,0,0,0,  };

static const int r1b_pttn_w_SOLID = 1; static const int r1b_pttn_h_SOLID = 1;
static const int r1b_pttn_w_GRAY5 = 4; static const int r1b_pttn_h_GRAY5 = 4;
static const int r1b_pttn_w_GRAY4 = 4; static const int r1b_pttn_h_GRAY4 = 4;
static const int r1b_pttn_w_GRAY3 = 2; static const int r1b_pttn_h_GRAY3 = 2;
static const int r1b_pttn_w_GRAY2 = 4; static const int r1b_pttn_h_GRAY2 = 4;
static const int r1b_pttn_w_GRAY1 = 4; static const int r1b_pttn_h_GRAY1 = 4;
static const int r1b_pttn_w_EMPTY = 1; static const int r1b_pttn_h_EMPTY = 1;
static const int r1b_pttn_w_GRID1 = 2; static const int r1b_pttn_h_GRID1 = 2;
static const int r1b_pttn_w_GRID2 = 4; static const int r1b_pttn_h_GRID2 = 4;
static const int r1b_pttn_w_DOTS1 = 2; static const int r1b_pttn_h_DOTS1 = 2;
static const int r1b_pttn_w_DOTS2 = 4; static const int r1b_pttn_h_DOTS2 = 4;
static const int r1b_pttn_w_DOTSR =12; static const int r1b_pttn_h_DOTSR =12;
static const int r1b_pttn_w_HRZL1 = 1; static const int r1b_pttn_h_HRZL1 = 2;
static const int r1b_pttn_w_VRTL1 = 2; static const int r1b_pttn_h_VRTL1 = 1;
static const int r1b_pttn_w_HRZL2 = 1; static const int r1b_pttn_h_HRZL2 = 4;
static const int r1b_pttn_w_VRTL2 = 4; static const int r1b_pttn_h_VRTL2 = 1;
static const int r1b_pttn_w_DGNLL = 4; static const int r1b_pttn_h_DGNLL = 4;
static const int r1b_pttn_w_DGNLR = 4; static const int r1b_pttn_h_DGNLR = 4;
static const int r1b_pttn_w_CROSS = 4; static const int r1b_pttn_h_CROSS = 4;
static const int r1b_pttn_w_BRICK = 8; static const int r1b_pttn_h_BRICK = 8;
static const int r1b_pttn_w_SCALE = 8; static const int r1b_pttn_h_SCALE = 8;
static const int r1b_pttn_w_WAVES = 8; static const int r1b_pttn_h_WAVES = 8;
static const int r1b_pttn_w_CHESS = 4; static const int r1b_pttn_h_CHESS = 4;
static const int r1b_pttn_w_DMOND = 8; static const int r1b_pttn_h_DMOND = 8;

r1b_im_t* r1b_pttn_SOLID = NULL; r1b_im_t* r1b_pttn_GRAY5 = NULL;
r1b_im_t* r1b_pttn_GRAY4 = NULL; r1b_im_t* r1b_pttn_GRAY3 = NULL;
r1b_im_t* r1b_pttn_GRAY2 = NULL; r1b_im_t* r1b_pttn_GRAY1 = NULL;
r1b_im_t* r1b_pttn_EMPTY = NULL; r1b_im_t* r1b_pttn_GRID1 = NULL;
r1b_im_t* r1b_pttn_GRID2 = NULL; r1b_im_t* r1b_pttn_DOTS1 = NULL;
r1b_im_t* r1b_pttn_DOTS2 = NULL; r1b_im_t* r1b_pttn_DOTSR = NULL;
r1b_im_t* r1b_pttn_HRZL1 = NULL; r1b_im_t* r1b_pttn_VRTL1 = NULL;
r1b_im_t* r1b_pttn_HRZL2 = NULL; r1b_im_t* r1b_pttn_VRTL2 = NULL;
r1b_im_t* r1b_pttn_DGNLL = NULL; r1b_im_t* r1b_pttn_DGNLR = NULL;
r1b_im_t* r1b_pttn_CROSS = NULL; r1b_im_t* r1b_pttn_BRICK = NULL;
r1b_im_t* r1b_pttn_SCALE = NULL; r1b_im_t* r1b_pttn_WAVES = NULL;
r1b_im_t* r1b_pttn_CHESS = NULL; r1b_im_t* r1b_pttn_DMOND = NULL;

#define R1B_PATTERN(x) \
  ((r1b_pttn_ ## x) ? (r1b_pttn_ ## x) : (\
    r1b_pttn_ ## x = (r1b_im_t*)malloc(sizeof(r1b_im_t)),\
    r1b_pttn_ ## x -> data = r1b_pttn_data_ ## x,\
    r1b_pttn_ ## x -> w = r1b_pttn_w_ ## x,\
    r1b_pttn_ ## x -> h = r1b_pttn_h_ ## x,\
    r1b_pttn_ ## x \
  ))

#define R1B_DESTROY_PATTERN(x) if (r1b_pttn_ ## x) {free(r1b_pttn_ ## x); r1b_pttn_ ## x = NULL;};

#ifndef R1B_CONFIG_NO_FG8X12
  // converted from freeglut/freeglut_font_data.c
  // ==============================================================
  // this license below is from freeGlut, (freeglut_font_data.c)

  /*
   * The legal status of this file is a bit vague.  The font glyphs
   * themselves come from XFree86 v4.3.0 (as of this writing), and as
   * part of the X server may be subject to the XFree86 copyrights.
   * The original freeglut fonts were extracted by a utility written
   * by Pawel W. Olszta (see below) and the generated fonts contained
   * his copyright exclusively.  Steve Baker asserts that Pawel
   * assigned intellectual property rights to Steve Baker.  Steve
   * Baker also asserts that fonts cannot be copyrighted.  He has
   * neither stripped the copyright from the freeglut fonts nor
   * formally retitled anything in his name.  Since that time, the
   * OpenGLUT project has branched from freeglut, and has made
   * necessary modifications to Pawel's ``genfonts'' utility.
   * To that extent, OpenGLUT may have some title to this file.
   * What is fairly clear is that the font data is licensed under
   * the XFree86 license (which is variously termed ``XFree'' and
   * ``MIT'' by the freeglut project).  It is believed that all
   * title holders wish this file to be as useful as possible, and
   * that either the ``XFree'' or ``MIT'' license works.
   *
   * Portions copyright (c) 2004, the OpenGLUT project contributors.
   * OpenGLUT branched from freeglut in February, 2004.
   *
   * Copyright (c) 1999-2000 by Pawel W. Olszta
   * Written by Pawel W. Olszta, <olszta@sourceforge.net>
   * 
   * Permission is hereby granted, free of charge, to any person obtaining a
   * copy of this software and associated documentation files (the "Software"),
   * to deal in the Software without restriction, including without limitation
   * the rights to use, copy, modify, merge, publish, distribute, sublicense,
   * and/or sell copies of the Software, and to permit persons to whom the
   * Software is furnished to do so, subject to the following conditions:
   *
   * The above copyright notice and this permission notice shall be included
   * in all copies or substantial portions of the Sotware.
   */
  // ==============================================================
  static char     R1B_FG8X12_GLYPHS [] = {0,0,0,0,0,0,0,0,0,0,0,0,0,16,16,16,16,16,16,16,0,16,0,0,0,36,36,36,0,0,0,0,0,0,0,0,0,0,36,36,126,36,126,36,36,0,0,0,0,16,60,80,80,56,20,20,120,16,0,0,0,34,82,36,8,8,16,36,42,68,0,0,0,0,0,48,72,72,48,74,68,58,0,0,0,56,48,64,0,0,0,0,0,0,0,0,0,4,8,8,16,16,16,8,8,4,0,0,0,32,16,16,8,8,8,16,16,32,0,0,0,0,0,36,24,126,24,36,0,0,0,0,0,0,0,16,16,124,16,16,0,0,0,0,0,0,0,0,0,0,0,0,56,48,64,0,0,0,0,0,0,126,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,56,16,0,0,2,2,4,8,16,32,64,128,128,0,0,0,24,36,66,66,66,66,66,36,24,0,0,0,16,48,80,16,16,16,16,16,124,0,0,0,60,66,66,2,4,24,32,64,126,0,0,0,126,2,4,8,28,2,2,66,60,0,0,0,4,12,20,36,68,68,126,4,4,0,0,0,126,64,64,92,98,2,2,66,60,0,0,0,28,32,64,64,92,98,66,66,60,0,0,0,126,2,4,8,8,16,16,32,32,0,0,0,60,66,66,66,60,66,66,66,60,0,0,0,60,66,66,70,58,2,2,4,56,0,0,0,0,0,16,56,16,0,0,16,56,16,0,0,0,0,16,56,16,0,0,56,48,64,0,0,2,4,8,16,32,16,8,4,2,0,0,0,0,0,0,126,0,0,126,0,0,0,0,0,64,32,16,8,4,8,16,32,64,0,0,0,60,66,66,2,4,8,8,0,8,0,0,0,60,66,66,78,82,86,74,64,60,0,0,0,24,36,66,66,66,126,66,66,66,0,0,0,252,66,66,66,124,66,66,66,252,0,0,0,60,66,64,64,64,64,64,66,60,0,0,0,252,66,66,66,66,66,66,66,252,0,0,0,126,64,64,64,120,64,64,64,126,0,0,0,126,64,64,64,120,64,64,64,64,0,0,0,60,66,64,64,64,78,66,70,58,0,0,0,66,66,66,66,126,66,66,66,66,0,0,0,124,16,16,16,16,16,16,16,124,0,0,0,31,4,4,4,4,4,4,68,56,0,0,0,66,68,72,80,96,80,72,68,66,0,0,0,64,64,64,64,64,64,64,64,126,0,0,0,130,130,198,170,146,146,130,130,130,0,0,0,66,66,98,82,74,70,66,66,66,0,0,0,60,66,66,66,66,66,66,66,60,0,0,0,124,66,66,66,124,64,64,64,64,0,0,0,60,66,66,66,66,66,82,74,60,2,0,0,124,66,66,66,124,80,72,68,66,0,0,0,60,66,64,64,60,2,2,66,60,0,0,0,254,16,16,16,16,16,16,16,16,0,0,0,66,66,66,66,66,66,66,66,60,0,0,0,130,130,68,68,68,40,40,40,16,0,0,0,130,130,130,130,146,146,146,170,68,0,0,0,130,130,68,40,16,40,68,130,130,0,0,0,130,130,68,40,16,16,16,16,16,0,0,0,126,2,4,8,16,32,64,64,126,0,0,0,60,32,32,32,32,32,32,32,60,0,0,0,128,128,64,32,16,8,4,2,2,0,0,0,120,8,8,8,8,8,8,8,120,0,0,0,16,40,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,254,0,0,56,24,4,0,0,0,0,0,0,0,0,0,0,0,0,60,2,62,66,70,58,0,0,0,64,64,64,92,98,66,66,98,92,0,0,0,0,0,0,60,66,64,64,66,60,0,0,0,2,2,2,58,70,66,66,70,58,0,0,0,0,0,0,60,66,126,64,66,60,0,0,0,28,34,32,32,124,32,32,32,32,0,0,0,0,0,0,58,68,68,56,64,60,66,60,0,64,64,64,92,98,66,66,66,66,0,0,0,0,16,0,48,16,16,16,16,124,0,0,0,0,4,0,12,4,4,4,4,68,68,56,0,64,64,64,68,72,112,72,68,66,0,0,0,48,16,16,16,16,16,16,16,124,0,0,0,0,0,0,236,146,146,146,146,130,0,0,0,0,0,0,92,98,66,66,66,66,0,0,0,0,0,0,60,66,66,66,66,60,0,0,0,0,0,0,92,98,66,98,92,64,64,64,0,0,0,0,58,70,66,70,58,2,2,2,0,0,0,0,92,34,32,32,32,32,0,0,0,0,0,0,60,66,48,12,66,60,0,0,0,0,32,32,124,32,32,32,34,28,0,0,0,0,0,0,68,68,68,68,68,58,0,0,0,0,0,0,68,68,68,40,40,16,0,0,0,0,0,0,130,130,146,146,170,68,0,0,0,0,0,0,66,36,24,24,36,66,0,0,0,0,0,0,66,66,66,70,58,2,66,60,0,0,0,0,126,4,8,16,32,126,0,0,0,14,16,16,8,48,8,16,16,14,0,0,0,16,16,16,16,16,16,16,16,16,0,0,0,112,8,8,16,12,16,8,8,112,0,0,0,36,84,72,0,0,0,0,0,0,0,0};
  static uint32_t R1B_FG8X12_OFFSETS[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188 };
  static uint8_t  R1B_FG8X12_SIZES  [] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
  static uint16_t R1B_FG8X12_CMAP   [] = {32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126};
  r1b_font_t* r1b_font_fg8x12 = NULL;

  #define R1B_FONT_FG8X12\
    ((r1b_font_fg8x12) ? (r1b_font_fg8x12) : (\
      r1b_font_fg8x12 = (r1b_font_t*)malloc(sizeof(r1b_font_t)),\
      r1b_font_fg8x12 -> glyphs = R1B_FG8X12_GLYPHS ,\
      r1b_font_fg8x12 -> offsets= R1B_FG8X12_OFFSETS,\
      r1b_font_fg8x12 -> sizes  = R1B_FG8X12_SIZES  ,\
      r1b_font_fg8x12 -> cmap   = R1B_FG8X12_CMAP   ,\
      r1b_font_fg8x12 -> flags  = R1B_FLAG_SORTED   ,\
      r1b_font_fg8x12 -> h = 12,\
      r1b_font_fg8x12 -> n = 95,\
      r1b_font_fg8x12 \
    ))

    // non-macro wrapper for swig etc.
    r1b_font_t* r1b_get_font_fg8x12(){{
      return R1B_FONT_FG8X12;
    }}

#endif /*R1B_CONFIG_NO_FG8X12*/

float* r1b_tmp0 = NULL;
int r1b_tmp0_size = 0;

float* r1b_tmp1 = NULL;
int r1b_tmp1_size = 0;

/**
 * @brief (internal use) allocate temporary buffer for certain operations
 * @param w  width
 * @param h  height
 */
void r1b_make_tmp0(int w, int h){
  int l = w*h;
  if (!r1b_tmp0){
    r1b_tmp0_size = l;
    r1b_tmp0 = (float*)malloc(r1b_tmp0_size*sizeof(float));
  }else if (r1b_tmp0_size < l){
    r1b_tmp0_size = l;
    r1b_tmp0 = (float*)realloc(r1b_tmp0, r1b_tmp0_size*sizeof(float));
  }
}

/**
 * @brief (internal use) allocate temporary buffer for certain operations
 * @param w  width
 * @param h  height
 */
void r1b_make_tmp1(int w, int h){
  int l = w*h;
  if (!r1b_tmp1){
    r1b_tmp1_size = l;
    r1b_tmp1 = (float*)malloc(r1b_tmp1_size*sizeof(float));
  }else if (r1b_tmp1_size < l){
    r1b_tmp1_size = l;
    r1b_tmp1 = (float*)realloc(r1b_tmp1, r1b_tmp1_size*sizeof(float));
  }
}

/**
 * @brief free all resources allocated internally by the library
 * @param w  width
 * @param h  height
 */
void r1b_cleanup(){
  if (r1b_tmp0){
    r1b_tmp0_size = 0;
    free(r1b_tmp0);
  }
  if (r1b_tmp1){
    r1b_tmp1_size = 0;
    free(r1b_tmp1);
  }
  #ifndef R1B_CONFIG_NO_FG8X12
    if (r1b_font_fg8x12){
      free(r1b_font_fg8x12);
    }
  #endif
  R1B_DESTROY_PATTERN(SOLID); R1B_DESTROY_PATTERN(GRAY5);
  R1B_DESTROY_PATTERN(GRAY4); R1B_DESTROY_PATTERN(GRAY3);
  R1B_DESTROY_PATTERN(GRAY2); R1B_DESTROY_PATTERN(GRAY1);
  R1B_DESTROY_PATTERN(EMPTY); R1B_DESTROY_PATTERN(GRID1);
  R1B_DESTROY_PATTERN(GRID2); R1B_DESTROY_PATTERN(DOTS1);
  R1B_DESTROY_PATTERN(DOTS2); R1B_DESTROY_PATTERN(DOTSR);
  R1B_DESTROY_PATTERN(HRZL1); R1B_DESTROY_PATTERN(VRTL1);
  R1B_DESTROY_PATTERN(HRZL2); R1B_DESTROY_PATTERN(VRTL2);
  R1B_DESTROY_PATTERN(DGNLL); R1B_DESTROY_PATTERN(DGNLR);
  R1B_DESTROY_PATTERN(CROSS); R1B_DESTROY_PATTERN(BRICK);
  R1B_DESTROY_PATTERN(SCALE); R1B_DESTROY_PATTERN(WAVES);
  R1B_DESTROY_PATTERN(CHESS); R1B_DESTROY_PATTERN(DMOND);
}

#ifndef R1B_CONFIG_NO_STBI
/**
 * @brief read an image from disk as grayscale
 * @param path  the file path
 * @return      an image
 */
r1b_im_t r1b_read(const char* path){  
  int width, height, channels;
  unsigned char *image = stbi_load(path,
                                 &width,
                                 &height,
                                 &channels,
                                 STBI_grey);
  
  float* data = (float*)malloc(width*height*sizeof(float));
  int i; for (i= 0; i < height; i++){
    int j; for (j= 0; j < width; j++){
      data[i*width+j] = 1.0-(float)image[i*width+j]/255.0;
    }
  }
  stbi_image_free(image);
  r1b_im_t im;
  im.w = width;
  im.h = height;
  im.data = data;
  return im;
}
/**
 * @brief write image to file, supported: jpg, png, bmp
 * @param path  the file path
 * @param       im an image
 */
void r1b_snapshot(const char* path, r1b_im_t* im){
  unsigned char *image = (unsigned char*)malloc(sizeof(unsigned char)*im->w*im->h);
  int i; for (i= 0; i < im->h; i++ ){
    int j; for (j= 0; j < im->w; j++ ){
      image[i*im->w+j] = (unsigned char)(int) ((1.0-fmin(fmax(im->data[i*im->w+j],0.0),1.0)) * 255.0);
    }
  }
  char* ext = (char*)path + strlen(path);
  while (ext > (char*)path && *(char*)ext != '.') {
      ext--;
  }
  ext ++;
  if (strcmp(ext,"jpg")==0 || strcmp(ext,"jpeg")==0){
    stbi_write_jpg(path, im->w, im->h, 1, image, 90);
  }else if (strcmp(ext,"png")==0){
    stbi_write_png(path, im->w, im->h, 1, image, im->w);
  }else if (strcmp(ext,"bmp")==0){
    stbi_write_bmp(path, im->w, im->h, 1, image);
  }
}
#endif /*R1B_CONFIG_NO_STBI*/

/**
 * @brief create image filled with zeros
 * @param w  width
 * @param h  height
 * @return   an image
 */
r1b_im_t r1b_zeros(int w, int h){
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)calloc(w*h,sizeof(float));
  return im;
}
/**
 * @brief create image filled with ones
 * @param w  width
 * @param h  height
 * @return   an image
 */
r1b_im_t r1b_ones(int w, int h){
  int l = w*h;
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)malloc(l*sizeof(float));
  int i; for (i= 0; i < l; i++){
    im.data[i] = 1.0;
  }
  return im;
}
/**
 * @brief create image from data pointed by array pointer, copying the data over
 * @param w    width
 * @param h    height
 * @param arr  an array that is at least w x h in size
 * @return     an image
 */
r1b_im_t r1b_from_array(int w, int h, float* arr){
  int l = w*h;
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)malloc(l*sizeof(float));
  memcpy(im.data, arr, l*sizeof(float));
  return im;
}

/**
 * @brief create image filled with FLT_MAX
 * @param w  width
 * @param h  height
 * @return   an image
 */
r1b_im_t r1b_infs(int w, int h){
  int l = w*h;
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)malloc(l*sizeof(float));
  int i; for (i= 0; i < l; i++){
    im.data[i] = FLT_MAX;
  }
  return im;
}

/**
 * @brief free data allocated in an image; does not free the pointer itself
 * @param im  pointer to image
 */
void r1b_free(r1b_im_t* im){
  free(im->data);
  im->data = NULL;
}

/**
 * @brief transpose an image
 * @param im  pointer to image
 */
void r1b_transpose(r1b_im_t* im){
  // TODO: cache friendly
  r1b_make_tmp0(im->w,im->h);
  int i; for (i= 0; i < im->h; i++){
    int j; for (j= 0; j < im->w; j++){
      r1b_tmp0[j*im->h+i] = im->data[i*im->w+j];
    }
  }
  int tmp = im->w;
  im->w = im->h;
  im->h = tmp;
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

/**
 * @brief transpose and flip an image, effectively rotating it by 90 degrees.
 * @param im  pointer to image
 */
void r1b_transpose_flip(r1b_im_t* im){
  // TODO: cache friendly
  r1b_make_tmp0(im->w,im->h);
  int i; for (i= 0; i < im->h; i++){
    int j; for (j= 0; j < im->w; j++){
      r1b_tmp0[j*im->h+i] = im->data[i*im->w+im->w-1-j];
    }
  }
  int tmp = im->w;
  im->w = im->h;
  im->h = tmp;
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

/**
 * @brief normalize an image to a given interval
 * @param im  pointer to image
 * @param lo  new min value
 * @param hi  new max value
 */
void r1b_normalize(r1b_im_t* im, float lo, float hi){
  float m =  FLT_MAX;
  float M = -FLT_MAX;
  int i;
  for (i = 0; i < im->h*im->w; i++){
    if (im->data[i] == FLT_MAX || im->data[i] == -FLT_MAX){
      continue;
    }
    m = fmin(im->data[i],m);
    M = fmax(im->data[i],M);
  }
  float hi_lo = hi - lo;
  for (i = 0; i < im->h*im->w; i++){
    im->data[i] = fmin(fmax( ((im->data[i]-m)/M) * hi_lo + lo  ,lo),hi);
  }
}

/**
 * @brief duplicates an image
 * @param im  pointer to image
 * @return    the clone
 */
r1b_im_t r1b_copy_of(r1b_im_t* im){
  int s = im->w*im->h*sizeof(float);
  r1b_im_t dst;
  dst.w = im->w;
  dst.h = im->h;
  dst.data = (float*)malloc(s);
  memcpy(dst.data, im->data, s);
  return dst;
}

/**
 * @brief copy data from one image to another
 * the images should have the same width, and destination is at least
 * the same height as source
 * @param im   source: pointer to image to be copied from
 * @param dst  destination: pointer to image to be copied into
 */
void r1b_copy_to(r1b_im_t* im, r1b_im_t* dst){
  memcpy(dst->data, im->data, im->w*im->h*sizeof(float));
}

/**
 * @brief (internal use) apply floyd-steinberg dithering to a grayscale image
 * @param im  pointer to image
 */
void r1b_dither_fs(r1b_im_t* im) {
  r1b_make_tmp0(im->w,im->h);
  r1b_make_tmp1(im->w,im->h);

  memset(r1b_tmp1,0,im->w*im->h*sizeof(float));

  int i; for (i= 0; i < im->h; i++) {
    int j; for (j= 0; j < im->w; j++) {
      float o = im->data[i*im->w+j] + r1b_tmp1[i*im->w+j];
      float n = round(o);
      float qe = o - n;

      if(j<im->w-1){         r1b_tmp1[ i   *im->w+ j+1] += qe * 7.0/16.0; }
      if(i<im->h-1){if(j!=0){r1b_tmp1[(i+1)*im->w+ j-1] += qe * 3.0/16.0; }
                             r1b_tmp1[(i+1)*im->w+ j  ] += qe * 5.0/16.0; 
      if(j<im->w-1){         r1b_tmp1[(i+1)*im->w+ j+1] += qe * 1.0/16.0; }}

      r1b_tmp0[i*im->w+j] = n;
    }
  }
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

/**
 * @brief (internal use) apply ordered dithering to a grayscale image
 * @param im  pointer to image
 */
void r1b_dither_ord(r1b_im_t* im){
  r1b_make_tmp0(im->w,im->h);

  int i; for (i= 0; i < im->h; i++ ){
    int j; for (j= 0; j < im->w; j++ ){

      float o = im->data[i*im->w+j];
      float n = round(o);
      float qe = fabs(o - n);
      float d = r1b_dither_ord_idx[(i%4)*4+j%4];
      if (qe < d) {
        r1b_tmp0[i*im->w+j] = n;
      }else{
        r1b_tmp0[i*im->w+j] = 1.0-n;
      }
    }
  }
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

/**
 * @brief apply dithering to a grayscale image
 * turning it into binary image using specified algorithm
 * @param im    pointer to image
 * @param mode  the algorithm to use, either R1B_DTHR_ORD or R1B_DTHR_FS
 */
void r1b_dither(r1b_im_t* im, int mode){
  switch(mode){
    case R1B_DTHR_ORD:
      r1b_dither_ord(im);
      break;
    case R1B_DTHR_FS:
    default:
      r1b_dither_fs(im);
  }
}

/**
 * @brief print an image to stdout for debugging
 * @param im  pointer to image
 */
void r1b_log(r1b_im_t* im){
  int i; for (i= 0; i < im->h; i++) {
    int j; for (j= 0; j < im->w; j++) {
      if (im->data[i*im->w+j]>=0.5){
        printf("* ");
      }else{
        printf("  ");
      }
    }
    printf("\n");
  }
}

#define R1B_PUT8(x) bytes[cnt_bytes] = x; cnt_bytes ++;

/**
 * @brief encode an image to ESC/POS commands
 * @param im               pointer to image
 * @param n_bytes_written  size of the returned buffer in bytes
 * @return                 an array of bytes
 */
char* r1b_encode(r1b_im_t* im, int* n_bytes_written){
  int l0 = im->w%256;
  int ll = (int)(im->w/256);
  int num_bytes = ((im->h+23)/24)*8 + 2 + im->w*3*((im->h+23)/24);
  int cnt_bytes = 0;

  char* bytes = (char*) malloc(sizeof(char)*num_bytes);

  R1B_PUT8(0x1b); R1B_PUT8(0x40);

  int r; for (r= 0; r < im->h; r+= 24){
    //ESC * m nL nH
    R1B_PUT8(0x1b);R1B_PUT8(0x2a);R1B_PUT8(33);R1B_PUT8((char)l0);R1B_PUT8((char)ll);
    int c; for (c= 0; c < im->w; c ++ ){
      int n; for (n= 0; n < 3; n++ ){
        char x = 0;
        int h; for (h= 0; h < 8; h++ ){
          x = x << 1;
          if ( (r+n*8+h)<=im->h-1 && im->data[R1B_MIN(r+n*8+h,im->h-1)*im->w+c]>=0.5 ){
            x = x | 1;
          }
        }
        R1B_PUT8(x);
      }
    }
    R1B_PUT8(0x1b);R1B_PUT8(0x4a);R1B_PUT8(0);
  }
  // printf("%d %d\n",num_bytes,cnt_bytes);
  *n_bytes_written = cnt_bytes;
  return bytes;
}

/**
 * @brief encode an image to ESC/POS commands and write it to a file
 * @param path  file path to write to
 * @param im    pointer to image
 */
void r1b_encode2file(const char* path, r1b_im_t* im){
  FILE * fp;
  fp = fopen(path, "wb");
  int n;
  char* buf = r1b_encode(im,&n);
  fwrite(buf , 1, n, fp);
  fclose(fp);
}

/**
 * @brief send an image to a thermal printer for printing using LPR command
 * @param printer  the name of the printer
 * @param im       pointer to image
 */
void r1b_lpr(const char* printer, r1b_im_t* im){
  char buf[256];
  r1b_encode2file("r1b_tmp",im);
  sprintf(buf,"lpr -P%s -o raw r1b_tmp",printer);
  system(buf);
}

/**
 * @brief (internal use) nearest neighbor resampling
 * @param im  pointer to image
 * @param w   new width
 * @param h   new height
 */
void r1b_resample_nearest(r1b_im_t* im, int w, int h){
  r1b_make_tmp0(w,h);

  float hs = (float)im->h/(float)h;
  float ws = (float)im->w/(float)w;

  int i; for (i= 0; i < h; i++){
    int j; for (j= 0; j < w; j++){
    
      int ii = R1B_MIN( im->h-1, (int)round((float)i*hs) );
      int jj = R1B_MIN( im->w-1, (int)round((float)j*ws) );
      r1b_tmp0[i*w+j] = im->data[ii*im->w+jj];
    }
  }
  // swap
  r1b_tmp0_size = im->w*im->h;
  float* tmp = im->data;

  im->w = w;
  im->h = h;
  im->data = r1b_tmp0;
  r1b_tmp0 = tmp;
}

/**
 * @brief (internal use) bilinear resampling
 * @param im  pointer to image
 * @param w   new width
 * @param h   new height
 */
void r1b_resample_bilinear(r1b_im_t* im, int w, int h){
  r1b_make_tmp0(w,h);

  float hs = (float)im->h/(float)h;
  float ws = (float)im->w/(float)w;

  int i; for (i= 0; i < h; i++){
    int j; for (j= 0; j < w; j++){
    
      float ii = (float)i*hs;
      float jj = (float)j*ws;

      int i0 = (int)ii;
      int i1 = R1B_MIN(im->h-1,(int)ceil(ii));
      int j0 = (int)jj;
      int j1 = R1B_MIN(im->w-1,(int)ceil(jj));

      float it = (float)ii-(float)i0;
      float jt = (float)jj-(float)j0;

      float x00 = im->data[i0*im->w+j0];
      float x01 = im->data[i0*im->w+j1];
      float x10 = im->data[i1*im->w+j0];
      float x11 = im->data[i1*im->w+j1];

      r1b_tmp0[i*w+j] = (x00*(1-jt)+x01*jt)*(1-it)+(x10*(1-jt)+x11*jt)*it;
    }
  }
  // swap
  r1b_tmp0_size = im->w*im->h;
  float* tmp = im->data;

  im->w = w;
  im->h = h;
  im->data = r1b_tmp0;
  r1b_tmp0 = tmp;
}

/**
 * @brief resample image to a different size
 * @param im    pointer to image
 * @param w     new width, pass R1B_INFER to scale proportionally per new height
 * @param h     new height, pass R1B_INFER to scale proportionally per new width
 * @param mode  the alogirthm, either R1B_SMPL_NN or R1B_SMPL_BILINEAR
 */
void r1b_resample(r1b_im_t* im, int w, int h, int mode){
  if (w == R1B_INFER){
    w = (int)round((float)h*(float)(im->w)/(float)(im->h));
  }
  if (h == R1B_INFER){
    h = (int)round((float)w*(float)(im->h)/(float)(im->w));
  }

  switch(mode){
    case R1B_SMPL_BILINEAR:
      r1b_resample_bilinear(im,w,h);
      break;
    case R1B_SMPL_NN:
    default:
      r1b_resample_nearest(im,w,h);
  }
}

/**
 * @brief retrieve the value of a pixel at given coordinate
 * @param im    pointer to image
 * @param x     x coordinate
 * @param y     y coordinate
 * @param mode  border handling when coordinate is outside image:
 *              R1B_BRDR_ZERO: zero padded;
 *              R1B_BRDR_COPY: copy padded;
 *              R1B_BRDR_WRAP: wrap around;
 *              R1B_BRDR_NONE: no boundry checking (expect funny result or segfault when out of range).
 */
float r1b_get(r1b_im_t* im, int x, int y, int mode){
  if (mode == R1B_BRDR_ZERO){
    if (x<  0 || x >= im->w || y < 0 || y >= im->h){
      return 0;
    }
  }else if (mode == R1B_BRDR_COPY){
    x = R1B_MIN(R1B_MAX(x,0),im->w-1);
    y = R1B_MIN(R1B_MAX(y,0),im->h-1);
  }else if (mode == R1B_BRDR_WRAP){
    while (x < 0 && im->w > 0) {
      x += im->w;
    }
    while (y < 0 && im->h > 0) {
      y += im->h;
    }
    x = x % im->w;
    y = y % im->h;
  }
  return im->data[y*im->w+x];
}

/**
 * @brief set the value of a pixel at given coordinate
 * @param im    pointer to image
 * @param x     x coordinate
 * @param y     y coordinate
 * @param val   the value of the pixel
 * @param mode  blit mode, one of:
 *              R1B_BLIT_SET:  overwrite the pixel;
 *              R1B_BLIT_FLIP: flip the value of the pixel;
 *              R1B_BLIT_OR:   turn on the pixel if it's off;
 *              R1B_BLIT_ADD:  add the value to the original.
 */
void r1b_set(r1b_im_t* im, int x, int y, float val, int mode){
  if (x<  0 || x >= im->w || y < 0 || y >= im->h){
    return;
  }
  float o = im->data[y*im->w+x];
  switch (mode) {
  case R1B_BLIT_SET:
    im->data[y*im->w+x] = val;
    break;
  case R1B_BLIT_FLIP:
    if (val > 0.5){
      im->data[y*im->w+x] = 1-o;
    }
    break;
  case R1B_BLIT_OR:
    im->data[y*im->w+x] = fmax(val,o);
    break;
  case R1B_BLIT_ADD:
    im->data[y*im->w+x] = val+o;
    break;
  default:
    im->data[y*im->w+x] = val;
  }
}

/**
 * @brief (internal use) upsample image by 2x using saa5050 algorithm
 * @param im  pointer to image
 */
void r1b_upsample2x_saa5050(r1b_im_t* im){
  //wikipedia.org/wiki/Pixel-art_scaling_algorithms#SAA5050_'diagonal_smoothing'

  r1b_make_tmp0(im->w*2,im->h*2);

  int i; for (i= 0; i < im->h; i++) {
    int _i  = (i-1)*im->w;
    int  i_ = i*im->w;

    int j; for (j= 0; j < im->w; j++) {

      // readable version:
      // int A = 0.5 < r1b_get(im,j-1,i-1,R1B_BRDR_ZERO);
      // int B = 0.5 < r1b_get(im,j,  i-1,R1B_BRDR_ZERO);
      // int C = 0.5 < r1b_get(im,j+1,i-1,R1B_BRDR_ZERO);
      // int D = 0.5 < r1b_get(im,j-1,i,  R1B_BRDR_ZERO);
      // int E = 0.5 < r1b_get(im,j,  i,  R1B_BRDR_ZERO);
      // int F = 0.5 < r1b_get(im,j+1,i,  R1B_BRDR_ZERO);

      int _j  = j-1;
      int  j_ = j+1;

      int bi =  i == 0;
      int bj0 = j == 0;
      int bj1 = j == im->w-1;

      int A = 0.5<((bi||bj0)?0:im->data[_i + _j ]);
      int B = 0.5<((bi)     ?0:im->data[_i +  j ]);
      int C = 0.5<((bi||bj1)?0:im->data[_i +  j_]);
      int D = 0.5<((    bj0)?0:im->data[ i_+ _j ]);
      int E = 0.5<(            im->data[ i_+  j ]);
      int F = 0.5<((    bj1)?0:im->data[ i_+  j_]);

      r1b_tmp0[i*2    *(im->w*2)+j*2  ] = B | (A & E & !B & !D);
      r1b_tmp0[i*2    *(im->w*2)+j*2+1] = B | (C & E & !B & !F);
      r1b_tmp0[(i*2+1)*(im->w*2)+j*2  ] = E | (!A & !E & B & D);
      r1b_tmp0[(i*2+1)*(im->w*2)+j*2+1] = E | (!C & !E & B & F);
    }
  }
  // swap
  r1b_tmp0_size = im->w*im->h;
  float* tmp = im->data;

  im->w *=2;
  im->h *=2;
  im->data = r1b_tmp0;
  r1b_tmp0 = tmp;
}

/**
 * @brief (internal use) upsample image by 2x using EPX algorithm
 * @param im  pointer to image
 */
void r1b_upsample2x_epx(r1b_im_t* im){
  //wikipedia.org/wiki/Pixel-art_scaling_algorithms#EPX
  r1b_make_tmp0(im->w*2,im->h*2);

  float ep = R1B_CONFIG_UP2X_FLOAT_EPSILON;

  int i; for (i= 0; i < im->h; i++) {
    int j; for (j= 0; j < im->w; j++) {
      float P = im->data[i*im->w+j];

      float A = (i==0      )?P:im->data[(i-1)*im->w+j  ];
      float B = (j==im->w-1)?P:im->data[(i  )*im->w+j+1];
      float C = (j==0      )?P:im->data[(i  )*im->w+j-1];
      float D = (i==im->h-1)?P:im->data[(i+1)*im->w+j  ];

      int AeqC = fabs(C-A)<ep;
      int AeqB = fabs(A-B)<ep;
      int CeqD = fabs(D-C)<ep;
      int BeqD = fabs(B-D)<ep;

      r1b_tmp0[ i*2   *(im->w*2)+j*2  ] = (AeqC & (!CeqD) & (!AeqB)) ? A : P;
      r1b_tmp0[ i*2   *(im->w*2)+j*2+1] = (AeqB & (!AeqC) & (!BeqD)) ? B : P;
      r1b_tmp0[(i*2+1)*(im->w*2)+j*2  ] = (CeqD & (!BeqD) & (!AeqC)) ? C : P;
      r1b_tmp0[(i*2+1)*(im->w*2)+j*2+1] = (BeqD & (!AeqB) & (!CeqD)) ? D : P;
    }
  }
  // swap
  r1b_tmp0_size = im->w*im->h;
  float* tmp = im->data;

  im->w *=2;
  im->h *=2;
  im->data = r1b_tmp0;
  r1b_tmp0 = tmp;
}

/**
 * @brief (internal use) upsample image by 2x using Eagle algorithm
 * @param im  pointer to image
 */
void r1b_upsample2x_eagle(r1b_im_t* im){
  //wikipedia.org/wiki/Pixel-art_scaling_algorithms#Eagle
  r1b_make_tmp0(im->w*2,im->h*2);

  float ep = R1B_CONFIG_UP2X_FLOAT_EPSILON;

  int i; for (i= 0; i < im->h; i++) {
    int _i  = (i-1)*im->w;
    int  i_ = (i+1)*im->w;
    int _i_ = i    *im->w;

    int j; for (j= 0; j < im->w; j++) {
      int _j  = j-1;
      int  j_ = j+1;

      int bi0 = i == 0;
      int bi1 = i == im->h-1;
      int bj0 = j == 0;
      int bj1 = j == im->w-1;

      float C =              im->data[_i_+ j ];
      float S = (bi0||bj0)?C:im->data[_i +_j ];
      float T = (bi0)     ?C:im->data[_i + j ];
      float U = (bi0||bj1)?C:im->data[_i + j_];
      float V = (     bj0)?C:im->data[_i_+_j ];
      float W = (     bj1)?C:im->data[_i_+ j_];
      float X = (bi1||bj0)?C:im->data[ i_+_j ];
      float Y = (bi1)     ?C:im->data[ i_+ j ];
      float Z = (bi1||bj1)?C:im->data[ i_+ j_];

      r1b_tmp0[i*2    *(im->w*2)+j*2  ] = (fabs(V-S)<ep && fabs(S-T)<ep) ? S : C;
      r1b_tmp0[i*2    *(im->w*2)+j*2+1] = (fabs(T-U)<ep && fabs(U-W)<ep) ? U : C;
      r1b_tmp0[(i*2+1)*(im->w*2)+j*2  ] = (fabs(V-X)<ep && fabs(X-Y)<ep) ? X : C;
      r1b_tmp0[(i*2+1)*(im->w*2)+j*2+1] = (fabs(W-Z)<ep && fabs(Z-Y)<ep) ? Z : C;
    }
  }
  // swap
  r1b_tmp0_size = im->w*im->h;
  float* tmp = im->data;

  im->w *=2;
  im->h *=2;
  im->data = r1b_tmp0;
  r1b_tmp0 = tmp;
}


// hq2x algorithm
// original public domain c++ version with YUV tables by byuu: 
// http://forums.nesdev.com/viewtopic.php?p=82770#82770 https://pastebin.com/YXpmqvW5
// here modified to work with 1-channel floating points
uint8_t r1b_hq2x_rotate[256] = {0,32,8,40,1,33,9,41,64,96,72,104,65,97,73,105,2,34,10,42,3,35,11,43,66,98,74,106,67,99,75,107,128,160,136,168,129,161,137,169,192,224,200,232,193,225,201,233,130,162,138,170,131,163,139,171,194,226,202,234,195,227,203,235,16,48,24,56,17,49,25,57,80,112,88,120,81,113,89,121,18,50,26,58,19,51,27,59,82,114,90,122,83,115,91,123,144,176,152,184,145,177,153,185,208,240,216,248,209,241,217,249,146,178,154,186,147,179,155,187,210,242,218,250,211,243,219,251,4,36,12,44,5,37,13,45,68,100,76,108,69,101,77,109,6,38,14,46,7,39,15,47,70,102,78,110,71,103,79,111,132,164,140,172,133,165,141,173,196,228,204,236,197,229,205,237,134,166,142,174,135,167,143,175,198,230,206,238,199,231,207,239,20,52,28,60,21,53,29,61,84,116,92,124,85,117,93,125,22,54,30,62,23,55,31,63,86,118,94,126,87,119,95,127,148,180,156,188,149,181,157,189,212,244,220,252,213,245,221,253,150,182,158,190,151,183,159,191,214,246,222,254,215,247,223,255};
uint8_t r1b_hq2x_table [256] = {
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 15, 12, 5,  3, 17, 13,
  4, 4, 6, 18, 4, 4, 6, 18, 5,  3, 12, 12, 5,  3,  1, 12,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 17, 13, 5,  3, 16, 14,
  4, 4, 6, 18, 4, 4, 6, 18, 5,  3, 16, 12, 5,  3,  1, 14,
  4, 4, 6,  2, 4, 4, 6,  2, 5, 19, 12, 12, 5, 19, 16, 12,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 16, 12, 5,  3, 16, 12,
  4, 4, 6,  2, 4, 4, 6,  2, 5, 19,  1, 12, 5, 19,  1, 14,
  4, 4, 6,  2, 4, 4, 6, 18, 5,  3, 16, 12, 5, 19,  1, 14,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 15, 12, 5,  3, 17, 13,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 16, 12, 5,  3, 16, 12,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 17, 13, 5,  3, 16, 14,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 16, 13, 5,  3,  1, 14,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 16, 12, 5,  3, 16, 13,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 16, 12, 5,  3,  1, 12,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3, 16, 12, 5,  3,  1, 14,
  4, 4, 6,  2, 4, 4, 6,  2, 5,  3,  1, 12, 5,  3,  1, 14,
};

#define R1B_HQ2X_BLEND1(A,B  ) (((A)*3 +(B)        )/4 )
#define R1B_HQ2X_BLEND2(A,B,C) (((A)*2 +(B)  +(C)  )/4 )
#define R1B_HQ2X_BLEND3(A,B,C) (((A)*5 +(B)*2+(C)  )/8 )
#define R1B_HQ2X_BLEND4(A,B,C) (((A)*6 +(B)  +(C)  )/8 )
#define R1B_HQ2X_BLEND5(A,B,C) (((A)*2 +(B)*3+(C)*3)/8 )
#define R1B_HQ2X_BLEND6(A,B,C) (((A)*14+(B)  +(C)  )/16)

float r1b_hq2x_blend(unsigned rule, float E, float A, float B, float D, float F, float H) {
  float ep = R1B_CONFIG_UP2X_FLOAT_EPSILON;
  switch(rule) { default:
    case  0: return E;
    case  1: return R1B_HQ2X_BLEND1(E, A   );
    case  2: return R1B_HQ2X_BLEND1(E, D   );
    case  3: return R1B_HQ2X_BLEND1(E, B   );
    case  4: return R1B_HQ2X_BLEND2(E, D, B);
    case  5: return R1B_HQ2X_BLEND2(E, A, B);
    case  6: return R1B_HQ2X_BLEND2(E, A, D);
    case  7: return R1B_HQ2X_BLEND3(E, B, D);
    case  8: return R1B_HQ2X_BLEND3(E, D, B);
    case  9: return R1B_HQ2X_BLEND4(E, D, B);
    case 10: return R1B_HQ2X_BLEND5(E, D, B);
    case 11: return R1B_HQ2X_BLEND6(E, D, B);
    case 12: return (fabs(B-D)<ep) ? R1B_HQ2X_BLEND2(E, D, B) : E;
    case 13: return (fabs(B-D)<ep) ? R1B_HQ2X_BLEND5(E, D, B) : E;
    case 14: return (fabs(B-D)<ep) ? R1B_HQ2X_BLEND6(E, D, B) : E;
    case 15: return (fabs(B-D)<ep) ? R1B_HQ2X_BLEND2(E, D, B) : R1B_HQ2X_BLEND1(E, A);
    case 16: return (fabs(B-D)<ep) ? R1B_HQ2X_BLEND4(E, D, B) : R1B_HQ2X_BLEND1(E, A);
    case 17: return (fabs(B-D)<ep) ? R1B_HQ2X_BLEND5(E, D, B) : R1B_HQ2X_BLEND1(E, A);
    case 18: return (fabs(B-F)<ep) ? R1B_HQ2X_BLEND3(E, B, D) : R1B_HQ2X_BLEND1(E, D);
    case 19: return (fabs(D-H)<ep) ? R1B_HQ2X_BLEND3(E, D, B) : R1B_HQ2X_BLEND1(E, B);
  }
}

/**
 * @brief (internal use) upsample image by 2x using HQX algorithm
 * @param im  pointer to image
 */
void r1b_upsample2x_hqx(r1b_im_t* im){
  r1b_make_tmp0(im->w*2,im->h*2);

  float* input = im->data;
  float* output = r1b_tmp0;
  int width = im->w;
  int height = im->h;
  int outwidth = im->w*2;
  float ep = R1B_CONFIG_UP2X_FLOAT_EPSILON;

  int y; for (y = 0; y < height; y++) {
    const float *in = input + y * width;
    float *out0 = output + y * outwidth * 2;
    float *out1 = output + y * outwidth * 2 + outwidth;

    int prevline = (y == 0 ? 0 : width);
    int nextline = (y == height - 1 ? 0 : width);

    
    *out0++ = *in; *out0++ = *in;
    *out1++ = *in; *out1++ = *in;
    in++;

    int x; for(x = 1; x < width-1; x++) {
      float A = *(in - prevline - 1);
      float B = *(in - prevline + 0);
      float C = *(in - prevline + 1);
      float D = *(in - 1);
      float E = *(in + 0);
      float F = *(in + 1);
      float G = *(in + nextline - 1);
      float H = *(in + nextline + 0);
      float I = *(in + nextline + 1);
      float e = E;

      uint8_t pattern;
      pattern  = (fabs(e - A)>ep) << 0;
      pattern |= (fabs(e - B)>ep) << 1;
      pattern |= (fabs(e - C)>ep) << 2;
      pattern |= (fabs(e - D)>ep) << 3;
      pattern |= (fabs(e - F)>ep) << 4;
      pattern |= (fabs(e - G)>ep) << 5;
      pattern |= (fabs(e - H)>ep) << 6;
      pattern |= (fabs(e - I)>ep) << 7;

      *(out0 + 0) = r1b_hq2x_blend(r1b_hq2x_table[pattern], E, A, B, D, F, H); pattern = r1b_hq2x_rotate[pattern];
      *(out0 + 1) = r1b_hq2x_blend(r1b_hq2x_table[pattern], E, C, F, B, H, D); pattern = r1b_hq2x_rotate[pattern];
      *(out1 + 1) = r1b_hq2x_blend(r1b_hq2x_table[pattern], E, I, H, F, D, B); pattern = r1b_hq2x_rotate[pattern];
      *(out1 + 0) = r1b_hq2x_blend(r1b_hq2x_table[pattern], E, G, D, H, B, F);

      in++;
      out0 += 2;
      out1 += 2;
    }
    
    *out0++ = *in; *out0++ = *in;
    *out1++ = *in; *out1++ = *in;

    in++;
  }

  // swap
  r1b_tmp0_size = im->w*im->h;
  float* tmp = im->data;

  im->w *=2;
  im->h *=2;
  im->data = r1b_tmp0;
  r1b_tmp0 = tmp;

}

/**
 * @brief upsample image by 2x using pixel-art scaling algorithms
 * @param im   pointer to image
 * @param mode algorithm: one of R1B_UP2X_SAA5050, R1B_UP2X_EPX, R1B_UP2X_EAGLE, R1B_UP2X_HQX
 */
void r1b_upsample2x(r1b_im_t* im, int mode){
  switch(mode){
    case R1B_UP2X_SAA5050:
      r1b_upsample2x_saa5050(im);
      break;
    case R1B_UP2X_EAGLE:
      r1b_upsample2x_eagle(im);
      break;
    case R1B_UP2X_HQX:
      r1b_upsample2x_hqx(im);
      break;
    case R1B_UP2X_EPX:
    default:
      r1b_upsample2x_epx(im);
  }
}


/**
 * @brief upsample image by a power of two using bedstead algorithm
 * @param im  pointer to image
 * @param  n  upscale by n-th power of two, e.g. n=3 => upscale by 8x
 */
void r1b_bedstead(r1b_im_t* im, int n){
  // algorithm used by the bedstead font (public domain)
  // basically a nicer saa5050
  // https://bjh21.me.uk/bedstead/
  // https://bjh21.me.uk/bedstead/bedstead.c
  // here modified to work with raster
  int po2 = pow(2,n);
  float w = (float)po2;
  float w4 = w/4;
  float w4w2 = w4+w/2;

  r1b_make_tmp0(im->w*po2,im->h*po2);
  
  int y;for (y = 0; y < im->h; y++) {
    int x;for (x = 0; x < im->w; x++) {
      int L  = 0.5<r1b_get(im,x-1, y  ,R1B_BRDR_ZERO);
      int R  = 0.5<r1b_get(im,x+1, y  ,R1B_BRDR_ZERO);
      int U  = 0.5<r1b_get(im,x, y-1  ,R1B_BRDR_ZERO);
      int D  = 0.5<r1b_get(im,x, y+1  ,R1B_BRDR_ZERO);
      int UL = 0.5<r1b_get(im,x-1, y-1,R1B_BRDR_ZERO);
      int UR = 0.5<r1b_get(im,x+1, y-1,R1B_BRDR_ZERO);
      int DL = 0.5<r1b_get(im,x-1, y+1,R1B_BRDR_ZERO);
      int DR = 0.5<r1b_get(im,x+1, y+1,R1B_BRDR_ZERO);

      int tl, tr, bl, br;

      if (im->data[y*im->w+x]>0.5) {
        /* Assume filled in */
        tl = tr = bl = br = 1;
        /* Check for diagonals */
        if ((UL && !U && !L) || (DR && !D && !R))
          tr = bl = 0;
        if ((UR && !U && !R) || (DL && !D && !L))
          tl = br = 0;
        /* Avoid odd gaps */
        if (L || UL || U) tl = 1;
        if (R || UR || U) tr = 1;
        if (L || DL || D) bl = 1;
        if (R || DR || D) br = 1;
        

        int i;for (i = 0; i < po2; i++){
          int j;for (j = 0; j < po2; j++){
            int ii = y*po2+i;
            int jj = x*po2+j;
            int idx = ii*im->w*po2+jj;
            r1b_tmp0[idx] = 1;
            if (!bl && i >= j+w4w2){
              r1b_tmp0[idx] = 0;
            }
            if (!tr && i+w4w2 <= j){
              r1b_tmp0[idx] = 0;
            }
            if (!tl && po2-i > j+ceil(w4w2)){
              r1b_tmp0[idx] = 0;
            }
            if (!br && po2-i-1+w4w2 <= j){
              r1b_tmp0[idx] = 0;
            }
          }
        }

      } else {
        /* Assume clear */
        tl = tr = bl = br = 0;
        /* white pixel -- just diagonals */
        if (L && U && !UL) tl = 1;
        if (R && U && !UR) tr = 1;
        if (L && D && !DL) bl = 1;
        if (R && D && !DR) br = 1;

        int i;for (i = 0; i < po2; i++){
          int j;for (j = 0; j < po2; j++){
            int ii = y*po2+i;
            int jj = x*po2+j;
            int idx = ii*im->w*po2+jj;
            r1b_tmp0[idx] = 0;
            if (bl && i > j+w4){
              r1b_tmp0[idx] = 1;
            }
            if (tr && i+w4 < j){
              r1b_tmp0[idx] = 1;
            }
            if (tl && po2-i-1 > j+w4){
              r1b_tmp0[idx] = 1;
            }
            if (br && po2-i <= ceil(j-w4)){
              r1b_tmp0[idx] = 1;
            }
          }
        }

      }
      
    }
  }
  // swap
  r1b_tmp0_size = im->w*im->h;
  float* tmp = im->data;

  im->w *=po2;
  im->h *=po2;
  im->data = r1b_tmp0;
  r1b_tmp0 = tmp;
}


#define R1B_PT_IN_PL(x,y,x0,y0,x1,y1) ((((x)-(x0))*((y1)-(y0)) - ((y)-(y0))*((x1)-(x0)))<=0)
#define R1B_PT_IN_TRI(x,y,x0,y0,x1,y1,x2,y2) ( R1B_PT_IN_PL(x,y,x0,y0,x1,y1) && R1B_PT_IN_PL(x,y,x1,y1,x2,y2) && R1B_PT_IN_PL(x,y,x2,y2,x0,y0) )

/**
 * @brief draw a 2D triangle
 * @param im    pointer to image
 * @param x0    x coordinate of first vertex
 * @param y0    y coordinate of first vertex
 * @param x1    x coordinate of second vertex
 * @param y1    y coordinate of second vertex
 * @param x2    x coordinate of third vertex
 * @param y2    y coordinate of third vertex
 * @param pttn  fill pattern
 * @param mode  blit mode, see r1b_set for details
 */
void r1b_triangle(r1b_im_t* im,float x0 ,float y0 ,float x1 ,float y1 ,float x2 ,float y2 , r1b_im_t* pttn, int mode ){

  if (!R1B_PT_IN_PL(x0,y0,x1,y1,x2,y2)){
    float x_tmp = x1;
    float y_tmp = y1;
    x1 = x2;
    y1 = y2;
    x2 = x_tmp;
    y2 = y_tmp;
  }
  int xmin = (int)floor(fmin(fmin(x0,x1),x2));
  int xmax = (int) ceil(fmax(fmax(x0,x1),x2));
  int ymin = (int)floor(fmin(fmin(y0,y1),y2));
  int ymax = (int) ceil(fmax(fmax(y0,y1),y2));

  int y; for (y=ymin; y <= ymax; y++){
    int x; for (x=xmin; x <= xmax; x++){
      if (R1B_PT_IN_TRI((float)x,(float)y,x0,y0,x1,y1,x2,y2)){
        float v = pttn->data[(y % pttn->h) * pttn->w + (x % pttn->w)];
        r1b_set(im,x,y,v,mode);
      }
    }
  }
}

/**
 * @brief draw a 2D rectangle
 * @param im    pointer to image
 * @param x0    left
 * @param y0    top
 * @param x1    right
 * @param y1    bottom
 * @param pttn  fill pattern
 * @param mode  blit mode, see r1b_set for details
 */
void r1b_rect(r1b_im_t* im,float x0 ,float y0 ,float x1 ,float y1 , r1b_im_t* pttn, int mode){
  int xmin = (int)round(fmin(x0,x1));
  int xmax = (int)round(fmax(x0,x1));
  int ymin = (int)round(fmin(y0,y1));
  int ymax = (int)round(fmax(y0,y1));

  int y; for (y=ymin; y <= ymax; y++){
    int x; for (x=xmin; x <= xmax; x++){
      float v = pttn->data[(y % pttn->h) * pttn->w + (x % pttn->w)];
      r1b_set(im,x,y,v,mode);
    }
  }
}

#define R1B_LINE_STEP(sx0,sx1,sy0,sy1,x) (((sx0) == (sx1)) ? (sy1) : ((int)round((float)(sy0)+(float)((x)-(sx0))*(float)((sy1)-(sy0))/(float)((sx1)-(sx0)))) )

/**
 * @brief draw a 2D line
 * @param im    pointer to image
 * @param x0    x coordinate of first point
 * @param y0    y coordinate of first point
 * @param x1    x coordinate of second point
 * @param y1    y coordinate of second point
 * @param val   value (color) of the line
 * @param mode  blit mode, see r1b_set for details
 */
void r1b_line(r1b_im_t* im, float x0 ,float y0 ,float x1 ,float y1, float val, int mode){

  int sx0 = (int)round(x0);
  int sy0 = (int)round(y0);
  int sx1 = (int)round(x1);
  int sy1 = (int)round(y1);
  int dx  = sx1 > sx0 ? 1 : -1; // x increment
  int dy  = sy1 > sy0 ? 1 : -1; // y increment
  
  if (abs(sx0 - sx1) >= abs(sy0 - sy1)){ // slope < 1 ?
    int x = sx0;
    while (x != sx1+dx){
      int y = R1B_LINE_STEP(sx0,sx1,sy0,sy1,x);
      r1b_set(im,x,y,val,mode);
      x += dx;
    }
  }else{
    int y = sy0;
    while (y != sy1+dy){
      int x = R1B_LINE_STEP(sy0,sy1,sx0,sx1,y);
      r1b_set(im,x,y,val,mode);
      y += dy;
    }
  }
}

/**
 * @brief draw a polyline or outline a polygon
 * @param im    pointer to image
 * @param Xs    pointer to array of x-coordinates
 * @param Ys    pointer to array of y-coordinates
 * @param n     number of points
 * @param close true for closed (polygon) or false for open (polyline)
 * @param val   value (color) of the lines
 * @param mode  blit mode, see r1b_set for details
 */
void r1b_lines(r1b_im_t* im, float* Xs, float* Ys, int n, int close, float val, int mode){
  int m = n - 1 + (close & 1);
  int i; for (i=0; i < m; i++ ){
    r1b_line(im, Xs[i], Ys[i], Xs[(i+1)%n], Ys[(i+1)%n], val, mode);
  }
}

/**
 * @brief draw a 2D line with thickness
 * @param im          pointer to image
 * @param x0          x coordinate of first point
 * @param y0          y coordinate of first point
 * @param x1          x coordinate of second point
 * @param y1          y coordinate of second point
 * @param val         value (color) of the line
 * @param half_thick  set thickness of line to half_thick*2+1
 * @param mode        blit mode, see r1b_set for details
 */
void r1b_thick_line(r1b_im_t* im, float x0, float y0, float x1, float y1, float val, int half_thick, int mode){
  int dx = x1 > x0 ? 1 : -1;
  int dy = y1 > y0 ? 1 : -1;
  r1b_line(im,x0,y0,x1,y1,val,mode);

  int i; for (i= 1; i <= half_thick; i++) {
    float dxi = (float)(i*dx);
    float dyi = (float)(i*dy);
    r1b_line(im,x0+dxi,y0,x1,y1-dyi,val,mode);
    r1b_line(im,x0,y0+dyi,x1-dxi,y1,val,mode);
  }
}

/**
 * @brief load a bitmap font in unifont .hex format
 * @param path   file path
 * @param h      height of the font, since the hex format does not store this information
 * @param cp0    unicode code point range start, only glyphs between cp0 and cp1 will be loaded (if any exist) when you don't need the whole set
 * @param cp1    unicode code point range end
 * @param flags  a bitwise OR of flags:
 *               R1B_FLAG_SORTED: set this if the glyphs stored in the file are sorted by unicode code point, which improves speed
 * @return       a font type
 */
r1b_font_t r1b_load_font_hex(const char* path, int h, int cp0, int cp1, int flags) {
  cp0 = R1B_MAX(1,cp0);

  r1b_font_t font;
  font.h = h;
  font.flags = flags;

  FILE * fp;
  char * line = NULL;
  size_t len;
  size_t linelen = 0;
  size_t read;

  fp = fopen(path,"r");

  int n_lines = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    linelen = strlen(line)-1;
    if (linelen < 5){
      continue;
    }
    line[4] = 0;
    int cp = (int)strtol(line, NULL, 16);
    if (cp0 <= cp && cp <= cp1){
      n_lines ++;
    }
  }

  rewind(fp);
  linelen = 0;

  font.n = n_lines;
  font.sizes   = ( uint8_t*)malloc( sizeof(uint8_t)*n_lines);
  font.offsets = (uint32_t*)malloc(sizeof(uint32_t)*n_lines);
  font.cmap    = (uint16_t*)malloc(sizeof(uint16_t)*n_lines);

  int      idx  = 0;
  uint32_t off  = 0;
  uint64_t total= 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    linelen = strlen(line)-1;
    if (linelen < 5){
      continue;
    }
    line[4] = 0;
    int cp = (int)strtol(line, NULL, 16);
    if (cp0 <= cp && cp <= cp1){
      font.sizes[idx] = (linelen-5)/h;
      font.offsets[idx] = off;
      font.cmap[idx] = cp;
      off += font.sizes[idx];
      idx ++;
      total += (linelen-5)/2;
    }
  }

  rewind(fp);
  linelen = 0;

  font.glyphs = (char*)malloc(total);
  idx = 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    linelen = strlen(line)-1;
    if (linelen < 5){
      continue;
    }
    line[4] = 0;
    int cp = (int)strtol(line, NULL, 16);
    if (cp0 <= cp && cp <= cp1){
      int j; for (j= 5; j < linelen; j+=2){
        char buf[3];
        buf[0] = line[j]; buf[1] = line[j+1]; buf[2] = 0;
        unsigned char b = (unsigned char)strtol(buf,NULL,16);
        font.glyphs[font.offsets[idx]*h/2 + (j-5)/2] = b;
      }
      idx ++;
    }
  }

  fclose(fp);

  return font;
}

/**
 * @brief free data allocated in a font
 * @param font  pointer to font
 */
void r1b_destroy_font(r1b_font_t* font){
  if (font->glyphs)free(font->glyphs);
  if (font->sizes)free(font->sizes);
  if (font->cmap)free(font->cmap);
  if (font->offsets)free(font->offsets);
}

/**
 * @brief (internal use) locate a glyph in font by codepoint with linear search
 * @param font  pointer to font
 * @param cp    codepoint
 */
int r1b_glyph_index_lin_search(r1b_font_t* font, int cp){
  int i; for (i= 0; i < font->n; i++){
    if (font->cmap[i] == cp){
      return i;
    }
  }
  return -1;
}

/**
 * @brief (internal use) locate a glyph in font by codepoint with binary search
 * @param font  pointer to font
 * @param cp    codepoint
 * @param i0    the low index
 * @param i1    the high index
 */
int r1b_glyph_index_bin_search(r1b_font_t* font, int cp, int i0, int i1){
  if (i0 == i1){
    return -1;
  }
  int m = (i0+i1)/2;
  if (cp == font->cmap[m]){
    return m;
  }
  if (cp < font->cmap[m]){
    return r1b_glyph_index_bin_search(font,cp,i0,m);
  }else{
    return r1b_glyph_index_bin_search(font,cp,m+1,i1);
  }
}

/**
 * @brief (internal use) locate a glyph in font by codepoint
 * @param font  pointer to font
 * @param cp    codepoint
 */
int r1b_glyph_index(r1b_font_t* font, int cp){
  if (font->flags & R1B_FLAG_SORTED){
    return r1b_glyph_index_bin_search(font, cp, 0, font->n);
  }else{
    return r1b_glyph_index_lin_search(font, cp);
  }
}

/**
 * @brief draw a single unicode character to image
 * @param im    pointer to image
 * @param cp    codepoint
 * @param x     x coordinate
 * @param y     y coordinate
 * @param font  pointer to font
 * @param val   value (color) of the text
 * @param mode  blit mode, see r1b_set
 * @param highlight  boolean: whether to draw a highlight behind the text (to stand out from busy background)
 */
int r1b_putchar(r1b_im_t* im, int cp, int x, int y, r1b_font_t* font,float val, int mode, int highlight){
  int idx = r1b_glyph_index(font,cp);
  if (idx < 0){
    return 0;
  }
  int off = (font->offsets[idx]*font->h)/2;
  int w = font->sizes[idx]*4;

  int r; for (r= 0; r < font->h; r ++) {
    int c; for (c= 0; c < w; c ++ ){
      int bb = font->glyphs[off+r*w/8+c/8];
      int b = (bb >> (7-c%8)) & 1;
      if (b > 0){
        r1b_set(im,x+c,y+r,val,mode);
      }else if (highlight){
        r1b_set(im,x+c,y+r,1-val,mode);
      }
    }
  }
  return w;
}

// https://github.com/skeeto/branchless-utf8/blob/master/utf8.h
// Branchless UTF-8 decoder
//
/* Decode the next character, C, from BUF, reporting errors in E.
 *
 * Since this is a branchless decoder, four bytes will be read from the
 * buffer regardless of the actual length of the next character. This
 * means the buffer _must_ have at least three bytes of zero padding
 * following the end of the data stream.
 *
 * Errors are reported in E, which will be non-zero if the parsed
 * character was somehow invalid: invalid byte sequence, non-canonical
 * encoding, or a surrogate half.
 *
 * The function returns a pointer to the next character. When an error
 * occurs, this pointer will be a guess that depends on the particular
 * error, but it will always advance at least one byte.
 */
static void* r1b_utf8_decode(void *buf, uint32_t *c, int *e) {
    static const char lengths[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0
    };
    static const int masks[]  = {0x00, 0x7f, 0x1f, 0x0f, 0x07};
    static const uint32_t mins[] = {4194304, 0, 128, 2048, 65536};
    static const int shiftc[] = {0, 18, 12, 6, 0};
    static const int shifte[] = {0, 6, 4, 2, 0};

    unsigned char *s = (unsigned char *)buf;
    int len = lengths[s[0] >> 3];

    /* Compute the pointer to the next character early so that the next
     * iteration can start working on the next character. Neither Clang
     * nor GCC figure out this reordering on their own.
     */
    unsigned char *next = s + len + !len;

    /* Assume a four-byte character and load four bytes. Unused bits are
     * shifted out.
     */
    *c  = (uint32_t)(s[0] & masks[len]) << 18;
    *c |= (uint32_t)(s[1] & 0x3f) << 12;
    *c |= (uint32_t)(s[2] & 0x3f) <<  6;
    *c |= (uint32_t)(s[3] & 0x3f) <<  0;
    *c >>= shiftc[len];

    /* Accumulate the various error conditions. */
    *e  = (*c < mins[len]) << 6; // non-canonical encoding
    *e |= ((*c >> 11) == 0x1b) << 7;  // surrogate half?
    *e |= (*c > 0x10FFFF) << 8;  // out of range?
    *e |= (s[1] & 0xc0) >> 2;
    *e |= (s[2] & 0xc0) >> 4;
    *e |= (s[3]       ) >> 6;
    *e ^= 0x2a; // top two bits of each tail byte correct?
    *e >>= shifte[len];

    return next;
}


/**
 * @brief draw a string (of wide chars) to image
 * @param im         pointer to image
 * @param str        text stored as wchar_t*
 * @param x          x coordinate
 * @param y          y coordinate
 * @param font       pointer to font
 * @param val        value (color) of the text
 * @param mode       blit mode, see r1b_set
 * @param highlight  boolean: whether to draw a highlight behind the text (to stand out from busy background)
 */
void r1b_text(r1b_im_t* im, wchar_t* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight){
  wchar_t c = 42;
  int i = 0;
  int xx = x;
  int yy = y;
  while (c != 0){
    c = str[i];
    if (c == 0){
      return;
    }
    if (c == 0x0A){
      yy += font->h;
      xx = x;
    }else{
      xx += r1b_putchar(im,c,xx,yy,font,val,mode,highlight);
    }
    i ++;
  }
}

/**
 * @brief draw a utf-8 encoded string to image
 * @param im         pointer to image
 * @param str        utf-8 encoded string
 * @param x          x coordinate
 * @param y          y coordinate
 * @param font       pointer to font
 * @param val        value (color) of the text
 * @param mode       blit mode, see r1b_set
 * @param highlight  boolean: whether to draw a highlight behind the text (to stand out from busy background)
 */
void r1b_text_utf8(r1b_im_t* im, char* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight){
  wchar_t wstr[strlen(str)+1];
  char padded[strlen(str)+4];
  memcpy(padded,str,strlen(str));
  memset(&padded[strlen(str)],0,4);
  void* next = (void*)padded;
  int e;
  int idx = 0;
  while((char*)next <= (char*)padded+strlen(str)){
    next = r1b_utf8_decode(next, (uint32_t *)&wstr[idx], &e);
    idx++;
  }
  wstr[idx] = 0;
  r1b_text(im,wstr,x,y,font,val,mode,highlight);
}

/**
 * @brief draw an ascii-only string to image
 * @param im         pointer to image
 * @param str        the string
 * @param x          x coordinate
 * @param y          y coordinate
 * @param font       pointer to font
 * @param val        value (color) of the text
 * @param mode       blit mode, see r1b_set
 * @param highlight  boolean: whether to draw a highlight behind the text (to stand out from busy background)
 */
void r1b_text_ascii(r1b_im_t* im, char* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight){
  char c = 42;
  int i = 0;
  int xx = x;
  int yy = y;
  while (c != 0){
    c = str[i];
    if (c == 0){
      return;
    }
    if (c == 0x0A){
      yy += font->h;
      xx = x;
    }else{
      xx += r1b_putchar(im,c,xx,yy,font,val,mode,highlight);
    }
    i ++;
  }
}

/**
 * @brief (internal use) calculate area of a polygon
 * @param X   x-coordinates of vertices
 * @param Y   y-coordinates of vertices
 * @param n   number of vertices
 * @return    the area
 */
float r1b_area(float* X, float* Y, int n) {
  // ported from https://github.com/cmu462/DrawSVG
  float a = 0.0f;
  int p,q; for (p=n-1,q=0; q<n; p=q++) {
    a += X[p] * Y[q] - X[q] * Y[p];
  }
  return a * 0.5f;
}

int r1b_triangulate_snip(float* X, float* Y,int u,int v,int w,int n,int *V ) {
  // ported from https://github.com/cmu462/DrawSVG
  int p;
  float Ax, Ay, Bx, By, Cx, Cy, Px, Py;
  Ax = X[V[u]];
  Ay = Y[V[u]];
  Bx = X[V[v]];
  By = Y[V[v]];
  Cx = X[V[w]];
  Cy = Y[V[w]];
  if ( 0.0000000001f > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))) ) return 0;
  for ( p = 0; p < n; p++ ) {
    if( (p == u) || (p == v) || (p == w) ) continue;
    Px = X[V[p]];
    Py = Y[V[p]];
    if (R1B_PT_IN_TRI(Px,Py,Ax,Ay,Bx,By,Cx,Cy)) return 0;
  }
  return 1;
}

/**
 * @brief (internal use) triangulate a polygon
 * @param X          x-coordinates of vertices
 * @param Y          y-coordinates of vertices
 * @param n          number of vertices
 * @param triangles  pointer to an array where triangle vertex indices will be written
 * @return           number of triangles written
 */
int r1b_triangulate(float* X, float* Y, int n, int* triangles) {
  // ported from https://github.com/cmu462/DrawSVG
  // allocate and initialize list of vertices in polygon
  if ( n < 3 ) return 0;
  int* V = (int*)alloca(n*sizeof(int));
  // we want a counter-clockwise polygon in V
  if ( 0.0f < r1b_area(X,Y,n) ) {
    int v; for (v=0; v<n; v++) V[v] = v;
  } else {
    int v; for (v=0; v<n; v++) V[v] = (n-1)-v;
  }
  int nv = n;
  // remove nv-2 Vertices, creating 1 triangle every time
  int count = 2*nv;   // error detection 
  int m = 0;
  int v; for (v= nv - 1; nv > 2;) {
    // if we loop, it is probably a non-simple polygon
    if (0 >= (count--)) {
      // Triangulate: ERROR - probable bad polygon!
      printf("Triangulate: ERROR - probable bad polygon!\n");
      return m;
    }
    // three consecutive vertices in current polygon, <u,v,w>
    int u = v     ; if (nv <= u) u = 0;      // prev
    v = u + 1     ; if (nv <= v) v = 0;      // new v   
    int w = v + 1 ; if (nv <= w) w = 0;      // next    
    if ( r1b_triangulate_snip(X,Y,u,v,w,nv,V) ) {
      int a,b,c,s,t;
      // true names of the vertices
      a = V[u]; b = V[v]; c = V[w];
      // output Triangle
      triangles[m*3  ]=a;
      triangles[m*3+1]=b;
      triangles[m*3+2]=c;
      m++;
      // remove v from remaining polygon
      for( s = v, t = v + 1; t < nv; s++, t++) V[s] = V[t]; nv--;
      // resest error detection counter
      count = 2 * nv;
    }
  }
  return m;
}

/**
 * @brief (internal use) draw a convex polygon on image
 * @param im    pointer to iamge
 * @param Xs    x-coordinates of vertices
 * @param Ys    y-coordinates of vertices
 * @param n     number of vertices
 * @param pttn  fill pattern
 * @param mode  blit mode, see r1b_set for details
 */
void r1b_polygon_convex(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode){
  int i; for (i= 1; i < n-1; i++ ){
    r1b_triangle(im,
      Xs[0],  Ys[0],
      Xs[i],  Ys[i],
      Xs[i+1],Ys[i+1],pttn,mode);
  }
}

/**
 * @brief (internal use) draw a concave polygon on image
 * @param im    pointer to iamge
 * @param Xs    x-coordinates of vertices
 * @param Ys    y-coordinates of vertices
 * @param n     number of vertices
 * @param pttn  fill pattern
 * @param mode  blit mode, see r1b_set for details
 */
void r1b_polygon_concave(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode){
  int tris[n*3];
  int n_tris = r1b_triangulate(Xs,Ys,n,tris);
  int i; for (i= 0; i < n_tris; i++) {
    r1b_triangle(im,
      Xs[tris[i*3  ]],Ys[tris[i*3  ]],
      Xs[tris[i*3+1]],Ys[tris[i*3+1]],
      Xs[tris[i*3+2]],Ys[tris[i*3+2]],pttn,mode);
  }
}

/**
 * @brief draw a polygon on image
 * @param im    pointer to iamge
 * @param Xs    x-coordinates of vertices
 * @param Ys    y-coordinates of vertices
 * @param n     number of vertices
 * @param pttn  fill pattern
 * @param mode  blit mode, see r1b_set for details
 * @param typ   type of polygon, either R1B_POLY_CONVEX or R1B_POLY_CONCAVE.
 *              concave mode works for convex polygons too, but asserting it as convex can speed things up
 */
void r1b_polygon(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode, int typ){
  switch (typ){
    case R1B_POLY_CONVEX:
      r1b_polygon_convex(im,Xs,Ys,n,pttn,mode);
      break;
    case R1B_POLY_CONCAVE:
    default:
      r1b_polygon_concave(im,Xs,Ys,n,pttn,mode);
  }
}

#define R1B_PT_IN_ELL(h,k,x,y,a,b) ((((x)-(h))*((x)-(h))/((a)*(a))+((y)-(k))*((y)-(k))/((b)*(b)))<=1)


/**
 * @brief draw an ellipse on image
 * @param im    pointer to iamge
 * @param cx    x-coordinates of the center
 * @param cy    y-coordinates of the center
 * @param rx    radius in x-direction
 * @param ry    radius in y-direction
 * @param ang   rotation of the ellipse (in radians)
 * @param pttn  fill pattern
 * @param mode  blit mode, see r1b_set for details
 */
void r1b_ellipse(r1b_im_t* im, float cx, float cy, float rx, float ry, float ang, r1b_im_t* pttn, int mode){
  int xmin,xmax,ymin,ymax;
  if (ang == 0){
    xmin = (int)floor(cx-rx);
    xmax = (int) ceil(cx+rx);
    ymin = (int)floor(cy-ry);
    ymax = (int) ceil(cy+ry);
  }else{
    float r = fmax(rx,ry);
    xmin = (int)floor(cx-r);
    xmax = (int) ceil(cx+r);
    ymin = (int)floor(cy-r);
    ymax = (int) ceil(cy+r);
  }

  float costh = cos(ang);
  float sinth = sin(ang);

  int y; for (y= ymin; y <= ymax; y ++ ){
    int x; for (x= xmin; x <= xmax; x ++ ){
      float fx = (float)x;
      float fy = (float)y;
      if (ang != 0){
        float gx = fx-cx;
        float gy = fy-cy;
        fx = cx + (gx * costh - gy * sinth);
        fy = cy + (gx * sinth + gy * costh);
      }
      if R1B_PT_IN_ELL(cx,cy,fx,fy,rx,ry){
        float v = pttn->data[(y % pttn->h) * pttn->w + (x % pttn->w)];
        r1b_set(im,x,y,v,mode);
      }  
    }
  }
}

/**
 * @brief draw outline of an ellipse on image
 * @param im      pointer to iamge
 * @param cx      x-coordinates of the center
 * @param cy      y-coordinates of the center
 * @param rx      radius in x-direction
 * @param ry      radius in y-direction
 * @param ang     rotation of the ellipse (in radians)
 * @param detail  number of segments used to approximate the ellipse, the higher the smoother
 * @param val     value (color) of the outline
 * @param mode    blit mode, see r1b_set for details
 */
void r1b_line_ellipse(r1b_im_t* im, float cx, float cy, float rx, float ry, float ang, int detail, float val, int mode){
  
  float costh = cos(-ang);
  float sinth = sin(-ang);
  float px, py;

  int i; for (i=0; i < detail+1; i ++){
    float a = (float)i/(float)detail*M_PI*2;
    float x = cos(a)*rx;
    float y = sin(a)*ry;
    float fx = cx + (x * costh - y * sinth);
    float fy = cy + (x * sinth + y * costh);
    if (i > 0){
      r1b_line(im,px,py,fx,fy,val,mode);
    }
    px = fx;
    py = fy;
  }
}

/**
 * @brief blit an image onto another, optionally applying a mask.
 *        supports drawing a subsection and repeated patterns
 * @param dst     pointer to destination image
 * @param src     pointer to source image
 * @param msk     pointer to mask image. for no masking, use an image of all 1's (e.g. R1B_GET_PATTERN(SOLID) and R1B_BRDR_WRAP for bdmode)
 * @param x0      x coordinate on the destination image for upper left  corner of source image
 * @param y0      y coordinate on the destination image for upper left  corner of source image
 * @param x1      x coordinate on the destination image for lower right corner of source image
 * @param y1      y coordinate on the destination image for lower right corner of source image
 * @param sx      x coordinate on the source image to offset
 * @param sy      y coordinate on the source image to offset
 * @param bdmode  border mode, see r1b_get for details
 * @param mode    blit mode, see r1b_set for details
 */
void r1b_blit(r1b_im_t* dst, r1b_im_t* src, r1b_im_t* msk, float x0, float y0, float x1, float y1, float sx, float sy, int bdmode, int mode){
  int dx = x1 > x0 ? 1 : -1;
  int dy = y1 > y0 ? 1 : -1;

  int xmin = (int)round(fmin(x0,x1));
  int xmax = (int)round(fmax(x0,x1));
  int ymin = (int)round(fmin(y0,y1));
  int ymax = (int)round(fmax(y0,y1));

  int isx = (int)round(sx);
  int isy = (int)round(sy);
  int ix0 = (int)round(x0);
  int iy0 = (int)round(y0);

  int y; for (y=ymin; y < ymax; y++){
    int x; for (x=xmin; x < xmax; x++){
      int j = dx * (x-xmin) +isx;
      int i = dy * (y-ymin) +isy;
      int u = r1b_get(msk,j,i,bdmode);
      if (u >= 0.5){
        float v = r1b_get(src,j,i,bdmode);
        r1b_set(dst,x,y,v,mode);
      }
    }
  }
}

/**
 * @brief blit an image onto another, a simplified version of r1b_blit with less arguments
 * @param dst  pointer to destination image
 * @param src  pointer to source image
 * @param x    x coordinate on the destination image for upper left corner of source image
 * @param y    y coordinate on the destination image for upper left corner of source image
 */
void r1b_paste(r1b_im_t* dst, r1b_im_t* src, float x, float y){
  r1b_blit(dst,src,R1B_PATTERN(SOLID),x,y,x+src->w,y+src->h,0,0,R1B_BRDR_WRAP,R1B_BLIT_SET);
}


/**
 * @brief load an wavefront .obj file to a new mesh
 *
 * currently doesn't support mtl or normals
 * @param path  file path
 * @return      a mesh type
 */
r1b_mesh_t r1b_load_obj(const char* path){
  r1b_mesh_t obj;

  FILE * fp;
  char * line = NULL;
  size_t len;
  size_t linelen = 0;
  size_t read;
  fp = fopen(path,"r");

  int nv = 0;
  int nf = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    linelen = strlen(line)-1;
    if (linelen < 2){
      continue;
    }
    if (line[0] == 'v' && line[1] == ' '){
      nv ++;
    }else if (line[0] == 'f' && line[1] == ' '){
      nf ++;
    }
  }

  obj.n_tri = nf;
  obj.n_vtx = nv;

  obj.X = (float*)malloc(sizeof(float)*nv);
  obj.Y = (float*)malloc(sizeof(float)*nv);
  obj.Z = (float*)malloc(sizeof(float)*nv);

  obj.tris = (int*)malloc(sizeof(int)*nf*3);
  obj.norms = NULL;

  rewind(fp);

  linelen = 0;

  int vi = 0;
  int fi = 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    linelen = strlen(line)-1;
    if (linelen < 2){
      continue;
    }
    if (line[0] == 'v' && line[1] == ' '){
      float x, y, z /*-Wall*/ = 0.0 /**/;
      int xyz = 0;
      int xi = 2; int yi = 2; int zi = 2;
      int i; for (i= 2; i < linelen+1; i++){
        if (line[i] == ' ' || i == linelen){
          line[i] = 0;
          if (xyz == 0){
            x = atof(&line[xi]);
            yi = i+1;
          }else if (xyz == 1){
            y = atof(&line[yi]);
            zi = i+1;
          }else if (xyz == 2){
            z = atof(&line[zi]);
            break;
          }
          xyz ++;
        }
      }
      obj.X[vi] = x;
      obj.Y[vi] = y;
      obj.Z[vi] = z;
      // printf("%f %f %f %d %d %d\n",x,y,z,xi,yi,zi);
      vi ++;
    }else if (line[0] == 'f' && line[1] == ' '){
      int a,b,c /*-Wall*/ = 0.0 /**/;
      int abc = 0;
      int ai = 2; int bi = 2; int ci = 2;
      int i; for (i= 2; i < linelen+1; i++){
        if (line[i] == '/'){
          line[i] = 0;
        }if (line[i] == ' ' || i == linelen){
          line[i] = 0;
          if (abc == 0){
            a = atoi(&line[ai]);
            bi = i+1;
          }else if (abc == 1){
            b = atoi(&line[bi]);
            ci = i+1;
          }else if (abc == 2){
            c = atoi(&line[ci]);
            break;
          }
          abc ++;
        }
      }
      a += (a < 0) ? vi : (-1);
      b += (b < 0) ? vi : (-1);
      c += (c < 0) ? vi : (-1);
      obj.tris[fi*3  ] = a;
      obj.tris[fi*3+1] = b;
      obj.tris[fi*3+2] = c;
      // printf("%d %d %d\n",a,b,c);
      fi++;
    }
  }
  return obj;
}

/**
 * @brief calculate the bounding box of a mesh
 * @param mesh   pointer to mesh
 * @param xmin   pointer to minimum x to be overwritten
 * @param ymin   pointer to minimum y to be overwritten
 * @param zmin   pointer to minimum z to be overwritten
 * @param xmax   pointer to maximum x to be overwritten
 * @param ymax   pointer to maximum y to be overwritten
 * @param zmax   pointer to maximum z to be overwritten
 */
void r1b_mesh_bbox(r1b_mesh_t* mesh, float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax){
  *xmin = FLT_MAX;
  *ymin = FLT_MAX;
  *zmin = FLT_MAX;
  *xmax = -FLT_MAX;
  *ymax = -FLT_MAX;
  *zmax = -FLT_MAX;
  int i; for (i= 0; i < mesh->n_vtx; i++){
    *xmin = fmin(*xmin,mesh->X[i]);
    *ymin = fmin(*ymin,mesh->Y[i]);
    *zmin = fmin(*zmin,mesh->Z[i]);
    *xmax = fmax(*xmax,mesh->X[i]);
    *ymax = fmax(*ymax,mesh->Y[i]);
    *zmax = fmax(*zmax,mesh->Z[i]);
  }
}

/**
 * @brief normalize vertices of a mesh to be bounded by (-1,-1,-1) and (1,1,1), 
 *        keeping proportions
 * @param mesh   pointer to mesh
 */
void r1b_normalize_mesh(r1b_mesh_t* mesh){
  float xmin,ymin,zmin,xmax,ymax,zmax;
  r1b_mesh_bbox(mesh,&xmin,&ymin,&zmin,&xmax,&ymax,&zmax);

  float s = R1B_MAX(R1B_MAX(xmax-xmin,ymax-ymin),zmax-zmin);
  float px = (s - (xmax-xmin)) / 2;
  float py = (s - (ymax-ymin)) / 2;
  float pz = (s - (zmax-zmin)) / 2;
  int i; for (i= 0; i < mesh->n_vtx; i++){
    mesh->X[i] = (mesh->X[i]-xmin+px)*(2/s)-1;
    mesh->Y[i] = (mesh->Y[i]-ymin+py)*(2/s)-1;
    mesh->Z[i] = (mesh->Z[i]-zmin+pz)*(2/s)-1;
  }
  // r1b_mesh_bbox(mesh,&xmin,&ymin,&zmin,&xmax,&ymax,&zmax);
  // printf("%f %f %f, %f %f %f\n",xmin,ymin,zmin,xmax,ymax,zmax);
}

/**
 * @brief free memory allocated in a mesh
 * @param mesh   pointer to mesh
 */
void r1b_destroy_mesh(r1b_mesh_t* mesh){
  free(mesh->X);
  free(mesh->Y);
  free(mesh->Z);
  free(mesh->tris);
  if (mesh->norms){
    free(mesh->norms);
  }
}

#define R1B_MAT_IDEN {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}
#define R1B_MAT_ROTX(a) {1,0,0,0, 0,cos(a),-sin(a),0, 0,sin(a),cos(a),0, 0,0,0,1}
#define R1B_MAT_ROTY(a) {cos(a),0,sin(a),0, 0,1,0,0, -sin(a),0,cos(a),0, 0,0,0,1}
#define R1B_MAT_ROTZ(a) {cos(a),-sin(a),0,0, sin(a),cos(a),0,0, 0,0,1,0, 0,0,0,1}
#define R1B_MAT_TRSL(x,y,z) {1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1}
#define R1B_MAT_SCAL(x,y,z) {x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1}
#define R1B_MAT_MULT(A,B) {(A)[0]*(B)[0]+(A)[1]*(B)[4]+(A)[2]*(B)[8]+(A)[3]*(B)[12],(A)[0]*(B)[1]+(A)[1]*(B)[5]+(A)[2]*(B)[9]+(A)[3]*(B)[13],(A)[0]*(B)[2]+(A)[1]*(B)[6]+(A)[2]*(B)[10]+(A)[3]*(B)[14],(A)[0]*(B)[3]+(A)[1]*(B)[7]+(A)[2]*(B)[11]+(A)[3]*(B)[15],(A)[4]*(B)[0]+(A)[5]*(B)[4]+(A)[6]*(B)[8]+(A)[7]*(B)[12],(A)[4]*(B)[1]+(A)[5]*(B)[5]+(A)[6]*(B)[9]+(A)[7]*(B)[13],(A)[4]*(B)[2]+(A)[5]*(B)[6]+(A)[6]*(B)[10]+(A)[7]*(B)[14],(A)[4]*(B)[3]+(A)[5]*(B)[7]+(A)[6]*(B)[11]+(A)[7]*(B)[15],(A)[8]*(B)[0]+(A)[9]*(B)[4]+(A)[10]*(B)[8]+(A)[11]*(B)[12],(A)[8]*(B)[1]+(A)[9]*(B)[5]+(A)[10]*(B)[9]+(A)[11]*(B)[13],(A)[8]*(B)[2]+(A)[9]*(B)[6]+(A)[10]*(B)[10]+(A)[11]*(B)[14],(A)[8]*(B)[3]+(A)[9]*(B)[7]+(A)[10]*(B)[11]+(A)[11]*(B)[15],(A)[12]*(B)[0]+(A)[13]*(B)[4]+(A)[14]*(B)[8]+(A)[15]*(B)[12],(A)[12]*(B)[1]+(A)[13]*(B)[5]+(A)[14]*(B)[9]+(A)[15]*(B)[13],(A)[12]*(B)[2]+(A)[13]*(B)[6]+(A)[14]*(B)[10]+(A)[15]*(B)[14],(A)[12]*(B)[3]+(A)[13]*(B)[7]+(A)[14]*(B)[11]+(A)[15]*(B)[15]}

#define R1B_MAT_TFRM(A,v) {((A)[0]*(v)[0]+(A)[1]*(v)[1]+(A)[2]*(v)[2]+(A)[3])/((A)[12]*(v)[0]+(A)[13]*(v)[1]+(A)[14]*(v)[2]+(A)[15]),((A)[4]*(v)[0]+(A)[5]*(v)[1]+(A)[6]*(v)[2]+(A)[7])/((A)[12]*(v)[0]+(A)[13]*(v)[1]+(A)[14]*(v)[2]+(A)[15]),((A)[8]*(v)[0]+(A)[9]*(v)[1]+(A)[10]*(v)[2]+(A)[11])/((A)[12]*(v)[0]+(A)[13]*(v)[1]+(A)[14]*(v)[2]+(A)[15])}
#define R1B_MAT_PROJ(f,v) {(f)*(v)[0]/(v)[2],(f)*(v)[1]/(v)[2]}

// see https://en.wikipedia.org/wiki/Barycentric_coordinate_system
#define R1B_BARY_DET(x,y,x1,y1,x2,y2,x3,y3) (((y2)-(y3))*((x1)-(x3))+((x3)-(x2))*((y1)-(y3)))
#define R1B_BARY_U(x,y,x1,y1,x2,y2,x3,y3)   (((y2)-(y3))*((x)-(x3))+((x3)-(x2))*((y)-(y3)))
#define R1B_BARY_V(x,y,x1,y1,x2,y2,x3,y3)   (((y3)-(y1))*((x)-(x3))+((x1)-(x3))*((y)-(y3)))


/**
 * @brief draw a 3D triangle to image, projected with pinhole camera model
 * @param im     pointer to image
 * @param depth  pointer to the depth buffer, which will be read and written. use r1b_infs() for initialization
 * @param f      focal length of the camera
 * @param x0     x coordinate of the first  vertex
 * @param y0     y coordinate of the first  vertex
 * @param z0     z coordinate of the first  vertex
 * @param x1     x coordinate of the second vertex
 * @param y1     y coordinate of the second vertex
 * @param z1     z coordinate of the second vertex
 * @param x2     x coordinate of the third  vertex
 * @param y2     y coordinate of the third  vertex
 * @param z2     z coordinate of the third  vertex
 * @param pttn   fill pattern, when NULL, `vals` argument will be used instead
 * @param vals   3-array for value (color) of each vertex (points in triangle will have interpolated colors), 
 *               used when `pttn` argument is NULL
 * @param mode   blit mode, see r1b_set for details
 */
void r1b_triangle3d(r1b_im_t* im, r1b_im_t* depth, float f, float x0, float y0, float z0, float x1 ,float y1, float z1, float x2 ,float y2, float z2, r1b_im_t* pttn, float* vals, int mode ){
  
  // printf("%f %f %f, %f %f %f, %f %f %f\n",x0,y0,z0,x1,y1,z1,x2,y2,z2);

  float u0[3] = {x0,y0,z0};
  float v0[] = R1B_MAT_PROJ(f,u0);
  float xx0 = v0[0]+im->w/2;
  float yy0 =-v0[1]+im->h/2;

  float u1[3] = {x1,y1,z1};
  float v1[] = R1B_MAT_PROJ(f,u1);
  float xx1 = v1[0]+im->w/2;
  float yy1 =-v1[1]+im->h/2;

  float u2[3] = {x2,y2,z2};
  float v2[] = R1B_MAT_PROJ(f,u2);
  float xx2 = v2[0]+im->w/2;
  float yy2 =-v2[1]+im->h/2;

  // printf("%f %f, %f %f, %f %f\n",xx0,yy0,xx1,yy1,xx2,yy2);

  int xmin = (int)floor(fmin(fmin(xx0,xx1),xx2));
  int xmax = (int) ceil(fmax(fmax(xx0,xx1),xx2));
  int ymin = (int)floor(fmin(fmin(yy0,yy1),yy2));
  int ymax = (int) ceil(fmax(fmax(yy0,yy1),yy2));

  int y; for (y=ymin; y <= ymax; y++){
    int x; for (x=xmin; x <= xmax; x++){

      float det= R1B_BARY_DET(x,y,xx0,yy0,xx1,yy1,xx2,yy2);
      float u  = R1B_BARY_U(  x,y,xx0,yy0,xx1,yy1,xx2,yy2)/det;
      float v  = R1B_BARY_V(  x,y,xx0,yy0,xx1,yy1,xx2,yy2)/det;
      float w  = (1-u-v);

      if (!(0 <= u && u <= 1 && 0 <= v && v<= 1 && 0 <= w && w <= 1)){
        continue;
      }

      float d = u * z0 + v * z1 + w * z2;
      float d0 = r1b_get(depth,x,y,R1B_BRDR_ZERO);

      if (d > d0){
        continue;
      }
      float val;
      if (pttn){
        val = pttn->data[(y % pttn->h) * pttn->w + (x % pttn->w)];
      }else{
        val = vals[0] * u + vals[1] * v + vals[2] * w;
      }
      r1b_set(im,x,y,val,mode);
      r1b_set(depth,x,y,d,R1B_BLIT_SET);
    }
  }
}

/**
 * @brief draw a 3D line to image, projected with pinhole camera model
 * @param im         pointer to image
 * @param depth      pointer to the depth buffer. use r1b_infs() for initialization
 * @param depth_read boolean: whether or not to read the depth buffer. use 0 to draw on top of everything
 * @param f          focal length of the camera
 * @param x0         x coordinate of the first  endpoint
 * @param y0         y coordinate of the first  endpoint
 * @param z0         z coordinate of the first  endpoint
 * @param x1         x coordinate of the second endpoint
 * @param y1         y coordinate of the second endpoint
 * @param z1         z coordinate of the second endpoint
 * @param val        value (color) of the line
 * @param mode       blit mode, see r1b_set for details
 */
void r1b_line3d(r1b_im_t* im, r1b_im_t* depth, int depth_read, float f, float x0 ,float y0, float z0, float x1 ,float y1, float z1, float val, int mode){

  float u0[3] = {x0,y0,z0};
  float v0[] = R1B_MAT_PROJ(f,u0);
  float xx0 = v0[0]+im->w/2;
  float yy0 =-v0[1]+im->h/2;

  float u1[3] = {x1,y1,z1};
  float v1[] = R1B_MAT_PROJ(f,u1);
  float xx1 = v1[0]+im->w/2;
  float yy1 =-v1[1]+im->h/2;

  int sx0 = (int)round(xx0);
  int sy0 = (int)round(yy0);
  int sx1 = (int)round(xx1);
  int sy1 = (int)round(yy1);
  int dx  = sx1 > sx0 ? 1 : -1; // x increment
  int dy  = sy1 > sy0 ? 1 : -1; // y increment
  
  if (abs(sx0 - sx1) >= abs(sy0 - sy1)){ // slope < 1 ?
    int x = sx0;
    while (x != sx1+dx){
      int y = R1B_LINE_STEP(sx0,sx1,sy0,sy1,x);

      if (depth_read){
        float t = fabs((float)(x-sx0)/(float)(sx1-sx0));
        float d = z0 * (1-t) + z1 * t;
        d -= R1B_CONFIG_LINE3D_EPSILON;
        float d0 = r1b_get(depth,x,y,R1B_BRDR_ZERO);
        if (d <= d0){
          r1b_set(depth,x,y,d,R1B_BLIT_SET);
          r1b_set(im,x,y,val,mode);
        }
      }else{
        r1b_set(depth,x,y,0,R1B_BLIT_SET);
        r1b_set(im,x,y,val,mode);
      }
    
      x += dx;
    }
  }else{
    int y = sy0;
    while (y != sy1+dy){
      int x = R1B_LINE_STEP(sy0,sy1,sx0,sx1,y);

      if (depth_read){
        float t = fabs((float)(y-sy0)/(float)(sy1-sy0));
        float d = z0 * (1-t) + z1 * t;
        d -= R1B_CONFIG_LINE3D_EPSILON;
        float d0 = r1b_get(depth,x,y,R1B_BRDR_ZERO);
        if (d <= d0){
          r1b_set(depth,x,y,d,R1B_BLIT_SET);
          r1b_set(im,x,y,val,mode);
        }
      }else{
        r1b_set(depth,x,y,0,R1B_BLIT_SET);
        r1b_set(im,x,y,val,mode);
      }
      y += dy;
    }
  }
}

/**
 * @brief transform mesh with a 4x4 transformation matrix
 * @param mesh   pointer to mesh
 * @param mat    the 4x4 row major transformation matrix as an array of 16 floats
 */
void r1b_transform_mesh(r1b_mesh_t* mesh, float* mat){
  int i; for (i= 0; i < mesh->n_vtx; i++){
    float u[3] = {mesh->X[i],mesh->Y[i],mesh->Z[i]};
    float v[] = R1B_MAT_TFRM(mat,u);
    mesh->X[i] = v[0];
    mesh->Y[i] = v[1];
    mesh->Z[i] = v[2];
  }
}

/**
 * @brief scale mesh, apply rotation by euler angles (x-y-z order) and translate mesh
 * 
 * a simplified interface to r1b_transform_mesh that covers many use cases.
 * @param mesh pointer to mesh
 * @param sx   scale along x-axis
 * @param sy   scale along y-axis
 * @param sz   scale along z-axis
 * @param rx   rotation around x-axis
 * @param ry   rotation around y-axis
 * @param rz   rotation around z-axis
 * @param x    translation along x-axis
 * @param y    translation along y-axis
 * @param z    translation along z-axis
 */
void r1b_scale_rotate_translate(r1b_mesh_t* mesh, float sx, float sy, float sz, float rx, float ry, float rz, float x, float y, float z){
  float scl[]  = R1B_MAT_SCAL(sx,sy,sz);
  float rotx[] = R1B_MAT_ROTX(rx);
  float roty[] = R1B_MAT_ROTY(ry);
  float rotz[] = R1B_MAT_ROTZ(rz);

  float rotxy[]= R1B_MAT_MULT(roty,rotx);
  float rot[]  = R1B_MAT_MULT(rotz,rotxy);
  float trl[]  = R1B_MAT_TRSL(x,y,z);
  float tfm[]  = R1B_MAT_MULT(trl,rot);

  r1b_transform_mesh(mesh, scl);
  r1b_transform_mesh(mesh, tfm);
}

/**
 * @brief make a deep clone of given mesh
 * 
 * @param mesh pointer to mesh
 * @return     the clone
 */
r1b_mesh_t r1b_copy_of_mesh(r1b_mesh_t* mesh){
  r1b_mesh_t dst;
  dst.n_vtx = mesh->n_vtx;
  dst.n_tri = mesh->n_tri;
  dst.X =  (float*)malloc(sizeof(float)*dst.n_vtx);
  dst.Y =  (float*)malloc(sizeof(float)*dst.n_vtx);
  dst.Z =  (float*)malloc(sizeof(float)*dst.n_vtx);
  dst.tris = (int*)malloc(sizeof(int)*3*dst.n_tri);

  memcpy(dst.X,   mesh->X,   sizeof(float)*dst.n_vtx);
  memcpy(dst.Y,   mesh->Y,   sizeof(float)*dst.n_vtx);
  memcpy(dst.Z,   mesh->Z,   sizeof(float)*dst.n_vtx);
  memcpy(dst.tris,mesh->tris,sizeof(int)*3*dst.n_tri);

  if (mesh->norms){
    dst.norms = (float*)malloc(sizeof(float)*3*dst.n_vtx);
    memcpy(dst.norms,mesh->norms,sizeof(float)*3*dst.n_vtx);
  }else{
    dst.norms = NULL;
  }

  return dst;
}

#define R1B_V3_CROSS(a1,a2,a3,b1,b2,b3) {(a2)*(b3)-(a3)*(b2),(a3)*(b1)-(a1)*(b3),(a1)*(b2)-(a2)*(b1)}
#define R1B_V3_DOT(a1,a2,a3,b1,b2,b3)   ((a1)*(b1)+(a2)*(b2)+(a3)*(b3))

#define R1B_V3_MAG(a1,a2,a3) (sqrt((a1)*(a1)+(a2)*(a2)+(a3)*(a3)))

/**
 * @brief estimate vertex normals for a mesh and store result in mesh->norms
 * @param mesh   pointer to mesh
 */
void r1b_compute_vertex_normals(r1b_mesh_t* mesh){
  if (!(mesh->norms)){
    mesh->norms = (float*)malloc(sizeof(float)*mesh->n_vtx*3);
  }
  int* cnts = (int*)malloc(sizeof(int)*mesh->n_vtx);
  int i;

  for (i = 0; i < mesh->n_tri; i++){
    int a = mesh->tris[i*3  ];
    int b = mesh->tris[i*3+1];
    int c = mesh->tris[i*3+2];
    float v0[3] = {mesh->X[b]-mesh->X[c],mesh->Y[b]-mesh->Y[c],mesh->Z[b]-mesh->Z[c]};
    float v1[3] = {mesh->X[a]-mesh->X[b],mesh->Y[a]-mesh->Y[b],mesh->Z[a]-mesh->Z[b]};;

    float nml[] = R1B_V3_CROSS(
      v0[0],v0[1],v0[2],
      v1[0],v1[1],v1[2]
    );
    float mnml = R1B_V3_MAG(nml[0],nml[1],nml[2]);
    nml[0]/=mnml;nml[1]/=mnml;nml[2]/=mnml;

    mesh->norms[a*3  ]+=nml[0];
    mesh->norms[a*3+1]+=nml[1];
    mesh->norms[a*3+2]+=nml[2];
    cnts[a]++;

    mesh->norms[b*3  ]+=nml[0];
    mesh->norms[b*3+1]+=nml[1];
    mesh->norms[b*3+2]+=nml[2];
    cnts[b]++;

    mesh->norms[c*3  ]+=nml[0];
    mesh->norms[c*3+1]+=nml[1];
    mesh->norms[c*3+2]+=nml[2];
    cnts[c]++;

  }
  for (i = 0; i < mesh->n_vtx; i++){
    mesh->norms[i*3  ]/=cnts[i];
    mesh->norms[i*3+1]/=cnts[i];
    mesh->norms[i*3+2]/=cnts[i];
  }
  free(cnts);
}

/**
 * @brief draw a 3d mesh to the image, projected with pinhole camera model
 * @param im        pointer to image
 * @param depth     pointer to the depth buffer, which will be read and written. use r1b_infs() for initialization
 * @param mesh      pointer to mesh
 * @param f         focal length of the camera
 * @param pttn      fill pattern, can be NULL depending on the shader specified
 * @param light     4-array: the first 3 are direction of the light, 4th is global illumination. can be NULL depending on shader specified
 * @param wire_val  value (color) of the wireframe. might be unused depending on the shader specified
 * @param shdr      shader type to use, one of:
 *                  R1B_SHDR_NONE:   no shading will be done, if wireframe is also off, you will not be able to see anything;
 *                  R1B_SHDR_FLAT:   flat shading, use pattern fill to evenly fill all faces;
 *                  R1B_SHDR_NDOTL:  n-dot-l diffuse shading, quantized to 5 levels and filled with patterns of different shades;
 *                  R1B_SHDR_NDOTLF: n-dot-l shading but without quantization, returning grayscale, on which dithering can be further applied
 * @param wire      type of wireframe, one of:
 *                  R1B_WIRE_FRONT: wireframe can be occluded;
 *                  R1B_WIRE_ALL:   all wireframes are drawn;
 *                  R1B_WIRE_NONE:  no wireframe is drawn.
 */
void r1b_render_mesh(r1b_im_t* im, r1b_im_t* depth, r1b_mesh_t* mesh, float f, r1b_im_t* pttn, float* light, int wire_val, int shdr, int wire){

  int i; for (i= 0; i < mesh->n_tri; i++){
    int a = mesh->tris[i*3  ];
    int b = mesh->tris[i*3+1];
    int c = mesh->tris[i*3+2];

    if (wire != R1B_WIRE_NONE){
      r1b_line3d(im,depth,(wire==R1B_WIRE_FRONT),f,mesh->X[a], mesh->Y[a], mesh->Z[a], mesh->X[b], mesh->Y[b], mesh->Z[b], wire_val, R1B_BLIT_SET);
      r1b_line3d(im,depth,(wire==R1B_WIRE_FRONT),f,mesh->X[b], mesh->Y[b], mesh->Z[b], mesh->X[c], mesh->Y[c], mesh->Z[c], wire_val, R1B_BLIT_SET);
      r1b_line3d(im,depth,(wire==R1B_WIRE_FRONT),f,mesh->X[c], mesh->Y[c], mesh->Z[c], mesh->X[a], mesh->Y[a], mesh->Z[a], wire_val, R1B_BLIT_SET);
    }

    if (shdr == R1B_SHDR_FLAT){
      r1b_triangle3d(im, depth, f,mesh->X[a], mesh->Y[a], mesh->Z[a],
                                 mesh->X[b], mesh->Y[b], mesh->Z[b],
                                 mesh->X[c], mesh->Y[c], mesh->Z[c], pttn, NULL, R1B_BLIT_SET);
    }else if (shdr == R1B_SHDR_NDOTL || shdr == R1B_SHDR_NDOTLF){

      float ndl;

      if (shdr == R1B_SHDR_NDOTL || mesh->norms == NULL){
        float v0[3] = {mesh->X[b]-mesh->X[c],mesh->Y[b]-mesh->Y[c],mesh->Z[b]-mesh->Z[c]};
        float v1[3] = {mesh->X[a]-mesh->X[b],mesh->Y[a]-mesh->Y[b],mesh->Z[a]-mesh->Z[b]};

        float nml[] = R1B_V3_CROSS(
          v0[0],v0[1],v0[2],
          v1[0],v1[1],v1[2]
        );
        float mnml = R1B_V3_MAG(nml[0],nml[1],nml[2]);
        nml[0]/=mnml;nml[1]/=mnml;nml[2]/=mnml;

        ndl = R1B_V3_DOT(nml[0],nml[1],nml[2],light[0],light[1],light[2]) + light[3];
      }

      if (shdr == R1B_SHDR_NDOTL){
        r1b_im_t* pttn3;
        if (ndl < 0.2){
          pttn3 = R1B_PATTERN(GRAY1);
        }else if (ndl < 0.4){
          pttn3 = R1B_PATTERN(GRAY2);
        }else if (ndl < 0.6){
          pttn3 = R1B_PATTERN(GRAY3);
        }else if (ndl < 0.8){
          pttn3 = R1B_PATTERN(GRAY4);
        }else{
          pttn3 = R1B_PATTERN(GRAY5);
        }
        r1b_triangle3d(im, depth, f,mesh->X[a], mesh->Y[a], mesh->Z[a],
                                               mesh->X[b], mesh->Y[b], mesh->Z[b],
                                               mesh->X[c], mesh->Y[c], mesh->Z[c], pttn3, NULL, R1B_BLIT_SET);
      }else{
        float ndls[] = {ndl,ndl,ndl};
        if (mesh->norms){
          ndls[0] = R1B_V3_DOT(mesh->norms[a*3], mesh->norms[a*3+1], mesh->norms[a*3+2], light[0],light[1],light[2])+light[3];
          ndls[1] = R1B_V3_DOT(mesh->norms[b*3], mesh->norms[b*3+1], mesh->norms[b*3+2], light[0],light[1],light[2])+light[3];
          ndls[2] = R1B_V3_DOT(mesh->norms[c*3], mesh->norms[c*3+1], mesh->norms[c*3+2], light[0],light[1],light[2])+light[3];
        }
        r1b_triangle3d(im, depth, f,mesh->X[a], mesh->Y[a], mesh->Z[a],
                                   mesh->X[b], mesh->Y[b], mesh->Z[b],
                                   mesh->X[c], mesh->Y[c], mesh->Z[c], NULL, ndls, R1B_BLIT_SET);
      }
    }

  }

}

#define R1B_MESH_ADD_VTX(mesh,x,y,z) mesh.X[mesh.n_vtx]=x; mesh.Y[mesh.n_vtx]=y; mesh.Z[mesh.n_vtx]=z; mesh.n_vtx++;
#define R1B_MESH_ADD_TRI(mesh,a,b,c) mesh.tris[mesh.n_tri*3]=a; mesh.tris[mesh.n_tri*3+1]=b; mesh.tris[mesh.n_tri*3+2]=c; mesh.n_tri++;

/**
 * @brief make a 3d cube mesh
 *
 * cube will be centred at 0,0,0
 * @param sx  x dimension
 * @param sy  y dimension
 * @param sz  z dimension
 */
r1b_mesh_t r1b_cube(float sx, float sy, float sz){
  float rx = sx/2;
  float ry = sy/2;
  float rz = sz/2;
  r1b_mesh_t mesh;

  mesh.X = (float*)malloc(sizeof(float)*8);
  mesh.Y = (float*)malloc(sizeof(float)*8);
  mesh.Z = (float*)malloc(sizeof(float)*8);

  mesh.tris = (int*)malloc(sizeof(int)*12*3);
  mesh.norms = NULL;

  mesh.n_tri = 0;
  mesh.n_vtx = 0;

  /* a cubist's cube
     4_____5
     /    /|
    /____/ |
  0|    1| |
   | 6   | |
   |_____|/ 7
  2     3
  */

  R1B_MESH_ADD_VTX(mesh,-rx, ry,-rz);
  R1B_MESH_ADD_VTX(mesh, rx, ry,-rz);
  R1B_MESH_ADD_VTX(mesh,-rx,-ry,-rz);
  R1B_MESH_ADD_VTX(mesh, rx,-ry,-rz);
  R1B_MESH_ADD_VTX(mesh,-rx, ry, rz);
  R1B_MESH_ADD_VTX(mesh, rx, ry, rz);
  R1B_MESH_ADD_VTX(mesh,-rx,-ry, rz);
  R1B_MESH_ADD_VTX(mesh, rx,-ry, rz);

  R1B_MESH_ADD_TRI(mesh,0,1,2);
  R1B_MESH_ADD_TRI(mesh,2,1,3);

  R1B_MESH_ADD_TRI(mesh,0,4,5);
  R1B_MESH_ADD_TRI(mesh,0,5,1);

  R1B_MESH_ADD_TRI(mesh,3,1,5);
  R1B_MESH_ADD_TRI(mesh,3,5,7);

  R1B_MESH_ADD_TRI(mesh,2,3,6);
  R1B_MESH_ADD_TRI(mesh,6,3,7);

  R1B_MESH_ADD_TRI(mesh,6,4,0);
  R1B_MESH_ADD_TRI(mesh,6,0,2);

  R1B_MESH_ADD_TRI(mesh,7,4,6);
  R1B_MESH_ADD_TRI(mesh,7,5,4);

  return mesh;
}

/**
 * @brief make a 3d sphere mesh
 *
 * sphere will be centred at 0,0,0
 * @param rad      radius
 * @param slices   number of segments on x-z plane 
 * @param stacks   number of segments on y axis
 */
r1b_mesh_t r1b_sphere(float rad, int slices, int stacks){
  r1b_mesh_t mesh;

  mesh.X = (float*)malloc(sizeof(float)*(2+stacks*slices));
  mesh.Y = (float*)malloc(sizeof(float)*(2+stacks*slices));
  mesh.Z = (float*)malloc(sizeof(float)*(2+stacks*slices));

  mesh.tris = (int*)malloc(sizeof(int)*stacks*slices*2*3);
  mesh.norms = NULL;

  mesh.n_tri = 0;
  mesh.n_vtx = 0;

  R1B_MESH_ADD_VTX(mesh,0, rad,0);
  R1B_MESH_ADD_VTX(mesh,0,-rad,0);

  int i;for (i = 0; i < stacks; i++){
    float th0 = (float)(i+1)/(float)stacks * M_PI;
    float y = rad*cos(th0);
    int j; for (j = 0; j < slices; j++){
      float th1 = (float)j/(float)slices * M_PI*2;
      float x = rad*cos(th1)*sin(th0);
      float z = rad*sin(th1)*sin(th0);

      R1B_MESH_ADD_VTX(mesh,x,y,z);
      if (i == 0){
        R1B_MESH_ADD_TRI(mesh,2+i*stacks+j,0,2+i*stacks+(j+1)%slices);
      }else if (i == stacks-1){
        R1B_MESH_ADD_TRI(mesh,2+(i-1)*stacks+j,2+(i-1)*stacks+(j+1)%slices,1);
      }else{
        R1B_MESH_ADD_TRI(mesh,2+(i-1)*stacks+j,   2+(i-1)*stacks+(j+1)%slices, 2+(i  )*stacks+j);
        R1B_MESH_ADD_TRI(mesh,2+(i-1)*stacks+(j+1)%slices, 2+(i  )*stacks+(j+1)%slices, 2+(i  )*stacks+j);
      }
    } 
  }
  return mesh;
}

/**
 * @brief make a 3d cylinder mesh
 *
 * cylinder will be centred at 0,0,0
 * @param rx       radius on x axis
 * @param rz       radius on z axis
 * @param h        height
 * @param slices   number of segments
 */
r1b_mesh_t r1b_cylinder(float rx, float rz, float h, int slices){
  r1b_mesh_t mesh;

  mesh.X = (float*)malloc(sizeof(float)*(2*slices+2));
  mesh.Y = (float*)malloc(sizeof(float)*(2*slices+2));
  mesh.Z = (float*)malloc(sizeof(float)*(2*slices+2));

  mesh.tris = (int*)malloc(sizeof(int)*slices*4*3);
  mesh.norms = NULL;

  mesh.n_tri = 0;
  mesh.n_vtx = 0;

  R1B_MESH_ADD_VTX(mesh,0, h/2,0);
  R1B_MESH_ADD_VTX(mesh,0,-h/2,0);

  int j; for (j = 0; j < slices; j++){
    float th = (float)j/(float)slices * M_PI*2;
    float x = rx*cos(th);
    float z = rz*sin(th);

    R1B_MESH_ADD_VTX(mesh,x, h/2,z);
    R1B_MESH_ADD_VTX(mesh,x,-h/2,z);

    R1B_MESH_ADD_TRI(mesh,2+j*2,            2+(j+1)%slices*2  , 2+j*2+1);
    R1B_MESH_ADD_TRI(mesh,2+(j+1)%slices*2, 2+(j+1)%slices*2+1, 2+j*2+1);

    R1B_MESH_ADD_TRI(mesh,2+j*2,         0, 2+(j+1)%slices*2);
    R1B_MESH_ADD_TRI(mesh,2+j*2+1,       2+(j+1)%slices*2+1,1);
    
  } 

  return mesh;
}

/**
 * @brief make a 3d cone mesh
 *
 * cone will be centred at 0,0,0
 * @param rx       radius on x axis
 * @param rz       radius on z axis
 * @param h        height
 * @param slices   number of segments
 */
r1b_mesh_t r1b_cone(float rx, float rz, float h, int slices){
  r1b_mesh_t mesh;

  mesh.X = (float*)malloc(sizeof(float)*(slices+2));
  mesh.Y = (float*)malloc(sizeof(float)*(slices+2));
  mesh.Z = (float*)malloc(sizeof(float)*(slices+2));

  mesh.tris = (int*)malloc(sizeof(int)*slices*2*3);
  mesh.norms = NULL;

  mesh.n_tri = 0;
  mesh.n_vtx = 0;

  R1B_MESH_ADD_VTX(mesh,0, h/2,0);
  R1B_MESH_ADD_VTX(mesh,0,-h/2,0);

  int j; for (j = 0; j < slices; j++){
    float th = (float)j/(float)slices * M_PI*2;
    float x = rx*cos(th);
    float z = rz*sin(th);

    R1B_MESH_ADD_VTX(mesh,x,-h/2,z);

    R1B_MESH_ADD_TRI(mesh,2+j,   0, 2+(j+1)%slices);
    R1B_MESH_ADD_TRI(mesh,2+j,   2+(j+1)%slices,1);
    
  } 

  return mesh;
}

/**
 * @brief generate a specified convolution matrix for image processing
 * @param ksize  kernel size, will be automatically rounded up to an odd integer
 * @param mode   morphological kernels: R1B_KERN_ELLIPSE, R1B_KERN_CROSS, R1B_KERN_RECT;
 *               convolutional kernels: R1B_KERN_GAUSS, R1B_KERN_GAUSS1D;
 * @return       kernal as image type
 */
r1b_im_t r1b_make_kernel(int ksize, int mode){
  if (!(ksize % 2)){
    ksize ++;
  }
  if (mode == R1B_KERN_RECT){
    return r1b_ones(ksize,ksize);
  }
  if (mode == R1B_KERN_GAUSS1D){
    r1b_im_t im = r1b_zeros(ksize,1);
    float sigma = 0.3*((float)(ksize-1)*0.5 - 1) + 0.8;
    float ss2 = sigma*sigma*2;
    int i; for (i = 0; i < ksize; i++){
      float x = (float)(i-ksize/2);
      float z = exp(-(x*x)/(ss2))/(2.5066282746*sigma);
      im.data[i]=z;
    }
    return im;
  }
  r1b_im_t im = r1b_zeros(ksize,ksize);
  
  if (mode == R1B_KERN_GAUSS){
    // sigma: https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html
    float sigma = 0.3*((float)(ksize-1)*0.5 - 1) + 0.8;
    float ss2 = sigma*sigma*2;
    int i; for (i = 0; i < ksize; i++){
      int j; for (j = 0; j < ksize; j++){
        float x = (float)(j-ksize/2);
        float y = (float)(i-ksize/2);
        float z = exp(-(x*x+y*y)/(ss2))/(M_PI*ss2);
        im.data[i*ksize+j]=z;
      }
    }
  }else if (mode == R1B_KERN_ELLIPSE){
    r1b_ellipse(&im, (ksize-1)/2, (ksize-1)/2, (ksize-1)/2, (ksize-1)/2, 0, R1B_PATTERN(SOLID), R1B_BLIT_SET);
  }else if (mode == R1B_KERN_CROSS){
    int i; for (i = 0; i < ksize; i++){
      im.data[i*ksize+ksize/2]=1;
      im.data[(ksize/2)*ksize+i]=1;
    }
  }
  return im;
}

/**
 * @brief perform 2D convolution on an image
 * @param im      pointer to image
 * @param kern    pointer to kernel
 * @param border  border mode, see r1b_get
 */
void r1b_conv2d(r1b_im_t* im, r1b_im_t* kern, int border) {
  r1b_make_tmp0(im->w,im->h);

  int khw = kern->w/2;
  int khh = kern->h/2;

  int i; for (i= 0; i < im->h; i++ ){
    int j; for (j= 0; j < im->w; j++ ){
      float sum = 0;
      int ki; for (ki= 0; ki < kern->h; ki ++ ){
        int kj; for (kj= 0; kj < kern->w; kj ++ ){
          sum += r1b_get(im,j-khw+kj, i-khh+ki, border) * kern->data[ki*kern->w+kj];
        }
      }
      r1b_tmp0[i*im->w+j] = sum;
    }
  }
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

/**
 * @brief perform morphological dilation on an image
 *
 * @param im      pointer to image
 * @param kern    pointer to kernel
 */
void r1b_dilate(r1b_im_t* im, r1b_im_t* kern){
  r1b_make_tmp0(im->w,im->h);

  int khw = kern->w/2;
  int khh = kern->h/2;

  int i; for (i= 0; i < im->h; i++ ){
    int j; for (j= 0; j < im->w; j++ ){
      float m = 0;
      int ki; for (ki= 0; ki < kern->h; ki ++ ){
        int kj; for (kj= 0; kj < kern->w; kj ++ ){
          m = fmax(m, r1b_get(im,j-khw+kj, i-khh+ki, R1B_BRDR_COPY) * kern->data[ki*kern->w+kj]);
        }
      }
      r1b_tmp0[i*im->w+j] = m;
    }
  }
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

/**
 * @brief perform morphological erosion on an image
 *
 * @param im      pointer to image
 * @param kern    pointer to kernel
 */
void r1b_erode(r1b_im_t* im, r1b_im_t* kern){
  r1b_make_tmp0(im->w,im->h);

  int khw = kern->w/2;
  int khh = kern->h/2;

  int i; for (i= 0; i < im->h; i++ ){
    int j; for (j= 0; j < im->w; j++ ){
      float m = 1;
      int ki; for (ki= 0; ki < kern->h; ki ++ ){
        int kj; for (kj= 0; kj < kern->w; kj ++ ){
          if (kern->data[ki*kern->w+kj] > 0.5){
            m = fmin(m, r1b_get(im,j-khw+kj, i-khh+ki, R1B_BRDR_COPY));
          }
        }
      }
      r1b_tmp0[i*im->w+j] = m;
    }
  }
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

/**
 * @brief apply sobel edge detection to an image
 *
 * @param im                        pointer to image
 * @param out_gradient_directions   optional: if non NULL, will be overwritten with gradient directions.
 *                                  (the source image will be written with gradient strength).
 *                                  if only gradient directions are needed, pass im->data here
 */
void r1b_sobel(r1b_im_t* im, float* out_gradient_directions){
  r1b_make_tmp1(im->w,im->h);

  r1b_im_t gx = r1b_copy_of(im);

  r1b_im_t gy;
  gy.w = im->w;
  gy.h = im->h;
  gy.data = r1b_tmp1;
  memcpy(gy.data, im->data, im->w*im->h*sizeof(float));

  float kdat0[3] = {1,2, 1};
  float kdat1[3] = {1,0,-1};

  r1b_im_t k1; k1.w = 1; k1.h = 3; k1.data = kdat0;
  r1b_im_t k2; k2.w = 3; k2.h = 1; k2.data = kdat1;
  r1b_im_t k3; k3.w = 1; k3.h = 3; k3.data = kdat1;
  r1b_im_t k4; k4.w = 3; k4.h = 1; k4.data = kdat0;

  r1b_conv2d(&gx,&k1,R1B_BRDR_COPY);
  r1b_conv2d(&gx,&k2,R1B_BRDR_COPY);

  r1b_conv2d(&gy,&k3,R1B_BRDR_COPY);
  r1b_conv2d(&gy,&k4,R1B_BRDR_COPY);

  int i; for (i = 0; i < im->w*im->h; i++){
    im->data[i] = hypot(gx.data[i],gy.data[i]);
  }
  if (out_gradient_directions){
    int i; for (i = 0; i < im->w*im->h; i++){
      out_gradient_directions[i] = atan2(gy.data[i],gx.data[i]);
    }
  }
  free(gx.data);
}

/**
 * @brief apply bluring to an image
 * @param im    pointer to image
 * @param rad   radius of blur, kernel size = rad*2+1
 * @param mode  one of: R1B_BLUR_BOX, R1B_BLUR_GAUSS
 */
void r1b_blur(r1b_im_t* im, int rad, int mode){
  r1b_im_t k1;
  if (mode == R1B_BLUR_GAUSS){
    k1 = r1b_make_kernel(rad*2+1,R1B_KERN_GAUSS1D);
  }else{
    k1 = r1b_zeros(rad*2+1,1);
    for (int i = 0; i < k1.w; i++){
      k1.data[i]=1.0/(float)k1.w;
    }
  }
  r1b_im_t k2 = r1b_copy_of(&k1);
  r1b_transpose(&k2);

  r1b_conv2d(im,&k1,R1B_BRDR_COPY);
  r1b_conv2d(im,&k2,R1B_BRDR_COPY);
  free(k1.data);
  free(k2.data);

}

/**
 * @brief apply canny edge detection to an image
 * @param im         pointer to image
 * @param blur_rad   radius for preprocessing blur, reduces noise
 * @param thresh_lo  lower threshold for the double thresholding step (weak edges)
 * @param thresh_hi  higher threshold for the double thresholding step (strong edges)
 */
void r1b_canny(r1b_im_t* im, int blur_rad, float thresh_lo, float thresh_hi){
  blur_rad  = ((int)blur_rad  == (int)R1B_INFER) ? 3   : blur_rad ;
  float th0 = ((int)thresh_lo == (int)R1B_INFER) ? 0.1 : thresh_lo;
  float th1 = ((int)thresh_hi == (int)R1B_INFER) ? 0.2 : thresh_hi;

  r1b_blur(im,blur_rad,R1B_BLUR_GAUSS);
  float* gdir = malloc(sizeof(float)*im->w*im->h);
  r1b_sobel(im,gdir);

  int i,j;
  float PI8 = M_PI/8;

  r1b_make_tmp0(im->w,im->h);

  for (i = 0; i < im->h; i++){
    for (j = 0; j < im->w; j++){
      int dx = 0;
      int dy = 0;
      float th = gdir[i*im->w+j];
      if (      -PI8 <= th && th <   PI8){ dx = 1;dy = 0;}
      else if (  PI8 <= th && th < 3*PI8){ dx = 1;dy = 1;}
      else if (3*PI8 <= th && th < 5*PI8){ dx = 0;dy = 1;}
      else if (5*PI8 <= th && th < 7*PI8){ dx =-1;dy = 1;}
      else if (7*PI8 <= th || th <-7*PI8){ dx =-1;dy = 0;}
      else if(-7*PI8 <= th && th <-5*PI8){ dx =-1;dy =-1;}
      else if(-5*PI8 <= th && th <-3*PI8){ dx = 0;dy =-1;}
      else if(-3*PI8 <= th && th <  -PI8){ dx = 1;dy =-1;}

      int o = i*im->w+j;
      if (im->data[o] <= r1b_get(im,j+dx,i+dy,R1B_BRDR_ZERO)){
        r1b_tmp0[o] = 0;
      }else if (im->data[i*im->w+j] < r1b_get(im,j-dx,i-dy,R1B_BRDR_ZERO)){
        r1b_tmp0[o] = 0;
      }else{
        r1b_tmp0[o] = im->data[o];
      }
    }
  }

  for (i = 0; i < im->h; i++){
    for (j = 0; j < im->w; j++){
      if (r1b_tmp0[i*im->w+j] >= th1){
        im->data[i*im->w+j] = 1;
      }else if (r1b_tmp0[i*im->w+j] < th0){
        im->data[i*im->w+j] = 0;
      }else{
        float p1 = im->data[R1B_MAX(i-1,0)      *im->w+R1B_MAX(j-1,0)      ];
        float p2 = im->data[R1B_MAX(i-1,0)      *im->w+j                   ];
        float p3 = im->data[R1B_MAX(i-1,0)      *im->w+R1B_MIN(j+1,im->w-1)];
        float p4 = im->data[       i            *im->w+R1B_MAX(j-1,0)      ];
        float p5 = im->data[       i            *im->w+R1B_MIN(j+1,im->w-1)];
        float p6 = im->data[R1B_MIN(i+1,im->h-1)*im->w+R1B_MAX(j-1,0)      ];
        float p7 = im->data[R1B_MIN(i+1,im->h-1)*im->w+j                   ];
        float p8 = im->data[R1B_MIN(i+1,im->h-1)*im->w+R1B_MIN(j+1,im->w-1)];

        if (p1 >= th1 || p2 >= th1 || p3 >= th1 || p4 >= th1 || p5 >= th1 || p6 >= th1 || p7 >= th1 || p8 >= th1){
          im->data[i*im->w+j] = 1;
        }else{
          im->data[i*im->w+j] = 0;
        }
        
      }
    }
  }
}

/**
 * @brief apply thresholding to an image
 * @param im   pointer to image
 * @param th   the threshold. pass R1B_INFER to use Otsu's method for automatically picking optimal threshold
 */
void r1b_threshold(r1b_im_t* im, float th){

  int i;
  if ((int)th == (int)R1B_INFER){
    // Otsu's method

    int nbin = 64;
    int hist[nbin];
    memset(hist,0,sizeof(int)*nbin);

    float vmin =  FLT_MAX;
    float vmax = -FLT_MAX;
    for (i= 0; i < im->h*im->w; i++ ){
      vmin = fmin(vmin,im->data[i]);
      vmax = fmax(vmax,im->data[i]); 
    }
    vmin-=0.01;
    vmax+=0.01;

    float bsize = (vmax-vmin)/(float)nbin;
    for (i= 0; i < im->h*im->w; i++ ){
      int n = (int)((im->data[i]-vmin)/bsize);
      hist[n]++;
    }

    float sum = 0;
    for (i=0; i<nbin; i++){sum += i * hist[i];}

    float sumB = 0;
    int wB = 0;
    int wF = 0;
    float varMax = 0;

    int threshold = 0;

    // http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
    for (i=0 ; i<nbin; i++) {
       wB += hist[i];               // Weight Background
       if (wB == 0) continue;

       wF = im->w*im->h - wB;       // Weight Foreground
       if (wF == 0) break;

       sumB += (float) (i * hist[i]);

       float mB = sumB / wB;            // Mean Background
       float mF = (sum - sumB) / wF;    // Mean Foreground

       // Calculate Between Class Variance
       float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

       // Check if new maximum found
       if (varBetween > varMax) {
          varMax = varBetween;
          threshold = i;
       }
    }
    th = vmin + ((float)threshold+0.5) * bsize;
    // printf("%d %f\n",threshold,th);
  }

  for (i= 0; i < im->h*im->w; i++ ){
    im->data[i] = (im->data[i]>=th);
  }
}

/**
 * @brief apply adaptive threshold to an image
 * @param im         pointer to image
 * @param rad        radius of neighborhood for each pixel
 * @param bias       adjusts brightness: pixel is considered below the threshold if it is this factor lower than its neighborhood
 * @param blur_mode  blurring kernel for averaging the neighborhood, e.g. R1B_BLUR_GAUSS, R1B_BLUR_BOX
 */
void r1b_threshold_adaptive(r1b_im_t* im, int rad, float bias, int blur_mode){
  int i;
  r1b_make_tmp0(im->w,im->h);
  r1b_im_t tmp;
  tmp.w = im->w;
  tmp.h = im->h;
  tmp.data = r1b_tmp0;
  memcpy(r1b_tmp0, im->data, im->w*im->h*sizeof(float));

  r1b_blur(&tmp,rad,blur_mode);

  for (i= 0; i < im->h*im->w; i++ ){
    if (im->data[i]<r1b_tmp0[i]-bias*r1b_tmp0[i]){
      im->data[i] = 0;
    }else{
      im->data[i] = 1;
    }
  }
}

/** @file */ 
#endif // include guard

// note: the license below applies to this file (r1b.h) only, other resources
// included in the project might be under a different license
/* =========================================================================
MIT License

Copyright (c) 2020 Lingdong Huang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
========================================================================= */
