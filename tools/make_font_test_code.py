import os
from glob import glob

out = ""

hxs = sorted(glob("../fonts/tecate/*/*.hex"),key=lambda x:-int(x.split("/")[-2]))

y = 2
for hx in hxs:
	h = int(hx.split("/")[-2])
	hx = hx.replace("../","")

	bname = hx.split("/")[-1].split(".")[0];
	name = "font_"+bname.replace("-","_")
	
	out += f'printf("testing {bname}...\\n");\n'
	out += f'r1b_font_t {name} = r1b_load_font_hex("{hx}",{h},0,INT_MAX,R1B_FLAG_SORTED);\n';
	out += f'r1b_text(&im, L"{bname}: Sphinx of black quartz, judge my vow! 0.123456789",2,{y},&{name},1,R1B_BLIT_SET,0);\n';
	out += f'r1b_destroy_font(&{name});\n'

	out += "\n"
	y += h+2;

print(out)