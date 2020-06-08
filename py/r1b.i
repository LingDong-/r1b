%include "carrays.i"
%array_class(float, floatArray);

%module r1b
%{
typedef struct {
  int w;
  int h;
  float* data;
} r1b_im_t;

typedef struct {
  int h;
  char* glyphs;
  int n;
  uint32_t* offsets;
  uint8_t*  sizes;
  uint16_t* cmap;
  int flags;
} r1b_font_t;

typedef struct {
  float* X;
  float* Y;
  float* Z;
  int* tris;
  float* norms;
  int n_vtx;
  int n_tri;
} r1b_mesh_t;

void r1b_make_tmp0(int w, int h);
void r1b_make_tmp1(int w, int h);
void r1b_cleanup();
r1b_im_t r1b_read(const char* path);
r1b_im_t r1b_zeros(int w, int h);
r1b_im_t r1b_ones(int w, int h);
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
void r1b_snapshot(const char* path, r1b_im_t* im);
void r1b_resample_nearest(r1b_im_t* im, int w, int h);
void r1b_resample_bilinear(r1b_im_t* im, int w, int h);
void r1b_resample(r1b_im_t* im, int w, int h, int mode);
float r1b_get(r1b_im_t* im, int x, int y, int mode);
void r1b_set(r1b_im_t* im, int x, int y, float val, int mode);
void r1b_conv2d(r1b_im_t* im, r1b_im_t* kern, int border) ;
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
r1b_mesh_t r1b_load_obj(const char* path);
void r1b_mesh_bbox(r1b_mesh_t* mesh, float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax);
void r1b_normalize_mesh(r1b_mesh_t* mesh);
void r1b_destroy_mesh(r1b_mesh_t* mesh);
void r1b_triangle3d(r1b_im_t* im, r1b_im_t* depth, float f, float x0, float y0, float z0, float x1 ,float y1, float z1, float x2 ,float y2, float z2, r1b_im_t* pttn, float* vals, int mode );
void r1b_line3d(r1b_im_t* im, r1b_im_t* depth, int depth_read, float f, float x0 ,float y0, float z0, float x1 ,float y1, float z1, float val, int mode);
void r1b_transform_mesh(r1b_mesh_t* mesh, float* mat);
void r1b_compute_vertex_normals(r1b_mesh_t* mesh);
void r1b_render_mesh(r1b_im_t* im, r1b_im_t* depth, r1b_mesh_t* mesh, float f, r1b_im_t* pttn, float* light, int wire_val, int shdr, int wire);

%}

typedef struct {
  int w;
  int h;
  float* data;
} r1b_im_t;

typedef struct {
  int h;
  char* glyphs;
  int n;
  uint32_t* offsets;
  uint8_t*  sizes;
  uint16_t* cmap;
  int flags;
} r1b_font_t;

typedef struct {
  float* X;
  float* Y;
  float* Z;
  int* tris;
  float* norms;
  int n_vtx;
  int n_tri;
} r1b_mesh_t;

void r1b_make_tmp0(int w, int h);
void r1b_make_tmp1(int w, int h);
void r1b_cleanup();
r1b_im_t r1b_read(const char* path);
r1b_im_t r1b_zeros(int w, int h);
r1b_im_t r1b_ones(int w, int h);
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
void r1b_snapshot(const char* path, r1b_im_t* im);
void r1b_resample_nearest(r1b_im_t* im, int w, int h);
void r1b_resample_bilinear(r1b_im_t* im, int w, int h);
void r1b_resample(r1b_im_t* im, int w, int h, int mode);
float r1b_get(r1b_im_t* im, int x, int y, int mode);
void r1b_set(r1b_im_t* im, int x, int y, float val, int mode);
void r1b_conv2d(r1b_im_t* im, r1b_im_t* kern, int border) ;
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
r1b_mesh_t r1b_load_obj(const char* path);
void r1b_mesh_bbox(r1b_mesh_t* mesh, float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax);
void r1b_normalize_mesh(r1b_mesh_t* mesh);
void r1b_destroy_mesh(r1b_mesh_t* mesh);
void r1b_triangle3d(r1b_im_t* im, r1b_im_t* depth, float f, float x0, float y0, float z0, float x1 ,float y1, float z1, float x2 ,float y2, float z2, r1b_im_t* pttn, float* vals, int mode );
void r1b_line3d(r1b_im_t* im, r1b_im_t* depth, int depth_read, float f, float x0 ,float y0, float z0, float x1 ,float y1, float z1, float val, int mode);
void r1b_transform_mesh(r1b_mesh_t* mesh, float* mat);
void r1b_compute_vertex_normals(r1b_mesh_t* mesh);
void r1b_render_mesh(r1b_im_t* im, r1b_im_t* depth, r1b_mesh_t* mesh, float f, r1b_im_t* pttn, float* light, int wire_val, int shdr, int wire);

%pythoncode %{
%}