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
  #define R1B_CONFIG_LINE3D_EPSILON 0.01
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define STB_IMAGE_IMPLEMENTATION
#include R1B_CONFIG_STBI_PATH

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include R1B_CONFIG_STBIW_PATH


#define R1B_INFER          0

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

#define R1B_SHDR_NONE      20
#define R1B_SHDR_FLAT      21
#define R1B_SHDR_NDOTL     22
#define R1B_SHDR_NDOTLF    23

#define R1B_FLAG_SORTED    1



#ifndef M_PI
  #define M_PI   3.14159265358979323846264338327950288
#endif

typedef struct {
  int w;
  int h;
  float* data;
} r1b_im_t;

typedef struct {
  int h;
  char* glyphs;
  int n;
  uint32_t* offsets;
  uint8_t*  sizes;
  uint16_t* cmap;
  int flags;
} r1b_font_t;

typedef struct {
  float* X;
  float* Y;
  float* Z;
  int* tris;
  float* norms;
  int n_vtx;
  int n_tri;
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

#define R1B_DESTROY_PATTERN(x) if (r1b_pttn_ ## x) {free(r1b_pttn_ ## x);};

#ifndef R1B_CONFIG_NO_FG8X12
  // converted from freeglut/freeglut_font_data.c
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
  r1b_im_t r1b_read(const char* path){  
    int width, height, channels;
    unsigned char *image = stbi_load(path,
                                   &width,
                                   &height,
                                   &channels,
                                   STBI_grey);
    
    float* data = (float*)malloc(width*height*sizeof(float));
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
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
  void r1b_snapshot(const char* path, r1b_im_t* im){
    unsigned char *image = (unsigned char*)malloc(sizeof(unsigned char)*im->w*im->h);
    for (int i = 0; i < im->h; i++ ){
      for (int j = 0; j < im->w; j++ ){
        image[i*im->w+j] = (unsigned char)(int) ((1.0-fmin(fmax(im->data[i*im->w+j],0.0),1.0)) * 255.0);
      }
    }
    void* ext = (void*)path + strlen(path);
    while (ext > (void*)path && *(char*)ext != '.') {
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

r1b_im_t r1b_zeros(int w, int h){
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)calloc(w*h,sizeof(float));
  return im;
}

r1b_im_t r1b_ones(int w, int h){
  int l = w*h;
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)malloc(l*sizeof(float));
  for (int i = 0; i < l; i++){
    im.data[i] = 1.0;
  }
  return im;
}

r1b_im_t r1b_from_array(int w, int h, float* arr){
  int l = w*h;
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)malloc(l*sizeof(float));
  memcpy(im.data, arr, l*sizeof(float));
  return im;
}

r1b_im_t r1b_infs(int w, int h){
  int l = w*h;
  r1b_im_t im;
  im.w = w;
  im.h = h;
  im.data = (float*)malloc(l*sizeof(float));
  for (int i = 0; i < l; i++){
    im.data[i] = FLT_MAX;
  }
  return im;
}


void r1b_free(r1b_im_t* im){
  free(im->data);
  im->data = NULL;
}

void r1b_transpose(r1b_im_t* im){
  // TODO: cache friendly
  r1b_make_tmp0(im->w,im->h);
  for (int i = 0; i < im->h; i++){
    for (int j = 0; j < im->w; j++){
      r1b_tmp0[j*im->h+i] = im->data[i*im->w+j];
    }
  }
  int tmp = im->w;
  im->w = im->h;
  im->h = tmp;
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

void r1b_transpose_flip(r1b_im_t* im){
  // TODO: cache friendly
  r1b_make_tmp0(im->w,im->h);
  for (int i = 0; i < im->h; i++){
    for (int j = 0; j < im->w; j++){
      r1b_tmp0[j*im->h+i] = im->data[i*im->w+im->w-1-j];
    }
  }
  int tmp = im->w;
  im->w = im->h;
  im->h = tmp;
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}


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

r1b_im_t r1b_copy_of(r1b_im_t* im){
  int s = im->w*im->h*sizeof(float);
  r1b_im_t dst;
  dst.w = im->w;
  dst.h = im->h;
  dst.data = (float*)malloc(s);
  memcpy(dst.data, im->data, s);
  return dst;
}

void r1b_copy_to(r1b_im_t* im, r1b_im_t* dst){
  memcpy(dst->data, im->data, im->w*im->h*sizeof(float));
}

void r1b_dither_fs(r1b_im_t* im) {
  r1b_make_tmp0(im->w,im->h);
  r1b_make_tmp1(im->w,im->h);

  memset(r1b_tmp1,0,im->w*im->h*sizeof(float));

  for (int i = 0; i < im->h; i++) {
    for (int j = 0; j < im->w; j++) {
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

void r1b_dither_ord(r1b_im_t* im){
  r1b_make_tmp0(im->w,im->h);

  for (int i = 0; i < im->h; i++ ){
    for (int j = 0; j < im->w; j++ ){

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

void r1b_log(r1b_im_t* im){
  for (int i = 0; i < im->h; i++) {
    for (int j = 0; j < im->w; j++) {
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

char* r1b_encode(r1b_im_t* im, int* n_bytes_written){
  int l0 = im->w%256;
  int ll = (int)(im->w/256);
  int num_bytes = ((im->h+23)/24)*8 + 2 + im->w*3*((im->h+23)/24);
  int cnt_bytes = 0;

  char* bytes = (char*) malloc(sizeof(char)*num_bytes);

  R1B_PUT8(0x1b); R1B_PUT8(0x40);

  for (int r = 0; r < im->h; r+= 24){
    //ESC * m nL nH
    R1B_PUT8(0x1b);R1B_PUT8(0x2a);R1B_PUT8(33);R1B_PUT8((char)l0);R1B_PUT8((char)ll);
    for (int c = 0; c < im->w; c ++ ){
      for (int n = 0; n < 3; n++ ){
        char x = 0;
        for (int h = 0; h < 8; h++ ){
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

void r1b_encode2file(const char* path, r1b_im_t* im){
  FILE * fp;
  fp = fopen(path, "wb");
  int n;
  char* buf = r1b_encode(im,&n);
  fwrite(buf , 1, n, fp);
  fclose(fp);
}

void r1b_lpr(const char* printer, r1b_im_t* im){
  char buf[256];
  r1b_encode2file("r1b_tmp",im);
  sprintf(buf,"lpr -P%s -o raw r1b_tmp",printer);
  system(buf);
}


void r1b_resample_nearest(r1b_im_t* im, int w, int h){
  r1b_make_tmp0(w,h);

  float hs = (float)im->h/(float)h;
  float ws = (float)im->w/(float)w;

  for (int i = 0; i < h; i++){
    for (int j = 0; j < w; j++){
    
      int ii = R1B_MIN( im->h-1, (int)round((float)i*hs) );
      int jj = R1B_MIN( im->w-1, (int)round((float)j*ws) );
      r1b_tmp0[i*w+j] = im->data[ii*im->w+jj];
    }
  }
  im->w = w;
  im->h = h;
  im->data = r1b_tmp0;

  r1b_tmp0_size = 0;
  r1b_tmp0 = NULL;
}

void r1b_resample_bilinear(r1b_im_t* im, int w, int h){
  r1b_make_tmp0(w,h);

  float hs = (float)im->h/(float)h;
  float ws = (float)im->w/(float)w;

  for (int i = 0; i < h; i++){
    for (int j = 0; j < w; j++){
    
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
  im->w = w;
  im->h = h;
  im->data = r1b_tmp0;

  r1b_tmp0_size = 0;
  r1b_tmp0 = NULL;
}


void r1b_resample(r1b_im_t* im, int w, int h, int mode){
  switch(mode){
    case R1B_SMPL_BILINEAR:
      r1b_resample_bilinear(im,w,h);
      break;
    case R1B_SMPL_NN:
    default:
      r1b_resample_nearest(im,w,h);
  }
}

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

void r1b_conv2d(r1b_im_t* im, r1b_im_t* kern, int border) {
  r1b_make_tmp0(im->w,im->h);

  int khw = kern->w/2;
  int khh = kern->h/2;

  for (int i = 0; i < im->h; i++ ){
    for (int j = 0; j < im->w; j++ ){
      float sum = 0;
      for (int ki = 0; ki < kern->h; ki ++ ){
        for (int kj = 0; kj < kern->w; kj ++ ){
          sum += r1b_get(im,j-khw+kj, i-khh+ki, border) * kern->data[ki*kern->w+kj];
        }
      }
      r1b_tmp0[i*im->w+j] = sum;
    }
  }
  memcpy(im->data, r1b_tmp0, im->w*im->h*sizeof(float));
}

#define R1B_PT_IN_PL(x,y,x0,y0,x1,y1) ((((x)-(x0))*((y1)-(y0)) - ((y)-(y0))*((x1)-(x0)))<=0)
#define R1B_PT_IN_TRI(x,y,x0,y0,x1,y1,x2,y2) ( R1B_PT_IN_PL(x,y,x0,y0,x1,y1) && R1B_PT_IN_PL(x,y,x1,y1,x2,y2) && R1B_PT_IN_PL(x,y,x2,y2,x0,y0) )

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

  for (int y=ymin; y <= ymax; y++){
    for (int x=xmin; x <= xmax; x++){
      if (R1B_PT_IN_TRI((float)x+0.5,(float)y+0.5,x0,y0,x1,y1,x2,y2)){
        float v = pttn->data[(y % pttn->h) * pttn->w + (x % pttn->w)];
        r1b_set(im,x,y,v,mode);
      }
    }
  }
}

void r1b_rect(r1b_im_t* im,float x0 ,float y0 ,float x1 ,float y1 , r1b_im_t* pttn, int mode){
  int xmin = (int)round(fmin(x0,x1));
  int xmax = (int)round(fmax(x0,x1));
  int ymin = (int)round(fmin(y0,y1));
  int ymax = (int)round(fmax(y0,y1));

  for (int y=ymin; y <= ymax; y++){
    for (int x=xmin; x <= xmax; x++){
      float v = pttn->data[(y % pttn->h) * pttn->w + (x % pttn->w)];
      r1b_set(im,x,y,v,mode);
    }
  }
}

#define R1B_LINE_STEP(sx0,sx1,sy0,sy1,x) (((sx0) == (sx1)) ? (sy1) : ((int)round((float)(sy0)+(float)((x)-(sx0))*(float)((sy1)-(sy0))/(float)((sx1)-(sx0)))) )

void r1b_line(r1b_im_t* im, float x0 ,float y0 ,float x1 ,float y1, float val, int mode){

  int sx0 = (int)round(x0-0.5);
  int sy0 = (int)round(y0-0.5);
  int sx1 = (int)round(x1-0.5);
  int sy1 = (int)round(y1-0.5);
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


void r1b_lines(r1b_im_t* im, float* Xs, float* Ys, int n, int close, float val, int mode){
  int m = n - 1 + (close & 1);
  for (int i=0; i < m; i++ ){
    r1b_line(im, Xs[i], Ys[i], Xs[(i+1)%n], Ys[(i+1)%n], val, mode);
  }
}

void r1b_thick_line(r1b_im_t* im, float x0, float y0, float x1, float y1, float val, int thick, int mode){
  int dx = x1 > x0 ? 1 : -1;
  int dy = y1 > y0 ? 1 : -1;
  r1b_line(im,x0,y0,x1,y1,val,mode);

  for (int i = 1; i <= thick; i++) {
    float dxi = (float)(i*dx);
    float dyi = (float)(i*dy);
    r1b_line(im,x0+dxi,y0,x1,y1-dyi,val,mode);
    r1b_line(im,x0,y0+dyi,x1-dxi,y1,val,mode);
  }
}

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
      for (int j = 5; j < linelen; j+=2){
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

void r1b_destroy_font(r1b_font_t* font){
  if (font->glyphs)free(font->glyphs);
  if (font->sizes)free(font->sizes);
  if (font->cmap)free(font->cmap);
  if (font->offsets)free(font->offsets);
}

int r1b_glyph_index_lin_search(r1b_font_t* font, int cp){
  for (int i = 0; i < font->n; i++){
    if (font->cmap[i] == cp){
      return i;
    }
  }
  return -1;
}

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

int r1b_glyph_index(r1b_font_t* font, int cp){
  if (font->flags & R1B_FLAG_SORTED){
    return r1b_glyph_index_bin_search(font, cp, 0, font->n);
  }else{
    return r1b_glyph_index_lin_search(font, cp);
  }
}

int r1b_putchar(r1b_im_t* im, int cp, int x, int y, r1b_font_t* font,float val, int mode, int highlight){
  int idx = r1b_glyph_index(font,cp);
  if (idx < 0){
    return 0;
  }
  int off = (font->offsets[idx]*font->h)/2;
  int w = font->sizes[idx]*4;

  for (int r = 0; r < font->h; r ++) {
    for (int c = 0; c < w; c ++ ){
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

    unsigned char *s = buf;
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

void r1b_text_utf8(r1b_im_t* im, char* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight){
  wchar_t wstr[strlen(str)];
  void* next = (void*)str;
  int e;
  int idx = 0;
  while(next <= (void*)str+strlen(str)){
    next = r1b_utf8_decode(next, (uint32_t *)&wstr[idx], &e);
    idx++;
  }
  wstr[idx] = 0;
  r1b_text(im,wstr,x,y,font,val,mode,highlight);
}

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


float r1b_area(float* X, float* Y, int n) {
  // ported from https://github.com/cmu462/DrawSVG
  float a = 0.0f;
  for(int p=n-1,q=0; q<n; p=q++) {
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

int r1b_triangulate(float* X, float* Y, int n, int* triangles) {
  // ported from https://github.com/cmu462/DrawSVG
  // allocate and initialize list of vertices in polygon
  if ( n < 3 ) return 0;
  int* V = (int*)alloca(n*sizeof(int));
  // we want a counter-clockwise polygon in V
  if ( 0.0f < r1b_area(X,Y,n) ) {
    for (int v=0; v<n; v++) V[v] = v;
  } else {
    for(int v=0; v<n; v++) V[v] = (n-1)-v;
  }
  int nv = n;
  // remove nv-2 Vertices, creating 1 triangle every time
  int count = 2*nv;   // error detection 
  int m = 0;
  for(int v = nv - 1; nv > 2;) {
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

void r1b_polygon_convex(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode){
  for (int i = 1; i < n-1; i++ ){
    r1b_triangle(im,
      Xs[0],  Ys[0],
      Xs[i],  Ys[i],
      Xs[i+1],Ys[i+1],pttn,mode);
  }
}

void r1b_polygon_concave(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode){
  int tris[n*3];
  int n_tris = r1b_triangulate(Xs,Ys,n,tris);
  for (int i = 0; i < n_tris; i++) {
    r1b_triangle(im,
      Xs[tris[i*3  ]],Ys[tris[i*3  ]],
      Xs[tris[i*3+1]],Ys[tris[i*3+1]],
      Xs[tris[i*3+2]],Ys[tris[i*3+2]],pttn,mode);
  }
}

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

  for (int y = ymin; y <= ymax; y ++ ){
    for (int x = xmin; x <= xmax; x ++ ){
      float fx = (float)x;
      float fy = (float)y;
      if (ang != 0){
        float gx = fx-cx;
        float gy = fy-cy;
        fx = cx + (gx * costh - gy * sinth);
        fy = cy + (gx * sinth + gy * costh);
      }
      if R1B_PT_IN_ELL(cx,cy,fx+0.5,fy+0.5,rx,ry){
        float v = pttn->data[(y % pttn->h) * pttn->w + (x % pttn->w)];
        r1b_set(im,x,y,v,mode);
      }  
    }
  }
}

void r1b_line_ellipse(r1b_im_t* im, float cx, float cy, float rx, float ry, float ang, int detail, float val, int mode){
  
  float costh = cos(ang);
  float sinth = sin(ang);
  float px, py;

  for (int i=0; i < detail+1; i ++){
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

  for (int y=ymin; y <= ymax; y++){
    for (int x=xmin; x <= xmax; x++){
      int j = ix0 + dx * (x-xmin) +isx;
      int i = iy0 + dy * (y-ymin) +isy;
      int u = r1b_get(msk,j,i,bdmode);
      if (u >= 0.5){
        float v = r1b_get(src,j,i,bdmode);
        r1b_set(dst,x,y,v,mode);
      }
    }
  }
}


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

  obj.X = malloc(sizeof(float)*nv);
  obj.Y = malloc(sizeof(float)*nv);
  obj.Z = malloc(sizeof(float)*nv);

  obj.tris = malloc(sizeof(int)*nf*3);
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
      for (int i = 2; i < linelen+1; i++){
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
      for (int i = 2; i < linelen+1; i++){
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

void r1b_mesh_bbox(r1b_mesh_t* mesh, float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax){
  *xmin = FLT_MAX;
  *ymin = FLT_MAX;
  *zmin = FLT_MAX;
  *xmax = -FLT_MAX;
  *ymax = -FLT_MAX;
  *zmax = -FLT_MAX;
  for (int i = 0; i < mesh->n_vtx; i++){
    *xmin = fmin(*xmin,mesh->X[i]);
    *ymin = fmin(*ymin,mesh->Y[i]);
    *zmin = fmin(*zmin,mesh->Z[i]);
    *xmax = fmax(*xmax,mesh->X[i]);
    *ymax = fmax(*ymax,mesh->Y[i]);
    *zmax = fmax(*zmax,mesh->Z[i]);
  }
}

void r1b_normalize_mesh(r1b_mesh_t* mesh){
  float xmin,ymin,zmin,xmax,ymax,zmax;
  r1b_mesh_bbox(mesh,&xmin,&ymin,&zmin,&xmax,&ymax,&zmax);

  float s = R1B_MAX(R1B_MAX(xmax-xmin,ymax-ymin),zmax-zmin);
  float px = (s - (xmax-xmin)) / 2;
  float py = (s - (ymax-ymin)) / 2;
  float pz = (s - (zmax-zmin)) / 2;
  for (int i = 0; i < mesh->n_vtx; i++){
    mesh->X[i] = (mesh->X[i]-xmin+px)*(2/s)-1;
    mesh->Y[i] = (mesh->Y[i]-ymin+py)*(2/s)-1;
    mesh->Z[i] = (mesh->Z[i]-zmin+pz)*(2/s)-1;
  }
  // r1b_mesh_bbox(mesh,&xmin,&ymin,&zmin,&xmax,&ymax,&zmax);
  // printf("%f %f %f, %f %f %f\n",xmin,ymin,zmin,xmax,ymax,zmax);
}

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

  for (int y=ymin; y <= ymax; y++){
    for (int x=xmin; x <= xmax; x++){

      float det= R1B_BARY_DET(x+0.5,y+0.5,xx0,yy0,xx1,yy1,xx2,yy2);
      float u  = R1B_BARY_U(  x+0.5,y+0.5,xx0,yy0,xx1,yy1,xx2,yy2)/det;
      float v  = R1B_BARY_V(  x+0.5,y+0.5,xx0,yy0,xx1,yy1,xx2,yy2)/det;
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

void r1b_line3d(r1b_im_t* im, r1b_im_t* depth, int depth_read, float f, float x0 ,float y0, float z0, float x1 ,float y1, float z1, float val, int mode){

  float u0[3] = {x0,y0,z0};
  float v0[] = R1B_MAT_PROJ(f,u0);
  float xx0 = v0[0]+im->w/2;
  float yy0 =-v0[1]+im->h/2;

  float u1[3] = {x1,y1,z1};
  float v1[] = R1B_MAT_PROJ(f,u1);
  float xx1 = v1[0]+im->w/2;
  float yy1 =-v1[1]+im->h/2;

  int sx0 = (int)round(xx0-0.5);
  int sy0 = (int)round(yy0-0.5);
  int sx1 = (int)round(xx1-0.5);
  int sy1 = (int)round(yy1-0.5);
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

void r1b_transform_mesh(r1b_mesh_t* mesh, float* mat){
  for (int i = 0; i < mesh->n_vtx; i++){
    float u[3] = {mesh->X[i],mesh->Y[i],mesh->Z[i]};
    float v[] = R1B_MAT_TFRM(mat,u);
    mesh->X[i] = v[0];
    mesh->Y[i] = v[1];
    mesh->Z[i] = v[2];
  }
}

#define R1B_V3_CROSS(a1,a2,a3,b1,b2,b3) {(a2)*(b3)-(a3)*(b2),(a3)*(b1)-(a1)*(b3),(a1)*(b2)-(a2)*(b1)}
#define R1B_V3_DOT(a1,a2,a3,b1,b2,b3)   ((a1)*(b1)+(a2)*(b2)+(a3)*(b3))

#define R1B_V3_MAG(a1,a2,a3) (sqrt((a1)*(a1)+(a2)*(a2)+(a3)*(a3)))


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
    float v1[3] = {mesh->X[a]-mesh->X[b],mesh->Y[a]-mesh->Y[b],mesh->Z[a]-mesh->Z[b]};

    float l0 = R1B_V3_MAG(v0[0],v0[1],v0[2]);
    float l1 = R1B_V3_MAG(v1[0],v1[1],v1[2]);

    float nml[] = R1B_V3_CROSS(
      v0[0]/l0,v0[1]/l0,v0[2]/l0,
      v1[0]/l1,v1[1]/l1,v1[2]/l1
    );

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

void r1b_render_mesh(r1b_im_t* im, r1b_im_t* depth, r1b_mesh_t* mesh, float f, r1b_im_t* pttn, float* light, int wire_val, int shdr, int wire){

  for (int i = 0; i < mesh->n_tri; i++){
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

        float l0 = R1B_V3_MAG(v0[0],v0[1],v0[2]);
        float l1 = R1B_V3_MAG(v1[0],v1[1],v1[2]);

        float nml[] = R1B_V3_CROSS(
          v0[0]/l0,v0[1]/l0,v0[2]/l0,
          v1[0]/l1,v1[1]/l1,v1[2]/l1
        );
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



#endif // include guard