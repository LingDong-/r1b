import re
import os

os.system("python3 cat_c.py")


txt = open('../r1b.h','r').read()

structs = re.findall(r'typedef.*?\{.*?\} *r1b_.*?_t;',txt.replace("\n",""))

macros = [x for x in txt.replace("\\\n","").split("\n") if x.startswith("#define R1B_") and len(x.strip().split(" "))>2]

macros = [x for x in macros if (not ("(" in x)) and (not ("{" in x))]

lines = txt.split("\n")
funcs = []

for l in lines:
	l = l.strip();
	if len(l.split(" "))<2:
		continue

	ll = l.split(" ");
	if ll[1].startswith("r1b_") and ll[0] != "}" and l.strip().endswith("{") and "=" not in l:
		funcs.append(l.replace("{",";"))

iface = "\n".join(macros+structs+funcs)

impl0 = """
make_tmp0
make_tmp1
dither_fs
dither_ord
resample_nearest
resample_bilinear
glyph_index_lin_search
glyph_index_bin_search
area
triangulate_snip
polygon_convex
polygon_concave
mesh_bbox
get_font_fg8x12
text
"""

impl1 = """
lines
polygon
transform_mesh
render_mesh
"""

impl = [x for x in (impl0+impl1).split("\n") if len(x)]

pubs = [x.strip().split("(")[0].split(" ")[1][4:] for x in funcs]
pubs = [x for x in pubs if x not in impl]

pubmacros = [x.split(" ")[1][4:] for x in macros]

newline = "\n"

code = f"""

%include "carrays.i"
%array_class(float, FloatArray);


%module r1b

%{{

{iface}

void* nullptr(){{
 	return NULL;
}}


%}}

{iface}

void* nullptr(){{
 	return NULL;
}}

%pythoncode %{{

{newline.join([x+"=r1b_"+x for x in pubs])}

{newline.join([x+"=R1B_"+x for x in pubmacros])}

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

%}}


"""
# print(code)

open("../py/r1b.i",'w').write(code)


os.system("cd ../py; sh compile.sh")

