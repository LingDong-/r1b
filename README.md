
<img align="left" src="examples/assets/r1b.png">

# r1b


*A thermal-printer-oriented, 1 bit graphics renderer for 2D and 3D.*

<br>
<br>
<hr>

- Header-only C99 library
- Builtin ESC/POS (printing commands) support.
- Rasterizes 2D and 3D primitives: lines, triangles, ellipses, polygons, meshes...
- Pattern fills: 24 builtin fills + custom designs. All area-filling drawing routines support patterns.
- Bitmap font support: use builtin font or load unifont .hex format, more than 200 other fonts included in the repo.
- Loads .obj 3D models and renders them with wireframes as well as shading.
- Dithers and thresholds images into 1 bit with various algorithms (Floyd-Steinberg, Ordered dithering, Otsu's threshold, Adaptive threshold...)
- Supports multiple pixel-art-upscaling backends: SAA5050, EPX, Eagle, HQX, Bedstead, as well as nearest neighbor and bilinear resampling.
- CV goodies: Sobel & Canny edge detection, Gaussin & box blur, Erosion, Dilation, Convolution.
- Python 3 binding available via SWIG!