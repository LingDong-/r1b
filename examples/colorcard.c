#include "../r1b.h"

r1b_im_t* get_nth_pattern(n){
  // access each builtin pattern by index
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
int main(){
    r1b_im_t im = r1b_zeros(384,1150);
    
    for (int i = 0; i < 24; i++){
        r1b_im_t* pttn = get_nth_pattern(i);
        // draw a rect for each pattern
        r1b_rect(&im,
            0,    i*50-50,   // upper left corner
            80,  (i+1)*50,   // lower right corner
            pttn, R1B_BLIT_SET);
    }

    r1b_im_t img = r1b_read("examples/assets/gradient.png");

    r1b_resample(&img,80,1250,R1B_SMPL_BILINEAR);

    r1b_im_t img2 = r1b_copy_of(&img);

    r1b_dither(&img,R1B_DTHR_FS);
    r1b_paste(&im,&img,152,-100);

    r1b_dither(&img2,R1B_DTHR_ORD);
    r1b_paste(&im,&img2,304,-100);
    
    r1b_snapshot("examples/out/colorcard.png",&im);

    r1b_lpr("Printer_USB_Thermal_Printer",&im);
}