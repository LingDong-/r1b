//gcc examples/mesh.c
#include "../r1b.h"

int main(){
  r1b_font_t font = r1b_load_font_hex("fonts/unifont.hex",16,0,INT_MAX,R1B_FLAG_SORTED);

  r1b_im_t hstack = r1b_zeros(3000,384);

  r1b_mesh_t mesh = r1b_load_obj("examples/assets/teapot.obj");
  r1b_normalize_mesh(&mesh);

  float rotx[] = R1B_MAT_ROTX(-0.2);
  float roty[] = R1B_MAT_ROTY(0);
  float rotz[] = R1B_MAT_ROTZ(0);
  
  float rotxy[]= R1B_MAT_MULT(roty,rotx);
  float rot[]  = R1B_MAT_MULT(rotz,rotxy);
  float trl[]  = R1B_MAT_TRSL(0,0,4.2);
  float tfm[]  = R1B_MAT_MULT(trl,rot);

  r1b_transform_mesh(&mesh, tfm);

  r1b_compute_vertex_normals(&mesh);

  {
    r1b_im_t im = r1b_zeros(500,384);
    r1b_im_t depth = r1b_infs(500,384);
    r1b_render_mesh(&im, &depth, &mesh, 1000, R1B_PATTERN(EMPTY), NULL, 1, R1B_SHDR_FLAT, R1B_WIRE_FRONT);

    r1b_text(&im,L"WIREFRAME FRONT",10,10,&font,1,R1B_BLIT_SET,0);

    r1b_blit(&hstack,&im,R1B_PATTERN(SOLID),0,0,500,384,0,0,R1B_BRDR_WRAP,R1B_BLIT_SET);

    {
      r1b_normalize(&depth,0.0,5);
      r1b_dither(&depth,R1B_DTHR_FS);
      r1b_snapshot("examples/out/depth.png",&depth);
    }
    
    r1b_free(&im);
    r1b_free(&depth);
  } {
    r1b_im_t im = r1b_zeros(500,384);
    r1b_im_t depth = r1b_infs(500,384);
    r1b_render_mesh(&im, &depth, &mesh, 1000, NULL, NULL, 1, R1B_SHDR_NONE, R1B_WIRE_ALL);

    r1b_text(&im,L"WIREFRAME ALL",10,10,&font,1,R1B_BLIT_SET,1);

    r1b_blit(&hstack,&im,R1B_PATTERN(SOLID),500,0,1000,384,0,0,R1B_BRDR_WRAP,R1B_BLIT_SET);

    r1b_free(&im);
    r1b_free(&depth);
  }  {
    r1b_im_t im = r1b_zeros(500,384);
    r1b_im_t depth = r1b_infs(500,384);
    r1b_render_mesh(&im, &depth, &mesh, 1000, R1B_PATTERN(GRAY2), NULL, 1, R1B_SHDR_FLAT, R1B_WIRE_FRONT);

    r1b_text(&im,L"WIREFRAME SHADED",10,10,&font,1,R1B_BLIT_SET,1);

    r1b_blit(&hstack,&im,R1B_PATTERN(SOLID),1000,0,1500,384,0,0,R1B_BRDR_WRAP,R1B_BLIT_SET);

    r1b_free(&im);
    r1b_free(&depth);
  } {
    r1b_im_t im = r1b_zeros(500,384);
    r1b_im_t depth = r1b_infs(500,384);
    r1b_render_mesh(&im, &depth, &mesh, 1000, R1B_PATTERN(SOLID), NULL, 0, R1B_SHDR_FLAT, R1B_WIRE_FRONT);

    r1b_text(&im,L"WIREFRAME INVERTED",10,10,&font,1,R1B_BLIT_SET,1);

    r1b_blit(&hstack,&im,R1B_PATTERN(SOLID),1500,0,2000,384,0,0,R1B_BRDR_WRAP,R1B_BLIT_SET);

    r1b_free(&im);
    r1b_free(&depth);
  } {
    r1b_im_t im = r1b_zeros(500,384);
    r1b_im_t depth = r1b_infs(500,384);
    
    float light[4] = {0.3,0,0.3,0.1};
    r1b_render_mesh(&im, &depth, &mesh, 1000, NULL, light, 1, R1B_SHDR_NDOTLF, R1B_WIRE_NONE);
    r1b_dither(&im,R1B_DTHR_FS);

    r1b_text(&im,L"LAMBERT DITHERED",10,10,&font,1,R1B_BLIT_SET,1);

    r1b_blit(&hstack,&im,R1B_PATTERN(SOLID),2000,0,2500,384,0,0,R1B_BRDR_WRAP,R1B_BLIT_SET);

    r1b_free(&im);
    r1b_free(&depth);
  }  {
    r1b_im_t im = r1b_zeros(500,384);
    r1b_im_t depth = r1b_infs(500,384);
    
    float light[4] = {0.38,0,0.38,0.1};
    r1b_render_mesh(&im, &depth, &mesh, 1000, NULL, light, 1, R1B_SHDR_NDOTL, R1B_WIRE_FRONT);

    r1b_text(&im,L"LAMBERT QUANTIZED",10,10,&font,1,R1B_BLIT_SET,1);

    r1b_blit(&hstack,&im,R1B_PATTERN(SOLID),2500,0,3000,384,0,0,R1B_BRDR_WRAP,R1B_BLIT_SET);

    r1b_free(&im);
    r1b_free(&depth);
  }

  r1b_snapshot("examples/out/teapots.png",&hstack);

  r1b_transpose_flip(&hstack);

  // r1b_lpr("Printer_USB_Thermal_Printer",&hstack);

  r1b_destroy_mesh(&mesh);
  r1b_cleanup();
}
