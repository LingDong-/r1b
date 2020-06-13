# r1b Manual

## Getting Started

First grab `build/r1b.h` from this repo and put it in your project folder, then:

```c
#include "r1b.h"
```

Done! 


Let's try to do a simple drawing!

```c
#include "r1b.h"

int main(){
    //initialize a new image of zeros
	r1b_im_t im = r1b_zeros(384,384);
	
	//draw an ellipse
	r1b_ellipse(
	    &im,    // pointer to the image
	    50,80,  // center coordinate
	    40,60,  // radius on each axis
	    M_PI/4, // rotation
	    R1B_PATTERN(BRICK), // cool pattern fill!
	    R1B_BLIT_SET // overwrite the pixels on the image
	);
	
	// save a snapshot of current image to png file
	r1b_snapshot("out.png",&im);
	
	// write a ESC/POS printable document!
	r1b_encode2file("out.bin",&im);
}

```


Note that `build/r1b.h` is the concatenated version which contains the entire source code of [*stbi*](https://github.com/nothings/stb) library for image reading and writing. Alternatively, you can include the more compact `r1b.h` at top-level of this repo. You'll now have two options: To not use stbi at all (and perhaps use your own image library of preference), do:

```c
#R1B_CONFIG_NO_STBI
#include "r1b.h"
```

Or, you can grab a copy of *stbi* from the [original author](https://github.com/nothings/stb), or, from the `external` folder of this repo, and place it in your project folder, then:

```c
#define R1B_CONFIG_STBI_PATH  "path/to/stb_image.h"
#define R1B_CONFIG_STBIW_PATH "path/to/stb_image_write.h"
#include "r1b.h"
```


## Basic Shapes and Patterns

### Shapes

We saw how to draw an ellipse in the last section, let's do a rectangle:

```c
r1b_im_t im = r1b_zeros(384,384);

// draw a rectangle
r1b_rect(&im,
	10,  10,  // upper left corner
	110,110,  // lower right corner
	R1B_PATTERN(GRAY4), // a different pattern fill
	R1B_BLIT_SET,
);

```

Let's draw a triangle on top of it, but instead of overwriting the pixels, we also can flip the pixels so we can tell between the shapes even if they have the same pattern fill:

```c
// draw a triangle
r1b_triangle(&im,
	10,  10,  // first vertex
	110,110,  // second vertex
	110,110,  // third vertex
	R1B_PATTERN(GRAY4),
	R1B_BLIT_FLIP,  // <-- flip the pixels!
);

```

For most of the operations, you'll be able to set the blit flag for different compositing methods, available options are:

- `R1B_BLIT_SET`:  overwrite the pixel;
- `R1B_BLIT_FLIP`: flip the value of the pixel;
- `R1B_BLIT_OR`:   turn on the pixel if it's off;
- `R1B_BLIT_ADD`:  add the value to the original.

Lines:

```c
// perfect 1 pixel line
r1b_line(&im,
	0,    0, // first endpoint
	100,100, // second endpoint
	1,       // color
	R1B_BLIT_SET
);

// a bolder line
// perfect 1 pixel line
r1b_thick_line(&im,
	0,    0, // first endpoint
	100,100, // second endpoint
	1,       // color
	2,       // that much thicker on either side of the line
	R1B_BLIT_SET
);

```

### Builtin patterns

We'll go into more complex shapes in the next section, but first let's check out all the pattern fills. There're 24 builtin patterns, all implemented as C macros. Let's draw them as a "color card" for future reference.


```c
r1b_im_t* get_nth_pattern(n){
  // access each builtin pattern by index
  switch (n) {
    case  0: return R1B_PATTERN(SOLID);
    case  1: return R1B_PATTERN(GRAY5);
    case  2: return R1B_PATTERN(GRAY4);
    case  3: return R1B_PATTERN(GRAY3);
    case  4: return R1B_PATTERN(GRAY2);
    case  5: return R1B_PATTERN(GRAY1);
    case  6: return R1B_PATTERN(EMPTY);
    case  7: return R1B_PATTERN(GRID1);
    case  8: return R1B_PATTERN(GRID2);
    case  9: return R1B_PATTERN(DOTS1);
    case 10: return R1B_PATTERN(DOTS2);
    case 11: return R1B_PATTERN(DOTSR);
    case 12: return R1B_PATTERN(HRZL1);
    case 13: return R1B_PATTERN(HRZL2);
    case 14: return R1B_PATTERN(VRTL1);
    case 15: return R1B_PATTERN(VRTL2);
    case 16: return R1B_PATTERN(DGNLL);
    case 17: return R1B_PATTERN(DGNLR);
    case 18: return R1B_PATTERN(CROSS);
    case 19: return R1B_PATTERN(BRICK);
    case 20: return R1B_PATTERN(SCALE);
    case 21: return R1B_PATTERN(WAVES);
    case 22: return R1B_PATTERN(CHESS);
    case 23: return R1B_PATTERN(DMOND);
  }
  return NULL;
}
int main(){
	r1b_im_t im = r1b_zeros(384,2400);
	
	for (int i = 0; i < 24; i++){
		r1b_im_t* pttn = get_nth_pattern(i);
		// draw a rect for each pattern
		r1b_rect(&im,
			0,       i*100,   // upper left corner
			384, (i+1)*100,   // lower right corner
			pttn, R1B_BLIT_SET);
	}
	
	r1b_snapshot("out.png",&im);
	r1b_encode2file("out.bin",&im);
}
```

Note that the pattern names (e.g. `SOLID`, `GRAY5` etc.) does not pollute the global namespace, they're used as verbatim strings in the macro and does not have meaning elsewhere. (Look into the source code for `R1B_PATTERN()` and see the magic!)


### Custom Patterns

In fact, patterns are also just an image type, so we can create our own quite easily.


```c
// data for a 4x4 "L" shaped pattern.
float pattern_data[16] = {
	0,1,0,0,
	0,1,0,0,
	0,1,1,1,
	0,0,0,0,
};

r1b_im_t pttn = r1b_from_array(
	4, //width
	4, //height
	pattern_data //data array
);

``` 

r1b uses 1-channel row-major floating point arrays for storing all image data, we'll go into more of that later.

Use it to draw the ellipse in the first demo:

```c
r1b_ellipse(&im, 50,80,40,60,M_PI/4, 
    &pttn, // <-- pointer to our pattern!
    R1B_BLIT_SET);

```

## More shapes

We can drawn an arbitrary polygon defined by arrays of coordinates.

```c
float X[] = {50, 80, 110, 10, 50, 20}; // x coordinates
float Y[] = {15, 10, 110, 60, 50, 20}; // y coordinates

r1b_polygon(&im,
	X,Y, // vertices
	6,   // number of vertices
	R1B_PATTERN(SCALE), R1B_BLIT_SET,
	R1B_POLY_CONCAVE // we're drawing a concave polygon
);
``` 

The `R1B_POLY_CONVEX` mode can be passed in place of `R1B_POLY_CONCAVE` if we're sure that our polygon is convex for a speed up; otherwise `R1B_POLY_CANCAVE` works for both situations.

We can draw an outline for the polygon as a polyline with `r1b_lines`:

```c
r1b_lines(&im,
	X,Y, // vertices
	6,   // number of vertices
	1,   // closed? closed -> polygon, open -> polyline
	1,   // color
	R1B_BLIT_SET
);
```


We can also draw outline for our previous ellipse with `r1b_line_ellipse`:

```c
r1b_line_ellipse(
    &im,    // pointer to the image
    50,80,  // center coordinate
    40,60,  // radius on each axis
    M_PI/4, // rotation
    32,     // detail, number of segments used to approximate the ellipse
    1,      // color
    R1B_BLIT_SET // overwrite the pixels on the image
);
```

## Images and the Image Struct

Here's how to read images from disk, resize them (so it fits in the thermal printer) and dither them to 1 bit:

```c
// read from disk as grayscale
r1b_im_t im = r1b_read("examples/assets/peppers.png");

// resize the image
r1b_resample(
    &im,       // pointer to image
    384,       // width
    R1B_INFER, // height, we can use R1B_INFER to
               // scale proportionally based on given width
	R1B_SMPL_BILINEAR  // resampling method
	                   // use R1B_SMPL_NN for nearest neighbor
);

// dither with Floyd-Steinberg algorithm
r1b_dither(&im, R1B_DTHR_FS);

// we can also use ordered dithering for a more "retro" look
// r1b_dither(&im, R1b_DTHR_ORD);

// `im` is now dithered. save the output!
r1b_snapshot("out.png",&im);

```


In r1b, all images are internally stored as 1-channel row-major floating point array. Though r1b claims to be a library for 1-bit graphics, it is often necessary to operate on grayscale images before binarizing it to 1-bit using thresholding or dithering. Thefore, to avoid the inconvenience and inefficiency of constantly converting between types, we store even binary images as floating points, typically using 0.0 and 1.0 to mean on and off. This also makes it possible to abuse r1b as grayscale or even full RGB or RGBA processing. Most of the operations do not assume propeties of the pixels stored and merely copy the value around. So with a bit of bit-twiddling we can reinterpret the 32-bits of the float for anything, e.g. a hex color 0xAARRGGBB.

Here's a short list of basic operations for images:

```c
r1b_zeros(width,height); // image of all 1's 
r1b_ones(width,height);  // image of all 1's 
r1b_infs(width,height);  // image of infinities, useful for depth buffer

r1b_im_t dst = r1b_copy_of(&src); // duplicate an image
r1b_copy_to(&src,&dst); // src and dst should be the same size
r1b_normalize(&im,0.0,1.0); // normalize image to given range
r1b_transpose(&im);
r1b_transpose_flip(&im); // effectively rotating image by 90°
                         // useful for fitting a fat image to the printer
r1b_log(&im);    // print image to stdout for debugging
```

All operations on images are in-place, including drawing routines, image processing etc. Internally, some operations are inherently in-place while some are not, however we unify to make all of them appear in place to the user for consistency and convenience (typically we need a series of operations for one specific effect). To support this efficiently, r1b has 2 internal buffers for inherently non in-place operations, and upon returning, it either does a `memcpy` or simply swap out the data pointer, so in fact there's minimum memory allocation/freeing happening behind the scene. 

You can keep a copy of the original image using `r1b_copy_of()` and use `r1b_cleanup()` to free these internal buffers if you're in dire need of memory.

We'll see more advanced image processing tricks in future sections.

## Font and Text

r1b supports the rendering of bitmap fonts. It has a default font burnt into the code that is always available, and you can also load more custom fonts with unifont `.hex` format.

The builtin font is accessible through `R1B_FONT_FG8X12` which is based on the [freeglut 8x13 bitmap font](ftp://146.255.57.4/nongnu/construo/doxygen/freeglut__font__data_8c-source.html). Here's an example:

```c
r1b_text(&im,
	L"Hello World!", // the string!
	10,10, // upper left corner
	R1B_FONT_FG8X12, // pointer to font
	1, // color
	R1B_BLIT_SET,
	0 // highlight: use 1 for standing out from busy background
);

```

Wide chars strings (`wchar_t*`) are used by `r1b_text` to support unicode. Alternatively, you can use `r1b_text_ascii()` to draw exclusively ASCII characters, or `r1b_text_utf8()` to draw a utf-8 encoded string. They have an identical signature.

We can also load `.hex` fonts from the disk. For example, unifont is an awesome bitmap font that supports most of the glyphs in unicode:

```c
r1b_font_t font = r1b_load_font_hex(
    "fonts/unifont.hex", // path to the font file
    16,     // height of the font. 
            // this must be the correct height of the bitmap font
            // unless you're looking for funny results
    0,      // lowest of the code point range to load
    INT_MAX,// highest of the code point range to load
    R1B_FLAG_SORTED  // font is sorted by unicode code point
);
```

if we don't need the whole unifont (or want to save space), we can load only a range of it using the third and fourth arguments. In the above example we used `(0,INT_MAX)` for the full range. Anyways, let's draw some unicode!

```c
r1b_text(&im,
	L"問天地好在", // the unicode string!
	10,10, // upper left corner
	&font, // pointer to font
	1, // color
	R1B_BLIT_SET,
	0 // highlight: use 1 for standing out from busy background
);
```

There are about 200 aditional bitmap fonts included in the `font` folder of this repo for your convenience. Most of them are converted from BDF format downloaded from [https://github.com/Tecate/bitmap-fonts](https://github.com/Tecate/bitmap-fonts). Beware that they might have different license from the r1b library itself. e.g. Unifont is GNU licensed.


## 3D


## Image Processing