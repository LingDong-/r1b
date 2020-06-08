import os
os.chdir("../")

# lines = open("r1b.h",'r').read().split("\n")
# for i in range(len(lines)):
# 	if lines[i].startswith('#include "'):
# 		f = lines[i].split('"')[1]
# 		lines[i] = open(f,'r').read()

# out = "\n".join(lines);

# open("build/r1b.h",'w').write(out);


out = open("r1b.h",'r').read()\
	.replace("#include R1B_CONFIG_STBI_PATH" ,"\n"+open("external/stb_image.h",      'r').read()+"\n")\
    .replace("#include R1B_CONFIG_STBIW_PATH","\n"+open("external/stb_image_write.h",'r').read()+"\n")\


open("build/r1b.c",'w').write(out);