//gcc examples/filters.c
#include "../r1b.h"

int main(){
  r1b_font_t font = r1b_load_font_hex("fonts/unifont.hex",16,0,INT_MAX,R1B_FLAG_SORTED);

  r1b_im_t canvas = r1b_zeros(384,1290);

  {
    r1b_im_t src = r1b_read("examples/assets/david.png");

    r1b_im_t dst1 = r1b_copy_of(&src);
    r1b_im_t dst2 = r1b_copy_of(&src);
    r1b_im_t dst3 = r1b_copy_of(&src);
    r1b_im_t dst4 = r1b_copy_of(&src);
    r1b_im_t dst5 = r1b_copy_of(&src);
    r1b_im_t dst6 = r1b_copy_of(&src);


    r1b_normalize(&dst1,0,0.8);

    r1b_dither(&dst1,R1B_DTHR_ORD);

    r1b_canny( &dst2,R1B_INFER,R1B_INFER,R1B_INFER);

    r1b_sobel(&dst3,NULL);

    r1b_dither(&dst3,R1B_DTHR_FS);

    r1b_threshold(&dst4,R1B_INFER);

    r1b_blur(&dst5,1,R1B_BLUR_GAUSS);
    r1b_threshold_adaptive(&dst5,5,-0.08,R1B_BLUR_GAUSS);

    r1b_dither(&dst6,R1B_DTHR_FS);
    
    r1b_blit(&canvas,&dst2,R1B_PATTERN(SOLID),0,0,src.w,src.h*2,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst1,R1B_PATTERN(SOLID),0,src.h,src.w,src.h*2,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst3,R1B_PATTERN(SOLID),0,src.h*2,src.w,src.h*3,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst4,R1B_PATTERN(CROSS),0,src.h*3,src.w,src.h*4,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst5,R1B_PATTERN(SOLID),0,src.h*4,src.w,src.h*5,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst6,R1B_PATTERN(SOLID),0,src.h*5,src.w,src.h*6,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);

    r1b_free(&dst1); r1b_free(&dst2); r1b_free(&dst3);
    r1b_free(&dst4); r1b_free(&dst5); r1b_free(&dst6);
    r1b_free(&src);

  }

  {
    r1b_im_t src = r1b_zeros(204,215);
    r1b_text(&src,L"David is a masterpiece of\nRenaissance sculpture\ncreated in marble between\n1501 \
and 1504 by the\nItalian artist\nMichelangelo. 大衛像是文\n藝復興時代米开朗基罗的杰\n作。於一五零壹年至一五零\n肆年雕成。(Wikipedia)",0,0,&font,1,R1B_BLIT_SET,0);

    r1b_im_t img = r1b_read("examples/assets/upsample_test.png");
    r1b_threshold(&img,R1B_INFER);
    r1b_blit(&src,&img,R1B_PATTERN(SOLID),0,150,200,150+img.h,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);


    r1b_im_t dst1 = r1b_copy_of(&src);
    r1b_bedstead(&dst1,2);

    
    r1b_im_t dst2 = r1b_copy_of(&dst1);
    r1b_im_t kern = r1b_make_kernel(3,R1B_KERN_ELLIPSE);
    r1b_dilate(&dst2,&kern);

    r1b_sobel( &dst2, NULL);
    r1b_threshold(&dst2,0.5);


    r1b_im_t dst3 = r1b_copy_of(&dst1);
    r1b_blur(&dst3,5,R1B_BLUR_GAUSS);
    r1b_dither(&dst3,R1B_DTHR_FS);

    r1b_im_t dst4 = r1b_copy_of(&src);
    r1b_im_t kern2 = r1b_make_kernel(7,R1B_KERN_ELLIPSE);
    r1b_bedstead(&dst4,3);
    r1b_erode(&dst4,&kern2);


    r1b_blit(&canvas,&src, R1B_PATTERN(SOLID),180,0,src.w+180,src.h,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);

    r1b_blit(&canvas,&dst1,R1B_PATTERN(SOLID),180,src.h,src.w+180,src.h*2,0,0,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst2,R1B_PATTERN(SOLID),180,src.h*2,src.w+180,src.h*3,0,215,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst3,R1B_PATTERN(SOLID),180,src.h*3,src.w+180,src.h*4,0,430,R1B_BRDR_WRAP,R1B_BLIT_OR);
    r1b_blit(&canvas,&dst4,R1B_PATTERN(SOLID),180,src.h*4,src.w+180,src.h*5,200,1200,R1B_BRDR_WRAP,R1B_BLIT_OR);
    
    r1b_text_ascii(&canvas,"Top left to Bottom Right:\nCanny Edge\nOtsu Threshold\nCanny + Ordered dither\nBedstead Upscale 2X\nSobel + FS Dither\nDilate + Sobel + Thresh\nOtsu Thresh + Pattern fill\nGaussin Blur + FS Dither\nAdaptive threshold\nBedstead 8X + Erosion\nFloyd Steinburg Dither",180,1075,R1B_FONT_FG8X12,1,R1B_BLIT_SET,0);

    r1b_free(&dst1); r1b_free(&dst2); r1b_free(&dst3 );
    r1b_free(&dst4); r1b_free(&kern); r1b_free(&kern2);
    r1b_free(&src);

  }

  r1b_snapshot("examples/out/filters.png",&canvas);

  r1b_lpr("Printer_USB_Thermal_Printer",&canvas);

  r1b_free(&canvas);
  r1b_destroy_font(&font);
  r1b_cleanup();
}