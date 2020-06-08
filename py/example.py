from r1b import *

im = r1b_zeros(400,400)
# im = r1b_read("../examples/assets/peppers.png")
# r1b_dither_fs(im);
# r1b_snapshot("out.png",im)
X = floatArray(3); X[0] = 100; X[1] = 200; X[2] = 100;
Y = floatArray(3); Y[0] = 100; Y[1] = 200; Y[2] = 300;
r1b_lines(im,X,Y,3,1,1,44)

r1b_snapshot("out.png",im)