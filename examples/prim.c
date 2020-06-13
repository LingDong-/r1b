//gcc examples/prim.c
#include "../r1b.h"


int main(){

  r1b_im_t im = r1b_zeros(1536,384);
  r1b_im_t depth = r1b_infs(1536,384);
  
  r1b_mesh_t cube    = r1b_cube(1,1,1);
  r1b_mesh_t sphere  = r1b_sphere(0.6,20,20);
  r1b_mesh_t cylinder= r1b_cylinder(0.5,0.5,1,20);
  r1b_mesh_t cone    = r1b_cone(0.5,0.5,1,20);

  r1b_scale_rotate_translate(&cube,     1,1,1,  -0.3,0,0, -2.4,0,4.5);
  r1b_scale_rotate_translate(&sphere,   1,1,1,  -0.3,0,0, -0.8,0,4.5);
  r1b_scale_rotate_translate(&cylinder, 1,1,1,  -0.3,0,0,  0.8,0,4.5);
  r1b_scale_rotate_translate(&cone,     1,1,1,  -0.3,0,0,  2.4,0,4.5);

  float light[4] = {0.4,0.3,0.2,0.0};
  float focal = 1000;
  r1b_render_mesh(&im, &depth, &cube,     focal, NULL, light, 1, R1B_SHDR_NDOTLF, R1B_WIRE_FRONT);
  r1b_render_mesh(&im, &depth, &sphere,   focal, NULL, light, 1, R1B_SHDR_NDOTLF, R1B_WIRE_FRONT);
  r1b_render_mesh(&im, &depth, &cylinder, focal, NULL, light, 1, R1B_SHDR_NDOTLF, R1B_WIRE_FRONT);
  r1b_render_mesh(&im, &depth, &cone,     focal, NULL, light, 1, R1B_SHDR_NDOTLF, R1B_WIRE_FRONT);

  r1b_dither(&im,R1B_DTHR_FS);

  r1b_text(&im, L"Cube",    30,      10, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 0);
  r1b_text(&im, L"Sphere",  30+384,  10, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 0);
  r1b_text(&im, L"Cylinder",30+384*2,10, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 0);
  r1b_text(&im, L"Cone",    30+384*3,10, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 0);

  r1b_snapshot("examples/out/prim.png",&im);

  r1b_transpose_flip(&im);
  // r1b_lpr("Printer_USB_Thermal_Printer",&im);

  r1b_free(&im);
  r1b_free(&depth);
  r1b_destroy_mesh(&cube);
  r1b_destroy_mesh(&sphere);
  r1b_destroy_mesh(&cylinder);
  r1b_destroy_mesh(&cone);

  r1b_cleanup();
}