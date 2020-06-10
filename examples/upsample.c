//gcc examples/upsample.c
#include "../r1b.h"

int main(){
  r1b_font_t font = r1b_load_font_hex("fonts/unifont.hex",16,0,INT_MAX,R1B_FLAG_SORTED);

  r1b_im_t canvas = r1b_zeros(384,1860);

  r1b_im_t src = r1b_zeros(128,128);
  r1b_text(&src,L"SOME TEXT 蠅頭\n檗窠 more text\nαβγδεζηθικλμνξ",8,8,&font,1,R1B_BLIT_SET,0);
  r1b_im_t img = r1b_read("examples/assets/upsample_test.png");
  r1b_paste(&src,&img,0,64);
  r1b_paste(&canvas,&src,0,0);

  {
    r1b_im_t dst = r1b_copy_of(&src);
    r1b_upsample2x(&dst, R1B_UP2X_SAA5050);
    r1b_paste(&canvas,&dst,0,128);
    r1b_free(&dst);

    r1b_text_ascii(&canvas,"SA5050",0,128,R1B_FONT_FG8X12,1,R1B_BLIT_SET,0);
  }

  {
    r1b_im_t dst = r1b_copy_of(&src);
    r1b_upsample2x(&dst, R1B_UP2X_EAGLE);
    r1b_paste(&canvas,&dst,0,128+256);
    r1b_free(&dst);

    r1b_text_ascii(&canvas,"Eagle",0,128+256,R1B_FONT_FG8X12,1,R1B_BLIT_SET,0);
  }

  {
    r1b_im_t dst = r1b_copy_of(&src);
    r1b_upsample2x(&dst, R1B_UP2X_EPX);
    r1b_paste(&canvas,&dst,0,128+256*2);
    r1b_free(&dst);

    r1b_text_ascii(&canvas,"EPX",0,128+256*2,R1B_FONT_FG8X12,1,R1B_BLIT_SET,0);
  }

  {
    r1b_im_t dst = r1b_copy_of(&src);
    r1b_upsample2x(&dst, R1B_UP2X_HQX);
    r1b_paste(&canvas,&dst,0,128+256*3);
    r1b_free(&dst);

    r1b_text_ascii(&canvas,"hq2x",0,128+256*3,R1B_FONT_FG8X12,1,R1B_BLIT_SET,0);
  }

  {
    r1b_im_t dst = r1b_copy_of(&src);
    r1b_bedstead(&dst,3);

    r1b_paste(&canvas,&dst,0,128+256*4);
    r1b_free(&dst);

    r1b_text_ascii(&canvas,"Bedstead",0,128+256*4,R1B_FONT_FG8X12,1,R1B_BLIT_SET,0);
  }

  // r1b_dither(&canvas,R1B_DTHR_FS);

  r1b_snapshot("examples/out/upsample.png",&canvas);

  r1b_destroy_font(&font);
  r1b_free(&canvas);
  r1b_cleanup();
}