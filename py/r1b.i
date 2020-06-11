

%include "carrays.i"
%array_class(float, FloatArray);


%module r1b

%{

#define R1B_INFER         -42
#define R1B_DTHR_ORD       1
#define R1B_DTHR_FS        2
#define R1B_SMPL_NN        11
#define R1B_SMPL_BILINEAR  12
#define R1B_BRDR_COPY      21
#define R1B_BRDR_ZERO      22
#define R1B_BRDR_NONE      23
#define R1B_BRDR_WRAP      24
#define R1B_FONT_HEX       31
#define R1B_BLIT_OR        41
#define R1B_BLIT_ADD       42
#define R1B_BLIT_FLIP      43
#define R1B_BLIT_SET       44
#define R1B_POLY_CONVEX    51
#define R1B_POLY_CONCAVE   52
#define R1B_WIRE_NONE      61
#define R1B_WIRE_FRONT     62
#define R1B_WIRE_ALL       63
#define R1B_SHDR_NONE      70
#define R1B_SHDR_FLAT      71
#define R1B_SHDR_NDOTL     72
#define R1B_SHDR_NDOTLF    73
#define R1B_UP2X_SAA5050   81
#define R1B_UP2X_EPX       82
#define R1B_UP2X_EAGLE     83
#define R1B_UP2X_HQX       84
#define R1B_KERN_ELLIPSE   91
#define R1B_KERN_GAUSS     92
#define R1B_KERN_GAUSS1D   93
#define R1B_KERN_CROSS     94
#define R1B_KERN_RECT      95
#define R1B_BLUR_GAUSS     111
#define R1B_BLUR_BOX       112
#define R1B_FLAG_SORTED    1
typedef struct {  int w;  int h;  float* data;} r1b_im_t;
typedef struct {  int h;  char* glyphs;  int n;  uint32_t* offsets;  uint8_t*  sizes;  uint16_t* cmap;  int flags;} r1b_font_t;
typedef struct {  float* X;  float* Y;  float* Z;  int* tris;  float* norms;  int n_vtx;  int n_tri;} r1b_mesh_t;
r1b_font_t* r1b_get_font_fg8x12();;
void r1b_make_tmp0(int w, int h);
void r1b_make_tmp1(int w, int h);
void r1b_cleanup();
r1b_im_t r1b_read(const char* path);
void r1b_snapshot(const char* path, r1b_im_t* im);
r1b_im_t r1b_zeros(int w, int h);
r1b_im_t r1b_ones(int w, int h);
r1b_im_t r1b_from_array(int w, int h, float* arr);
r1b_im_t r1b_infs(int w, int h);
void r1b_free(r1b_im_t* im);
void r1b_transpose(r1b_im_t* im);
void r1b_transpose_flip(r1b_im_t* im);
void r1b_normalize(r1b_im_t* im, float lo, float hi);
r1b_im_t r1b_copy_of(r1b_im_t* im);
void r1b_copy_to(r1b_im_t* im, r1b_im_t* dst);
void r1b_dither_fs(r1b_im_t* im) ;
void r1b_dither_ord(r1b_im_t* im);
void r1b_dither(r1b_im_t* im, int mode);
void r1b_log(r1b_im_t* im);
char* r1b_encode(r1b_im_t* im, int* n_bytes_written);
void r1b_encode2file(const char* path, r1b_im_t* im);
void r1b_lpr(const char* printer, r1b_im_t* im);
void r1b_resample_nearest(r1b_im_t* im, int w, int h);
void r1b_resample_bilinear(r1b_im_t* im, int w, int h);
void r1b_resample(r1b_im_t* im, int w, int h, int mode);
float r1b_get(r1b_im_t* im, int x, int y, int mode);
void r1b_set(r1b_im_t* im, int x, int y, float val, int mode);
void r1b_upsample2x_saa5050(r1b_im_t* im);
void r1b_upsample2x_epx(r1b_im_t* im);
void r1b_upsample2x_eagle(r1b_im_t* im);
float r1b_hq2x_blend(unsigned rule, float E, float A, float B, float D, float F, float H) ;
void r1b_upsample2x_hqx(r1b_im_t* im);
void r1b_upsample2x(r1b_im_t* im, int mode);
void r1b_bedstead(r1b_im_t* im, int n);
void r1b_triangle(r1b_im_t* im,float x0 ,float y0 ,float x1 ,float y1 ,float x2 ,float y2 , r1b_im_t* pttn, int mode );
void r1b_rect(r1b_im_t* im,float x0 ,float y0 ,float x1 ,float y1 , r1b_im_t* pttn, int mode);
void r1b_line(r1b_im_t* im, float x0 ,float y0 ,float x1 ,float y1, float val, int mode);
void r1b_lines(r1b_im_t* im, float* Xs, float* Ys, int n, int close, float val, int mode);
void r1b_thick_line(r1b_im_t* im, float x0, float y0, float x1, float y1, float val, int thick, int mode);
r1b_font_t r1b_load_font_hex(const char* path, int h, int cp0, int cp1, int flags) ;
void r1b_destroy_font(r1b_font_t* font);
int r1b_glyph_index_lin_search(r1b_font_t* font, int cp);
int r1b_glyph_index_bin_search(r1b_font_t* font, int cp, int i0, int i1);
int r1b_glyph_index(r1b_font_t* font, int cp);
int r1b_putchar(r1b_im_t* im, int cp, int x, int y, r1b_font_t* font,float val, int mode, int highlight);
void r1b_text(r1b_im_t* im, wchar_t* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight);
void r1b_text_utf8(r1b_im_t* im, char* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight);
void r1b_text_ascii(r1b_im_t* im, char* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight);
float r1b_area(float* X, float* Y, int n) ;
int r1b_triangulate_snip(float* X, float* Y,int u,int v,int w,int n,int *V ) ;
int r1b_triangulate(float* X, float* Y, int n, int* triangles) ;
void r1b_polygon_convex(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode);
void r1b_polygon_concave(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode);
void r1b_polygon(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode, int typ);
void r1b_ellipse(r1b_im_t* im, float cx, float cy, float rx, float ry, float ang, r1b_im_t* pttn, int mode);
void r1b_line_ellipse(r1b_im_t* im, float cx, float cy, float rx, float ry, float ang, int detail, float val, int mode);
void r1b_blit(r1b_im_t* dst, r1b_im_t* src, r1b_im_t* msk, float x0, float y0, float x1, float y1, float sx, float sy, int bdmode, int mode);
void r1b_paste(r1b_im_t* dst, r1b_im_t* src, float x, float y);
r1b_mesh_t r1b_load_obj(const char* path);
void r1b_mesh_bbox(r1b_mesh_t* mesh, float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax);
void r1b_normalize_mesh(r1b_mesh_t* mesh);
void r1b_destroy_mesh(r1b_mesh_t* mesh);
void r1b_triangle3d(r1b_im_t* im, r1b_im_t* depth, float f, float x0, float y0, float z0, float x1 ,float y1, float z1, float x2 ,float y2, float z2, r1b_im_t* pttn, float* vals, int mode );
void r1b_line3d(r1b_im_t* im, r1b_im_t* depth, int depth_read, float f, float x0 ,float y0, float z0, float x1 ,float y1, float z1, float val, int mode);
void r1b_transform_mesh(r1b_mesh_t* mesh, float* mat);
void r1b_compute_vertex_normals(r1b_mesh_t* mesh);
void r1b_render_mesh(r1b_im_t* im, r1b_im_t* depth, r1b_mesh_t* mesh, float f, r1b_im_t* pttn, float* light, int wire_val, int shdr, int wire);
r1b_im_t r1b_make_kernel(int ksize, int mode);
void r1b_conv2d(r1b_im_t* im, r1b_im_t* kern, int border) ;
void r1b_dilate(r1b_im_t* im, r1b_im_t* kern);
void r1b_erode(r1b_im_t* im, r1b_im_t* kern);
void r1b_sobel(r1b_im_t* im, float* out_gradient_directions);
void r1b_blur(r1b_im_t* im, int rad, int mode);
void r1b_canny(r1b_im_t* im, int blur_rad, float thresh_lo, float thresh_hi);
void r1b_threshold(r1b_im_t* im, float th);
void r1b_threshold_adaptive(r1b_im_t* im, int rad, float bias, int blur_mode);

void* nullptr(){
 	return NULL;
}


%}

#define R1B_INFER         -42
#define R1B_DTHR_ORD       1
#define R1B_DTHR_FS        2
#define R1B_SMPL_NN        11
#define R1B_SMPL_BILINEAR  12
#define R1B_BRDR_COPY      21
#define R1B_BRDR_ZERO      22
#define R1B_BRDR_NONE      23
#define R1B_BRDR_WRAP      24
#define R1B_FONT_HEX       31
#define R1B_BLIT_OR        41
#define R1B_BLIT_ADD       42
#define R1B_BLIT_FLIP      43
#define R1B_BLIT_SET       44
#define R1B_POLY_CONVEX    51
#define R1B_POLY_CONCAVE   52
#define R1B_WIRE_NONE      61
#define R1B_WIRE_FRONT     62
#define R1B_WIRE_ALL       63
#define R1B_SHDR_NONE      70
#define R1B_SHDR_FLAT      71
#define R1B_SHDR_NDOTL     72
#define R1B_SHDR_NDOTLF    73
#define R1B_UP2X_SAA5050   81
#define R1B_UP2X_EPX       82
#define R1B_UP2X_EAGLE     83
#define R1B_UP2X_HQX       84
#define R1B_KERN_ELLIPSE   91
#define R1B_KERN_GAUSS     92
#define R1B_KERN_GAUSS1D   93
#define R1B_KERN_CROSS     94
#define R1B_KERN_RECT      95
#define R1B_BLUR_GAUSS     111
#define R1B_BLUR_BOX       112
#define R1B_FLAG_SORTED    1
typedef struct {  int w;  int h;  float* data;} r1b_im_t;
typedef struct {  int h;  char* glyphs;  int n;  uint32_t* offsets;  uint8_t*  sizes;  uint16_t* cmap;  int flags;} r1b_font_t;
typedef struct {  float* X;  float* Y;  float* Z;  int* tris;  float* norms;  int n_vtx;  int n_tri;} r1b_mesh_t;
r1b_font_t* r1b_get_font_fg8x12();;
void r1b_make_tmp0(int w, int h);
void r1b_make_tmp1(int w, int h);
void r1b_cleanup();
r1b_im_t r1b_read(const char* path);
void r1b_snapshot(const char* path, r1b_im_t* im);
r1b_im_t r1b_zeros(int w, int h);
r1b_im_t r1b_ones(int w, int h);
r1b_im_t r1b_from_array(int w, int h, float* arr);
r1b_im_t r1b_infs(int w, int h);
void r1b_free(r1b_im_t* im);
void r1b_transpose(r1b_im_t* im);
void r1b_transpose_flip(r1b_im_t* im);
void r1b_normalize(r1b_im_t* im, float lo, float hi);
r1b_im_t r1b_copy_of(r1b_im_t* im);
void r1b_copy_to(r1b_im_t* im, r1b_im_t* dst);
void r1b_dither_fs(r1b_im_t* im) ;
void r1b_dither_ord(r1b_im_t* im);
void r1b_dither(r1b_im_t* im, int mode);
void r1b_log(r1b_im_t* im);
char* r1b_encode(r1b_im_t* im, int* n_bytes_written);
void r1b_encode2file(const char* path, r1b_im_t* im);
void r1b_lpr(const char* printer, r1b_im_t* im);
void r1b_resample_nearest(r1b_im_t* im, int w, int h);
void r1b_resample_bilinear(r1b_im_t* im, int w, int h);
void r1b_resample(r1b_im_t* im, int w, int h, int mode);
float r1b_get(r1b_im_t* im, int x, int y, int mode);
void r1b_set(r1b_im_t* im, int x, int y, float val, int mode);
void r1b_upsample2x_saa5050(r1b_im_t* im);
void r1b_upsample2x_epx(r1b_im_t* im);
void r1b_upsample2x_eagle(r1b_im_t* im);
float r1b_hq2x_blend(unsigned rule, float E, float A, float B, float D, float F, float H) ;
void r1b_upsample2x_hqx(r1b_im_t* im);
void r1b_upsample2x(r1b_im_t* im, int mode);
void r1b_bedstead(r1b_im_t* im, int n);
void r1b_triangle(r1b_im_t* im,float x0 ,float y0 ,float x1 ,float y1 ,float x2 ,float y2 , r1b_im_t* pttn, int mode );
void r1b_rect(r1b_im_t* im,float x0 ,float y0 ,float x1 ,float y1 , r1b_im_t* pttn, int mode);
void r1b_line(r1b_im_t* im, float x0 ,float y0 ,float x1 ,float y1, float val, int mode);
void r1b_lines(r1b_im_t* im, float* Xs, float* Ys, int n, int close, float val, int mode);
void r1b_thick_line(r1b_im_t* im, float x0, float y0, float x1, float y1, float val, int thick, int mode);
r1b_font_t r1b_load_font_hex(const char* path, int h, int cp0, int cp1, int flags) ;
void r1b_destroy_font(r1b_font_t* font);
int r1b_glyph_index_lin_search(r1b_font_t* font, int cp);
int r1b_glyph_index_bin_search(r1b_font_t* font, int cp, int i0, int i1);
int r1b_glyph_index(r1b_font_t* font, int cp);
int r1b_putchar(r1b_im_t* im, int cp, int x, int y, r1b_font_t* font,float val, int mode, int highlight);
void r1b_text(r1b_im_t* im, wchar_t* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight);
void r1b_text_utf8(r1b_im_t* im, char* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight);
void r1b_text_ascii(r1b_im_t* im, char* str, int x, int y, r1b_font_t* font, float val, int mode, int highlight);
float r1b_area(float* X, float* Y, int n) ;
int r1b_triangulate_snip(float* X, float* Y,int u,int v,int w,int n,int *V ) ;
int r1b_triangulate(float* X, float* Y, int n, int* triangles) ;
void r1b_polygon_convex(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode);
void r1b_polygon_concave(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode);
void r1b_polygon(r1b_im_t* im, float* Xs, float* Ys, int n, r1b_im_t* pttn, int mode, int typ);
void r1b_ellipse(r1b_im_t* im, float cx, float cy, float rx, float ry, float ang, r1b_im_t* pttn, int mode);
void r1b_line_ellipse(r1b_im_t* im, float cx, float cy, float rx, float ry, float ang, int detail, float val, int mode);
void r1b_blit(r1b_im_t* dst, r1b_im_t* src, r1b_im_t* msk, float x0, float y0, float x1, float y1, float sx, float sy, int bdmode, int mode);
void r1b_paste(r1b_im_t* dst, r1b_im_t* src, float x, float y);
r1b_mesh_t r1b_load_obj(const char* path);
void r1b_mesh_bbox(r1b_mesh_t* mesh, float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax);
void r1b_normalize_mesh(r1b_mesh_t* mesh);
void r1b_destroy_mesh(r1b_mesh_t* mesh);
void r1b_triangle3d(r1b_im_t* im, r1b_im_t* depth, float f, float x0, float y0, float z0, float x1 ,float y1, float z1, float x2 ,float y2, float z2, r1b_im_t* pttn, float* vals, int mode );
void r1b_line3d(r1b_im_t* im, r1b_im_t* depth, int depth_read, float f, float x0 ,float y0, float z0, float x1 ,float y1, float z1, float val, int mode);
void r1b_transform_mesh(r1b_mesh_t* mesh, float* mat);
void r1b_compute_vertex_normals(r1b_mesh_t* mesh);
void r1b_render_mesh(r1b_im_t* im, r1b_im_t* depth, r1b_mesh_t* mesh, float f, r1b_im_t* pttn, float* light, int wire_val, int shdr, int wire);
r1b_im_t r1b_make_kernel(int ksize, int mode);
void r1b_conv2d(r1b_im_t* im, r1b_im_t* kern, int border) ;
void r1b_dilate(r1b_im_t* im, r1b_im_t* kern);
void r1b_erode(r1b_im_t* im, r1b_im_t* kern);
void r1b_sobel(r1b_im_t* im, float* out_gradient_directions);
void r1b_blur(r1b_im_t* im, int rad, int mode);
void r1b_canny(r1b_im_t* im, int blur_rad, float thresh_lo, float thresh_hi);
void r1b_threshold(r1b_im_t* im, float th);
void r1b_threshold_adaptive(r1b_im_t* im, int rad, float bias, int blur_mode);

void* nullptr(){
 	return NULL;
}

%pythoncode %{

cleanup=r1b_cleanup
read=r1b_read
snapshot=r1b_snapshot
zeros=r1b_zeros
ones=r1b_ones
from_array=r1b_from_array
infs=r1b_infs
free=r1b_free
transpose=r1b_transpose
transpose_flip=r1b_transpose_flip
normalize=r1b_normalize
copy_of=r1b_copy_of
copy_to=r1b_copy_to
dither=r1b_dither
log=r1b_log
encode=r1b_encode
encode2file=r1b_encode2file
lpr=r1b_lpr
resample=r1b_resample
get=r1b_get
set=r1b_set
upsample2x_saa5050=r1b_upsample2x_saa5050
upsample2x_epx=r1b_upsample2x_epx
upsample2x_eagle=r1b_upsample2x_eagle
hq2x_blend=r1b_hq2x_blend
upsample2x_hqx=r1b_upsample2x_hqx
upsample2x=r1b_upsample2x
bedstead=r1b_bedstead
triangle=r1b_triangle
rect=r1b_rect
line=r1b_line
thick_line=r1b_thick_line
load_font_hex=r1b_load_font_hex
destroy_font=r1b_destroy_font
glyph_index=r1b_glyph_index
putchar=r1b_putchar
text_utf8=r1b_text_utf8
text_ascii=r1b_text_ascii
triangulate=r1b_triangulate
ellipse=r1b_ellipse
line_ellipse=r1b_line_ellipse
blit=r1b_blit
paste=r1b_paste
load_obj=r1b_load_obj
normalize_mesh=r1b_normalize_mesh
destroy_mesh=r1b_destroy_mesh
triangle3d=r1b_triangle3d
line3d=r1b_line3d
compute_vertex_normals=r1b_compute_vertex_normals
make_kernel=r1b_make_kernel
conv2d=r1b_conv2d
dilate=r1b_dilate
erode=r1b_erode
sobel=r1b_sobel
blur=r1b_blur
canny=r1b_canny
threshold=r1b_threshold
threshold_adaptive=r1b_threshold_adaptive

INFER=R1B_INFER
DTHR_ORD=R1B_DTHR_ORD
DTHR_FS=R1B_DTHR_FS
SMPL_NN=R1B_SMPL_NN
SMPL_BILINEAR=R1B_SMPL_BILINEAR
BRDR_COPY=R1B_BRDR_COPY
BRDR_ZERO=R1B_BRDR_ZERO
BRDR_NONE=R1B_BRDR_NONE
BRDR_WRAP=R1B_BRDR_WRAP
FONT_HEX=R1B_FONT_HEX
BLIT_OR=R1B_BLIT_OR
BLIT_ADD=R1B_BLIT_ADD
BLIT_FLIP=R1B_BLIT_FLIP
BLIT_SET=R1B_BLIT_SET
POLY_CONVEX=R1B_POLY_CONVEX
POLY_CONCAVE=R1B_POLY_CONCAVE
WIRE_NONE=R1B_WIRE_NONE
WIRE_FRONT=R1B_WIRE_FRONT
WIRE_ALL=R1B_WIRE_ALL
SHDR_NONE=R1B_SHDR_NONE
SHDR_FLAT=R1B_SHDR_FLAT
SHDR_NDOTL=R1B_SHDR_NDOTL
SHDR_NDOTLF=R1B_SHDR_NDOTLF
UP2X_SAA5050=R1B_UP2X_SAA5050
UP2X_EPX=R1B_UP2X_EPX
UP2X_EAGLE=R1B_UP2X_EAGLE
UP2X_HQX=R1B_UP2X_HQX
KERN_ELLIPSE=R1B_KERN_ELLIPSE
KERN_GAUSS=R1B_KERN_GAUSS
KERN_GAUSS1D=R1B_KERN_GAUSS1D
KERN_CROSS=R1B_KERN_CROSS
KERN_RECT=R1B_KERN_RECT
BLUR_GAUSS=R1B_BLUR_GAUSS
BLUR_BOX=R1B_BLUR_BOX
FLAG_SORTED=R1B_FLAG_SORTED

def from_list(lst):
	h = len(lst)
	w = len(lst[0])
	arr = FloatArray(w*h)
	for i in range(h):
		for j in range(w):
			arr[i*w+j] = lst[i][j]
	return r1b_from_array(w,h,arr)

def to_list(im):
	lst = []
	for i in range(im.h):
		lst.append([])
		for j in range(im.w):
			lst[-1].append(get(im,j,i,BRDR_NONE))
	return lst

def float_array(lst):
	arr = FloatArray(len(lst))
	for i in range(len(lst)):
		arr[i] = lst[i]
	return arr

def lines(im,pts,close,val,mode):
	X,Y = zip(*pts)
	return r1b_lines(im,float_array(X),float_array(Y),len(X),close,val,mode)

def polygon(im,pts,pttn,mode):
	X,Y = zip(*pts)
	return r1b_polygon(im,float_array(X),float_array(Y),len(X),pttn,mode)

def transform_mesh(mesh,mat):
	return r1b_transform_mesh(mesh,float_array(mat))

def render_mesh(im, depth, mesh, f, pttn, light, wire_val, shdr, wire):
	if pttn == None:
		pttn = nullptr()

	if light != None:
		return r1b_render_mesh(im, depth, mesh, f, nullptr(), float_array(light), wire_val, shdr, wire)
	else:
		return r1b_render_mesh(im, depth, mesh, f, pttn, nullptr(), wire_val, shdr, wire)

PTTN_SOLID = r1b_from_array( 1, 1, float_array([1]))
PTTN_GRAY5 = r1b_from_array( 4, 4, float_array([1,1,0,1,  1,1,1,1,  0,1,1,1,  1,1,1,1,  ]))
PTTN_GRAY4 = r1b_from_array( 4, 4, float_array([1,1,0,1,  0,1,1,1,  1,1,0,1,  0,1,1,1,  ]))
PTTN_GRAY3 = r1b_from_array( 2, 2, float_array([1,0,  0,1,  ]))
PTTN_GRAY2 = r1b_from_array( 4, 4, float_array([0,0,1,0,  1,0,0,0,  0,0,1,0,  1,0,0,0,  ]))
PTTN_GRAY1 = r1b_from_array( 4, 4, float_array([0,0,1,0,  0,0,0,0,  1,0,0,0,  0,0,0,0,  ]))
PTTN_EMPTY = r1b_from_array( 1, 1, float_array([0]))
PTTN_GRID1 = r1b_from_array( 2, 2, float_array([0,1,  1,1,  ]))
PTTN_GRID2 = r1b_from_array( 4, 4, float_array([0,0,0,1,  0,0,0,1,  0,0,0,1,  1,1,1,1,  ]))
PTTN_DOTS1 = r1b_from_array( 2, 2, float_array([1,0,  0,0,  ]))
PTTN_DOTS2 = r1b_from_array( 4, 4, float_array([1,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  ]))
PTTN_DOTSR = r1b_from_array(12,12, float_array([0,0,0,0,0,1,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,1,0,0,0,0,0,0,0,0,0,1,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,1,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,1,0,0,0,0,0,1,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,1,0,0,0,0,0,0,1,0,0,  ]))
PTTN_HRZL1 = r1b_from_array( 1, 2, float_array([1,  0,  ]))
PTTN_VRTL1 = r1b_from_array( 2, 1, float_array([1,0,  ]))
PTTN_HRZL2 = r1b_from_array( 1, 4, float_array([1,  0,  0,  0,  ]))
PTTN_VRTL2 = r1b_from_array( 4, 1, float_array([1,0,0,0,  ]))
PTTN_DGNLL = r1b_from_array( 4, 4, float_array([0,0,0,1,  0,0,1,0,  0,1,0,0,  1,0,0,0,  ]))
PTTN_DGNLR = r1b_from_array( 4, 4, float_array([1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1,  ]))
PTTN_CROSS = r1b_from_array( 4, 4, float_array([1,0,0,0,  0,1,0,1,  0,0,1,0,  0,1,0,1,  ]))
PTTN_BRICK = r1b_from_array( 8, 8, float_array([1,1,1,1,1,1,1,1,  0,0,0,0,1,0,0,0,  0,0,0,0,1,0,0,0,  0,0,0,0,1,0,0,0,  1,1,1,1,1,1,1,1,  1,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,  ]))
PTTN_SCALE = r1b_from_array( 8, 8, float_array([0,0,0,0,1,0,0,0,  0,0,0,1,0,1,0,0,  1,1,1,0,0,0,1,1,  1,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,  0,1,0,0,0,0,0,1,  0,0,1,1,1,1,1,0,  0,0,0,0,1,0,0,0,  ]))
PTTN_WAVES = r1b_from_array( 8, 8, float_array([0,0,0,0,0,0,1,0,  0,0,0,0,0,1,0,1,  1,0,0,0,1,0,0,0,  1,0,0,0,1,0,0,0,  1,0,0,0,1,0,0,0,  1,0,0,0,1,0,0,0,  0,1,0,1,0,0,0,0,  0,0,1,0,0,0,0,0,  ]))
PTTN_CHESS = r1b_from_array( 4, 4, float_array([1,1,0,0,  1,1,0,0,  0,0,1,1,  0,0,1,1,  ]))
PTTN_DMOND = r1b_from_array( 8, 8, float_array([0,0,0,0,1,0,0,0,  0,0,0,1,0,1,0,0,  0,0,1,0,1,0,1,0,  0,1,0,1,0,1,0,1,  0,0,1,0,1,0,1,0,  0,0,0,1,0,1,0,0,  0,0,0,0,1,0,0,0,  0,0,0,0,0,0,0,0,  ]))

FONT_FG8X12 = r1b_get_font_fg8x12()

NULL = nullptr()

%}


