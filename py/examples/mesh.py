import os
import sys; sys.path.append("../")
from math import sin,cos

import r1b

font = r1b.load_font_hex("../../fonts/unifont.hex",16,0,65535,r1b.FLAG_SORTED);

hstack = r1b.zeros(3000,384);

mesh = r1b.load_obj("../../examples/assets/teapot.obj");
r1b.normalize_mesh(mesh);

rotx = -0.2;
movz = 4.2

r1b.transform_mesh(mesh, [
		1,        0,         0,   0,
		0,cos(rotx),-sin(rotx),   0,
		0,sin(rotx), cos(rotx),movz,
		0,        0,         0,   1,
]);

r1b.compute_vertex_normals(mesh);


im = r1b.zeros(500,384);
depth = r1b.infs(500,384);
r1b.render_mesh(im, depth, mesh, 1000, r1b.PTTN_EMPTY, None, 1, r1b.SHDR_FLAT, r1b.WIRE_FRONT);

r1b.text_ascii(im,"WIREFRAME FRONT",10,10,font,1,r1b.BLIT_SET,0);

r1b.blit(hstack,im,r1b.PTTN_SOLID,0,0,500,384,0,0,r1b.BRDR_WRAP,r1b.BLIT_SET);

r1b.normalize(depth,0.0,5);
r1b.dither(depth,r1b.DTHR_FS);
r1b.snapshot("out/depth.png",depth);

r1b.free(im);
r1b.free(depth);


im = r1b.zeros(500,384);
depth = r1b.infs(500,384);
r1b.render_mesh(im, depth, mesh, 1000, None, None, 1, r1b.SHDR_NONE, r1b.WIRE_ALL);

r1b.text_ascii(im,"WIREFRAME ALL",10,10,font,1,r1b.BLIT_SET,1);

r1b.blit(hstack,im,r1b.PTTN_SOLID,500,0,1000,384,0,0,r1b.BRDR_WRAP,r1b.BLIT_SET);

r1b.free(im);
r1b.free(depth);


im = r1b.zeros(500,384);
depth = r1b.infs(500,384);
r1b.render_mesh(im, depth, mesh, 1000, r1b.PTTN_GRAY2, None, 1, r1b.SHDR_FLAT, r1b.WIRE_FRONT);

r1b.text_ascii(im,"WIREFRAME SHADED",10,10,font,1,r1b.BLIT_SET,1);

r1b.blit(hstack,im,r1b.PTTN_SOLID,1000,0,1500,384,0,0,r1b.BRDR_WRAP,r1b.BLIT_SET);

r1b.free(im);
r1b.free(depth);

im = r1b.zeros(500,384);
depth = r1b.infs(500,384);
r1b.render_mesh(im, depth, mesh, 1000, r1b.PTTN_SOLID, None, 0, r1b.SHDR_FLAT, r1b.WIRE_FRONT);

r1b.text_ascii(im,"WIREFRAME INVERTED",10,10,font,1,r1b.BLIT_SET,1);

r1b.blit(hstack,im,r1b.PTTN_SOLID,1500,0,2000,384,0,0,r1b.BRDR_WRAP,r1b.BLIT_SET);

r1b.free(im);
r1b.free(depth);

im = r1b.zeros(500,384);
depth = r1b.infs(500,384);

light = [0.3,0,0.3,0.1];
r1b.render_mesh(im, depth, mesh, 1000, None, light, 1, r1b.SHDR_NDOTLF, r1b.WIRE_NONE);
r1b.dither(im,r1b.DTHR_FS);

r1b.text_ascii(im,"LAMBERT DITHERED",10,10,font,1,r1b.BLIT_SET,1);

r1b.blit(hstack,im,r1b.PTTN_SOLID,2000,0,2500,384,0,0,r1b.BRDR_WRAP,r1b.BLIT_SET);

r1b.free(im);
r1b.free(depth);

im = r1b.zeros(500,384);
depth = r1b.infs(500,384);

light = [0.38,0,0.38,0.1];
r1b.render_mesh(im, depth, mesh, 1000, None, light, 1, r1b.SHDR_NDOTL, r1b.WIRE_FRONT);

r1b.text_ascii(im,"LAMBERT QUANTIZED",10,10,font,1,r1b.BLIT_SET,1);

r1b.blit(hstack,im,r1b.PTTN_SOLID,2500,0,3000,384,0,0,r1b.BRDR_WRAP,r1b.BLIT_SET);

r1b.free(im);
r1b.free(depth);

r1b.snapshot("out/teapots.png",hstack);

r1b.transpose_flip(hstack);

r1b.lpr("Printer_USB_Thermal_Printer",hstack);

r1b.destroy_font(font)
r1b.destroy_mesh(mesh);
r1b.cleanup();
