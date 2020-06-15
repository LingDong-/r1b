//gcc examples/bottles.c
#include "../r1b.h"
#include "utils/random.h"

r1b_im_t* get_nth_pattern(n){
  switch (n) {
    case  0: return R1B_PATTERN(SOLID);
    case  1: return R1B_PATTERN(GRAY5);
    case  2: return R1B_PATTERN(GRAY4);
    case  3: return R1B_PATTERN(GRAY3);
    case  4: return R1B_PATTERN(GRAY2);
    case  5: return R1B_PATTERN(GRAY1);
    case  6: return R1B_PATTERN(EMPTY);
    case  7: return R1B_PATTERN(GRID1);
    case  8: return R1B_PATTERN(GRID2);
    case  9: return R1B_PATTERN(DOTS1);
    case 10: return R1B_PATTERN(DOTS2);
    case 11: return R1B_PATTERN(DOTSR);
    case 12: return R1B_PATTERN(HRZL1);
    case 13: return R1B_PATTERN(HRZL2);
    case 14: return R1B_PATTERN(VRTL1);
    case 15: return R1B_PATTERN(VRTL2);
    case 16: return R1B_PATTERN(DGNLL);
    case 17: return R1B_PATTERN(DGNLR);
    case 18: return R1B_PATTERN(CROSS);
    case 19: return R1B_PATTERN(BRICK);
    case 20: return R1B_PATTERN(SCALE);
    case 21: return R1B_PATTERN(WAVES);
    case 22: return R1B_PATTERN(CHESS);
    case 23: return R1B_PATTERN(DMOND);
  }
  return NULL;
}

void draw_tree(r1b_im_t* im, float x, float y, float a, float aa, float d, int n){
  if (d < 2) {
    return;
  }
  float x0=x+cos( a-aa)*d;
  float y0=y+sin( a-aa)*d;
  float x1=x+cos( a+aa)*d;
  float y1=y+sin( a+aa)*d;

  r1b_line(im,x,y,x0,y0,1,R1B_BLIT_SET);
  r1b_line(im,x,y,x1,y1,1,R1B_BLIT_SET);
  draw_tree(im,x0,y0,a-aa,aa,d*(0.2+0.8*(float)rand()/(float)RAND_MAX),n-1);
  draw_tree(im,x1,y1,a+aa,aa,d*(0.2+0.8*(float)rand()/(float)RAND_MAX),n-1);
}

void draw_bottle(r1b_im_t* im, float x, float y, float z){
  int h = rand()%40+10;
  int w = rand()%100+50;
  float* X = (float*)alloca(h*2*sizeof(float));
  float* Y = (float*)alloca(h*2*sizeof(float));
  for (int i = 0; i < h; i++ ){
    float yy = (float)i*5;
    float xx = noise(yy*0.01,0,z)*(float)(w);
    X[i] =       x+xx; Y[i]       = y-(float)h*5+yy;
    X[h*2-i-1] = x-xx; Y[h*2-i-1] = y-(float)h*5+yy;
  }

  r1b_polygon(im,X,Y,h*2,get_nth_pattern(rand()%21+3),R1B_BLIT_SET,R1B_POLY_CONCAVE);
  r1b_lines(im,X,Y,h*2,1,1,R1B_BLIT_SET);

  r1b_ellipse     (im,x, Y[0], (X[0]-X[h*2-1])/2, 5, 0, R1B_PATTERN(EMPTY), R1B_BLIT_SET);
  r1b_line_ellipse(im,x, Y[0], (X[0]-X[h*2-1])/2, 5, 0, 32, 1, R1B_BLIT_SET);

  if (h > 40 && rand()%100>50) {
    draw_tree(im,x, Y[0]+5,-M_PI/2,0.3,20,5);
  }
}

int main() {
  // srand(0);
  // noiseSeed(0);

  r1b_im_t im = r1b_zeros(1200, 384);

  r1b_im_t tablecloth = r1b_zeros(32,32);
  r1b_set(&tablecloth,0,0,1,R1B_BLIT_SET);

  r1b_rect(&im,0,200,1200,384,&tablecloth,R1B_BLIT_SET);

  for (int i = 0; i < 20; i++ ){
    draw_bottle(&im, 100+rand()%1000,300+i*2, i);   
  }

  r1b_text(&im, L"Bottles", 20, 20, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 1);

  r1b_snapshot("examples/out/bottles.png", &im);

  r1b_transpose_flip(&im);
  
  r1b_lpr("Printer_USB_Thermal_Printer",&im);

  r1b_free(&im);
  r1b_free(&tablecloth);
  r1b_cleanup();

}