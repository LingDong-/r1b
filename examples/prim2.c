//gcc examples/prim2.c
#include "../r1b.h"


float randf(float lo, float hi){
  return lo+((float)rand()/(float)RAND_MAX)*(hi-lo);
}


int main(){

  r1b_im_t im = r1b_zeros(1536,384);
  r1b_im_t depth = r1b_infs(1536,384);
  
  float light[4] = {0.4,0.3,0.2,0.0};
  float focal = 1000;

  for (int i = 0; i < 100; i++){
    int rng = rand()%4;
    r1b_mesh_t mesh;
    switch(rng){
      case 0: mesh = r1b_cube(0.5,0.5,0.5); break;
      case 1: mesh = r1b_sphere(0.6,20,20); break;
      case 2: mesh = r1b_cylinder(0.5,0.5,1,20); break;
      case 3: mesh = r1b_cone(0.5,0.5,1,20); break;
    }
    float scl = randf(0.5,1.5);
    r1b_scale_rotate_translate(&mesh, 
      scl,scl,scl, 
      randf(-1,1)*M_PI,randf(-1,1)*M_PI,randf(-1,1)*M_PI, 
      randf(-4,4),randf(-2,2),randf(5,20)
    );

    r1b_render_mesh(&im, &depth, &mesh, focal, NULL, light, 1, R1B_SHDR_NDOTLF, R1B_WIRE_FRONT);
    r1b_destroy_mesh(&mesh);
  }
  r1b_dither(&im,R1B_DTHR_FS);

  r1b_snapshot("examples/out/prim2.png",&im);

  r1b_transpose_flip(&im);
  r1b_lpr("Printer_USB_Thermal_Printer",&im);

  r1b_free(&im);
  r1b_free(&depth);
  
  r1b_cleanup();
}