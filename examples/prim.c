//gcc examples/plants.c
#include "../r1b.h"

int main(){

  for (int i = 0; i < 10; i++){

    r1b_im_t im = r1b_zeros(384, 384);
    r1b_im_t depth = r1b_infs(384,384);
    
    // r1b_mesh_t cube = r1b_cube(1,1,1);
    // r1b_mesh_t cube = r1b_sphere(0.5,20,20);
    // r1b_mesh_t cube = r1b_cylinder(0.5,0.5,1,20);
    r1b_mesh_t cube = r1b_cone(0.5,0.5,1,20);

    float rotx[] = R1B_MAT_ROTX(0.3);
    float roty[] = R1B_MAT_ROTY((float)i/10.0);
    float rotz[] = R1B_MAT_ROTZ(0);
    
    float rotxy[]= R1B_MAT_MULT(roty,rotx);
    float rot[]  = R1B_MAT_MULT(rotz,rotxy);
    float trl[]  = R1B_MAT_TRSL(0,0,4);
    float tfm[]  = R1B_MAT_MULT(trl,rot);

    r1b_transform_mesh(&cube, tfm);
    // r1b_compute_vertex_normals(&cube);

    float light[4] = {0.4,0.3,0.2,0.0};
    r1b_render_mesh(&im, &depth, &cube, 1000, NULL, light, 1, R1B_SHDR_NDOTLF, R1B_WIRE_FRONT);

    r1b_dither(&im,R1B_DTHR_FS);
    // r1b_normalize(&im,0.1,0.9);

    char filename[32];
    sprintf(filename,"examples/out/prim%d.png",i);
    r1b_snapshot(filename,&im);
    r1b_free(&im);
    r1b_free(&depth);
  }

  r1b_cleanup();
}