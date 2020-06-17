# r1b API documentation
### `void r1b_cleanup()`
```
free all resources allocated internally by the library 
```
|parameter|description|
|---|---|
|`w`|```width ```|
|`h`|```height ```|




-----------------


### `r1b_im_t r1b_read(const char *path)`
```
read an image from disk as grayscale 
```
|parameter|description|
|---|---|
|`path`|```the file path ```|


**return** `an image `



-----------------


### `void r1b_snapshot(const char *path, r1b_im_t *im)`
```
write image to file, supported: jpg, png, bmp 
```
|parameter|description|
|---|---|
|`path`|```the file path ```|
|`im`|```an image ```|




-----------------


### `r1b_im_t r1b_zeros(int w, int h)`
```
create image filled with zeros 
```
|parameter|description|
|---|---|
|`w`|```width ```|
|`h`|```height ```|


**return** `an image `



-----------------


### `r1b_im_t r1b_ones(int w, int h)`
```
create image filled with ones 
```
|parameter|description|
|---|---|
|`w`|```width ```|
|`h`|```height ```|


**return** `an image `



-----------------


### `r1b_im_t r1b_from_array(int w, int h, float *arr)`
```
create image from data pointed by array pointer, copying the data over 
```
|parameter|description|
|---|---|
|`w`|```width ```|
|`h`|```height ```|
|`arr`|```an array that is at least w x h in size ```|


**return** `an image `



-----------------


### `r1b_im_t r1b_infs(int w, int h)`
```
create image filled with FLT_MAX 
```
|parameter|description|
|---|---|
|`w`|```width ```|
|`h`|```height ```|


**return** `an image `



-----------------


### `void r1b_free(r1b_im_t *im)`
```
free data allocated in an image; does not free the pointer itself 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|




-----------------


### `void r1b_transpose(r1b_im_t *im)`
```
transpose an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|




-----------------


### `void r1b_transpose_flip(r1b_im_t *im)`
```
transpose and flip an image, effectively rotating it by 90 degrees. 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|




-----------------


### `void r1b_normalize(r1b_im_t *im, float lo, float hi)`
```
normalize an image to a given interval 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`lo`|```new min value ```|
|`hi`|```new max value ```|




-----------------


### `r1b_im_t r1b_copy_of(r1b_im_t *im)`
```
duplicates an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|


**return** `the clone `



-----------------


### `void r1b_copy_to(r1b_im_t *im, r1b_im_t *dst)`
```
copy data from one image to another the images should have the same width, and destination is at least the same height as source 
```
|parameter|description|
|---|---|
|`im`|```source: pointer to image to be copied from ```|
|`dst`|```destination: pointer to image to be copied into ```|




-----------------


### `void r1b_dither(r1b_im_t *im, int mode)`
```
apply dithering to a grayscale image turning it into binary image using specified algorithm 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`mode`|```the algorithm to use, either R1B_DTHR_ORD or R1B_DTHR_FS ```|




-----------------


### `void r1b_log(r1b_im_t *im)`
```
print an image to stdout for debugging 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|




-----------------


### `char* r1b_encode(r1b_im_t *im, int *n_bytes_written)`
```
encode an image to ESC/POS commands 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`n_bytes_written`|```size of the returned buffer in bytes ```|


**return** `an array of bytes `



-----------------


### `void r1b_encode2file(const char *path, r1b_im_t *im)`
```
encode an image to ESC/POS commands and write it to a file 
```
|parameter|description|
|---|---|
|`path`|```file path to write to ```|
|`im`|```pointer to image ```|




-----------------


### `void r1b_lpr(const char *printer, r1b_im_t *im)`
```
send an image to a thermal printer for printing using LPR command 
```
|parameter|description|
|---|---|
|`printer`|```the name of the printer ```|
|`im`|```pointer to image ```|




-----------------


### `void r1b_resample(r1b_im_t *im, int w, int h, int mode)`
```
resample image to a different size 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`w`|```new width, pass R1B_INFER to scale proportionally per new height ```|
|`h`|```new height, pass R1B_INFER to scale proportionally per new width ```|
|`mode`|```the alogirthm, either R1B_SMPL_NN or R1B_SMPL_BILINEAR ```|




-----------------


### `float r1b_get(r1b_im_t *im, int x, int y, int mode)`
```
retrieve the value of a pixel at given coordinate 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`x`|```x coordinate ```|
|`y`|```y coordinate ```|
|`mode`|```border handling when coordinate is outside image: R1B_BRDR_ZERO: zero padded; R1B_BRDR_COPY: copy padded; R1B_BRDR_WRAP: wrap around; R1B_BRDR_NONE: no boundry checking (expect funny result or segfault when out of range). ```|




-----------------


### `void r1b_set(r1b_im_t *im, int x, int y, float val, int mode)`
```
set the value of a pixel at given coordinate 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`x`|```x coordinate ```|
|`y`|```y coordinate ```|
|`val`|```the value of the pixel ```|
|`mode`|```blit mode, one of: R1B_BLIT_SET: overwrite the pixel; R1B_BLIT_FLIP: flip the value of the pixel; R1B_BLIT_OR: turn on the pixel if it's off; R1B_BLIT_ADD: add the value to the original. ```|




-----------------


### `void r1b_upsample2x(r1b_im_t *im, int mode)`
```
upsample image by 2x using pixel-art scaling algorithms 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`mode`|```algorithm: one of R1B_UP2X_SAA5050, R1B_UP2X_EPX, R1B_UP2X_EAGLE, R1B_UP2X_HQX ```|




-----------------


### `void r1b_bedstead(r1b_im_t *im, int n)`
```
upsample image by a power of two using bedstead algorithm 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`n`|```upscale by n-th power of two, e.g. n=3 => upscale by 8x ```|




-----------------


### `void r1b_triangle(r1b_im_t *im, float x0, float y0, float x1, float y1, float x2, float y2, r1b_im_t *pttn, int mode)`
```
draw a 2D triangle 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`x0`|```x coordinate of first vertex ```|
|`y0`|```y coordinate of first vertex ```|
|`x1`|```x coordinate of second vertex ```|
|`y1`|```y coordinate of second vertex ```|
|`x2`|```x coordinate of third vertex ```|
|`y2`|```y coordinate of third vertex ```|
|`pttn`|```fill pattern ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_rect(r1b_im_t *im, float x0, float y0, float x1, float y1, r1b_im_t *pttn, int mode)`
```
draw a 2D rectangle 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`x0`|```left ```|
|`y0`|```top ```|
|`x1`|```right ```|
|`y1`|```bottom ```|
|`pttn`|```fill pattern ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_line(r1b_im_t *im, float x0, float y0, float x1, float y1, float val, int mode)`
```
draw a 2D line 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`x0`|```x coordinate of first point ```|
|`y0`|```y coordinate of first point ```|
|`x1`|```x coordinate of second point ```|
|`y1`|```y coordinate of second point ```|
|`val`|```value (color) of the line ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_lines(r1b_im_t *im, float *Xs, float *Ys, int n, int close, float val, int mode)`
```
draw a polyline or outline a polygon 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`Xs`|```pointer to array of x-coordinates ```|
|`Ys`|```pointer to array of y-coordinates ```|
|`n`|```number of points ```|
|`close`|```true for closed (polygon) or false for open (polyline) ```|
|`val`|```value (color) of the lines ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_thick_line(r1b_im_t *im, float x0, float y0, float x1, float y1, float val, int half_thick, int mode)`
```
draw a 2D line with thickness 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`x0`|```x coordinate of first point ```|
|`y0`|```y coordinate of first point ```|
|`x1`|```x coordinate of second point ```|
|`y1`|```y coordinate of second point ```|
|`val`|```value (color) of the line ```|
|`half_thick`|```set thickness of line to half_thick*2+1 ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `r1b_font_t r1b_load_font_hex(const char *path, int h, int cp0, int cp1, int flags)`
```
load a bitmap font in unifont .hex format 
```
|parameter|description|
|---|---|
|`path`|```file path ```|
|`h`|```height of the font, since the hex format does not store this information ```|
|`cp0`|```unicode code point range start, only glyphs between cp0 and cp1 will be loaded (if any exist) when you don't need the whole set ```|
|`cp1`|```unicode code point range end ```|
|`flags`|```a bitwise OR of flags: R1B_FLAG_SORTED: set this if the glyphs stored in the file are sorted by unicode code point, which improves speed ```|


**return** `a font type `



-----------------


### `void r1b_destroy_font(r1b_font_t *font)`
```
free data allocated in a font 
```
|parameter|description|
|---|---|
|`font`|```pointer to font ```|




-----------------


### `int r1b_putchar(r1b_im_t *im, int cp, int x, int y, r1b_font_t *font, float val, int mode, int highlight)`
```
draw a single unicode character to image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`cp`|```codepoint ```|
|`x`|```x coordinate ```|
|`y`|```y coordinate ```|
|`font`|```pointer to font ```|
|`val`|```value (color) of the text ```|
|`mode`|```blit mode, see r1b_set ```|
|`highlight`|```boolean: whether to draw a highlight behind the text (to stand out from busy background) ```|




-----------------


### `void r1b_text(r1b_im_t *im, wchar_t *str, int x, int y, r1b_font_t *font, float val, int mode, int highlight)`
```
draw a string (of wide chars) to image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`str`|```text stored as wchar_t* ```|
|`x`|```x coordinate ```|
|`y`|```y coordinate ```|
|`font`|```pointer to font ```|
|`val`|```value (color) of the text ```|
|`mode`|```blit mode, see r1b_set ```|
|`highlight`|```boolean: whether to draw a highlight behind the text (to stand out from busy background) ```|




-----------------


### `void r1b_text_utf8(r1b_im_t *im, char *str, int x, int y, r1b_font_t *font, float val, int mode, int highlight)`
```
draw a utf-8 encoded string to image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`str`|```utf-8 encoded string ```|
|`x`|```x coordinate ```|
|`y`|```y coordinate ```|
|`font`|```pointer to font ```|
|`val`|```value (color) of the text ```|
|`mode`|```blit mode, see r1b_set ```|
|`highlight`|```boolean: whether to draw a highlight behind the text (to stand out from busy background) ```|




-----------------


### `void r1b_text_ascii(r1b_im_t *im, char *str, int x, int y, r1b_font_t *font, float val, int mode, int highlight)`
```
draw an ascii-only string to image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`str`|```the string ```|
|`x`|```x coordinate ```|
|`y`|```y coordinate ```|
|`font`|```pointer to font ```|
|`val`|```value (color) of the text ```|
|`mode`|```blit mode, see r1b_set ```|
|`highlight`|```boolean: whether to draw a highlight behind the text (to stand out from busy background) ```|




-----------------


### `void r1b_polygon(r1b_im_t *im, float *Xs, float *Ys, int n, r1b_im_t *pttn, int mode, int typ)`
```
draw a polygon on image 
```
|parameter|description|
|---|---|
|`im`|```pointer to iamge ```|
|`Xs`|```x-coordinates of vertices ```|
|`Ys`|```y-coordinates of vertices ```|
|`n`|```number of vertices ```|
|`pttn`|```fill pattern ```|
|`mode`|```blit mode, see r1b_set for details ```|
|`typ`|```type of polygon, either R1B_POLY_CONVEX or R1B_POLY_CONCAVE. concave mode works for convex polygons too, but asserting it as convex can speed things up ```|




-----------------


### `void r1b_ellipse(r1b_im_t *im, float cx, float cy, float rx, float ry, float ang, r1b_im_t *pttn, int mode)`
```
draw an ellipse on image 
```
|parameter|description|
|---|---|
|`im`|```pointer to iamge ```|
|`cx`|```x-coordinates of the center ```|
|`cy`|```y-coordinates of the center ```|
|`rx`|```radius in x-direction ```|
|`ry`|```radius in y-direction ```|
|`ang`|```rotation of the ellipse (in radians) ```|
|`pttn`|```fill pattern ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_line_ellipse(r1b_im_t *im, float cx, float cy, float rx, float ry, float ang, int detail, float val, int mode)`
```
draw outline of an ellipse on image 
```
|parameter|description|
|---|---|
|`im`|```pointer to iamge ```|
|`cx`|```x-coordinates of the center ```|
|`cy`|```y-coordinates of the center ```|
|`rx`|```radius in x-direction ```|
|`ry`|```radius in y-direction ```|
|`ang`|```rotation of the ellipse (in radians) ```|
|`detail`|```number of segments used to approximate the ellipse, the higher the smoother ```|
|`val`|```value (color) of the outline ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_blit(r1b_im_t *dst, r1b_im_t *src, r1b_im_t *msk, float x0, float y0, float x1, float y1, float sx, float sy, int bdmode, int mode)`
```
blit an image onto another, optionally applying a mask. supports drawing a subsection and repeated patterns 
```
|parameter|description|
|---|---|
|`dst`|```pointer to destination image ```|
|`src`|```pointer to source image ```|
|`msk`|```pointer to mask image. for no masking, use an image of all 1's (e.g. R1B_GET_PATTERN(SOLID) and R1B_BRDR_WRAP for bdmode) ```|
|`x0`|```x coordinate on the destination image for upper left corner of source image ```|
|`y0`|```y coordinate on the destination image for upper left corner of source image ```|
|`x1`|```x coordinate on the destination image for lower right corner of source image ```|
|`y1`|```y coordinate on the destination image for lower right corner of source image ```|
|`sx`|```x coordinate on the source image to offset ```|
|`sy`|```y coordinate on the source image to offset ```|
|`bdmode`|```border mode, see r1b_get for details ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_paste(r1b_im_t *dst, r1b_im_t *src, float x, float y)`
```
blit an image onto another, a simplified version of r1b_blit with less arguments 
```
|parameter|description|
|---|---|
|`dst`|```pointer to destination image ```|
|`src`|```pointer to source image ```|
|`x`|```x coordinate on the destination image for upper left corner of source image ```|
|`y`|```y coordinate on the destination image for upper left corner of source image ```|




-----------------


### `r1b_mesh_t r1b_load_obj(const char *path)`
```
load an wavefront .obj file to a new mesh 
currently doesn't support mtl or normals 
```
|parameter|description|
|---|---|
|`path`|```file path ```|


**return** `a mesh type `



-----------------


### `void r1b_mesh_bbox(r1b_mesh_t *mesh, float *xmin, float *ymin, float *zmin, float *xmax, float *ymax, float *zmax)`
```
calculate the bounding box of a mesh 
```
|parameter|description|
|---|---|
|`mesh`|```pointer to mesh ```|
|`xmin`|```pointer to minimum x to be overwritten ```|
|`ymin`|```pointer to minimum y to be overwritten ```|
|`zmin`|```pointer to minimum z to be overwritten ```|
|`xmax`|```pointer to maximum x to be overwritten ```|
|`ymax`|```pointer to maximum y to be overwritten ```|
|`zmax`|```pointer to maximum z to be overwritten ```|




-----------------


### `void r1b_normalize_mesh(r1b_mesh_t *mesh)`
```
normalize vertices of a mesh to be bounded by (-1,-1,-1) and (1,1,1), keeping proportions 
```
|parameter|description|
|---|---|
|`mesh`|```pointer to mesh ```|




-----------------


### `void r1b_destroy_mesh(r1b_mesh_t *mesh)`
```
free memory allocated in a mesh 
```
|parameter|description|
|---|---|
|`mesh`|```pointer to mesh ```|




-----------------


### `void r1b_triangle3d(r1b_im_t *im, r1b_im_t *depth, float f, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, r1b_im_t *pttn, float *vals, int mode)`
```
draw a 3D triangle to image, projected with pinhole camera model 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`depth`|```pointer to the depth buffer, which will be read and written. use ```|
|`f`|```focal length of the camera ```|
|`x0`|```x coordinate of the first vertex ```|
|`y0`|```y coordinate of the first vertex ```|
|`z0`|```z coordinate of the first vertex ```|
|`x1`|```x coordinate of the second vertex ```|
|`y1`|```y coordinate of the second vertex ```|
|`z1`|```z coordinate of the second vertex ```|
|`x2`|```x coordinate of the third vertex ```|
|`y2`|```y coordinate of the third vertex ```|
|`z2`|```z coordinate of the third vertex ```|
|`pttn`|```fill pattern, when NULL, ```|
|`vals`|```3-array for value (color) of each vertex (points in triangle will have interpolated colors), used when ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_line3d(r1b_im_t *im, r1b_im_t *depth, int depth_read, float f, float x0, float y0, float z0, float x1, float y1, float z1, float val, int mode)`
```
draw a 3D line to image, projected with pinhole camera model 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`depth`|```pointer to the depth buffer. use ```|
|`depth_read`|```boolean: whether or not to read the depth buffer. use 0 to draw on top of everything ```|
|`f`|```focal length of the camera ```|
|`x0`|```x coordinate of the first endpoint ```|
|`y0`|```y coordinate of the first endpoint ```|
|`z0`|```z coordinate of the first endpoint ```|
|`x1`|```x coordinate of the second endpoint ```|
|`y1`|```y coordinate of the second endpoint ```|
|`z1`|```z coordinate of the second endpoint ```|
|`val`|```value (color) of the line ```|
|`mode`|```blit mode, see r1b_set for details ```|




-----------------


### `void r1b_transform_mesh(r1b_mesh_t *mesh, float *mat)`
```
transform mesh with a 4x4 transformation matrix 
```
|parameter|description|
|---|---|
|`mesh`|```pointer to mesh ```|
|`mat`|```the 4x4 row major transformation matrix as an array of 16 floats ```|




-----------------


### `void r1b_scale_rotate_translate(r1b_mesh_t *mesh, float sx, float sy, float sz, float rx, float ry, float rz, float x, float y, float z)`
```
scale mesh, apply rotation by euler angles (x-y-z order) and translate mesh 
a simplified interface to r1b_transform_mesh that covers many use cases. 
```
|parameter|description|
|---|---|
|`mesh`|```pointer to mesh ```|
|`sx`|```scale along x-axis ```|
|`sy`|```scale along y-axis ```|
|`sz`|```scale along z-axis ```|
|`rx`|```rotation around x-axis ```|
|`ry`|```rotation around y-axis ```|
|`rz`|```rotation around z-axis ```|
|`x`|```translation along x-axis ```|
|`y`|```translation along y-axis ```|
|`z`|```translation along z-axis ```|




-----------------


### `r1b_mesh_t r1b_copy_of_mesh(r1b_mesh_t *mesh)`
```
make a deep clone of given mesh 
```
|parameter|description|
|---|---|
|`mesh`|```pointer to mesh ```|


**return** `the clone `



-----------------


### `void r1b_compute_vertex_normals(r1b_mesh_t *mesh)`
```
estimate vertex normals for a mesh and store result in mesh->norms 
```
|parameter|description|
|---|---|
|`mesh`|```pointer to mesh ```|




-----------------


### `void r1b_render_mesh(r1b_im_t *im, r1b_im_t *depth, r1b_mesh_t *mesh, float f, r1b_im_t *pttn, float *light, int wire_val, int shdr, int wire)`
```
draw a 3d mesh to the image, projected with pinhole camera model 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`depth`|```pointer to the depth buffer, which will be read and written. use ```|
|`mesh`|```pointer to mesh ```|
|`f`|```focal length of the camera ```|
|`pttn`|```fill pattern, can be NULL depending on the shader specified ```|
|`light`|```4-array: the first 3 are direction of the light, 4th is global illumination. can be NULL depending on shader specified ```|
|`wire_val`|```value (color) of the wireframe. might be unused depending on the shader specified ```|
|`shdr`|```shader type to use, one of: R1B_SHDR_NONE: no shading will be done, if wireframe is also off, you will not be able to see anything; R1B_SHDR_FLAT: flat shading, use pattern fill to evenly fill all faces; R1B_SHDR_NDOTL: n-dot-l diffuse shading, quantized to 5 levels and filled with patterns of different shades; R1B_SHDR_NDOTLF: n-dot-l shading but without quantization, returning grayscale, on which dithering can be further applied ```|
|`wire`|```type of wireframe, one of: R1B_WIRE_FRONT: wireframe can be occluded; R1B_WIRE_ALL: all wireframes are drawn; R1B_WIRE_NONE: no wireframe is drawn. ```|




-----------------


### `r1b_mesh_t r1b_cube(float sx, float sy, float sz)`
```
make a 3d cube mesh 
cube will be centred at 0,0,0 
```
|parameter|description|
|---|---|
|`sx`|```x dimension ```|
|`sy`|```y dimension ```|
|`sz`|```z dimension ```|


**return** `a new cube mesh `



-----------------


### `r1b_mesh_t r1b_sphere(float rad, int slices, int stacks)`
```
make a 3d sphere mesh 
sphere will be centred at 0,0,0 
```
|parameter|description|
|---|---|
|`rad`|```radius ```|
|`slices`|```number of segments on x-z plane ```|
|`stacks`|```number of segments on y axis ```|


**return** `a new sphere mesh `



-----------------


### `r1b_mesh_t r1b_cylinder(float rx, float rz, float h, int slices)`
```
make a 3d cylinder mesh 
cylinder will be centred at 0,0,0 
```
|parameter|description|
|---|---|
|`rx`|```radius on x axis ```|
|`rz`|```radius on z axis ```|
|`h`|```height ```|
|`slices`|```number of segments ```|


**return** `a new cylinder mesh `



-----------------


### `r1b_mesh_t r1b_cone(float rx, float rz, float h, int slices)`
```
make a 3d cone mesh 
cone will be centred at 0,0,0 
```
|parameter|description|
|---|---|
|`rx`|```radius on x axis ```|
|`rz`|```radius on z axis ```|
|`h`|```height ```|
|`slices`|```number of segments ```|


**return** `a new cone mesh `



-----------------


### `r1b_im_t r1b_make_kernel(int ksize, int mode)`
```
generate a specified convolution matrix for image processing 
```
|parameter|description|
|---|---|
|`ksize`|```kernel size, will be automatically rounded up to an odd integer ```|
|`mode`|```morphological kernels: R1B_KERN_ELLIPSE, R1B_KERN_CROSS, R1B_KERN_RECT; convolutional kernels: R1B_KERN_GAUSS, R1B_KERN_GAUSS1D; ```|


**return** `kernal as image type `



-----------------


### `void r1b_conv2d(r1b_im_t *im, r1b_im_t *kern, int border)`
```
perform 2D convolution on an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`kern`|```pointer to kernel ```|
|`border`|```border mode, see r1b_get ```|




-----------------


### `void r1b_dilate(r1b_im_t *im, r1b_im_t *kern)`
```
perform morphological dilation on an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`kern`|```pointer to kernel ```|




-----------------


### `void r1b_erode(r1b_im_t *im, r1b_im_t *kern)`
```
perform morphological erosion on an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`kern`|```pointer to kernel ```|




-----------------


### `void r1b_sobel(r1b_im_t *im, float *out_gradient_directions)`
```
apply sobel edge detection to an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`out_gradient_directions`|```optional: if non NULL, will be overwritten with gradient directions. (the source image will be written with gradient strength). if only gradient directions are needed, pass im->data here ```|




-----------------


### `void r1b_blur(r1b_im_t *im, int rad, int mode)`
```
apply bluring to an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`rad`|```radius of blur, kernel size = rad*2+1 ```|
|`mode`|```one of: R1B_BLUR_BOX, R1B_BLUR_GAUSS ```|




-----------------


### `void r1b_canny(r1b_im_t *im, int blur_rad, float thresh_lo, float thresh_hi)`
```
apply canny edge detection to an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`blur_rad`|```radius for preprocessing blur, reduces noise ```|
|`thresh_lo`|```lower threshold for the double thresholding step (weak edges) ```|
|`thresh_hi`|```higher threshold for the double thresholding step (strong edges) ```|




-----------------


### `void r1b_threshold(r1b_im_t *im, float th)`
```
apply thresholding to an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`th`|```the threshold. pass R1B_INFER to use Otsu's method for automatically picking optimal threshold ```|




-----------------


### `void r1b_threshold_adaptive(r1b_im_t *im, int rad, float bias, int blur_mode)`
```
apply adaptive threshold to an image 
```
|parameter|description|
|---|---|
|`im`|```pointer to image ```|
|`rad`|```radius of neighborhood for each pixel ```|
|`bias`|```adjusts brightness: pixel is considered below the threshold if it is this factor lower than its neighborhood ```|
|`blur_mode`|```blurring kernel for averaging the neighborhood, e.g. R1B_BLUR_GAUSS, R1B_BLUR_BOX ```|




-----------------


