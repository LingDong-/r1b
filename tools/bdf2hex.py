import os
from glob import glob

bdfs = glob("../../bitmap-fonts/bitmap/*/bdf/*.bdf")+glob("../../bitmap-fonts/bitmap/*/*.bdf")

def bdf2hex(path):
	
	s = open(path,'r').read()
	h = int(s.split("SIZE ")[1].strip().split(" ")[0])
	a = [(int(x.split("ENCODING ")[1].split("\n")[0]),x.split("BITMAP\n")[1].split("\nENDCHAR")[0].split("\n")) for x in s.split("STARTCHAR")[1:]]

	how_strange = sum([len(x[1])!=h for x in a]);

	if (how_strange < 2) and len(a) >= 26:
		a = [x for x in a if len(x[1])==h]
		os.system("mkdir ../fonts/tecate/"+str(h))

		hx = "\n".join([hex(x[0]).split('x')[1].zfill(4).upper()+":"+"".join(x[1]) for x in a])
		open('../fonts/tecate/'+str(h)+"/"+(path.split("/")[-1].split(".")[0])+".hex",'w').write(hx)

for b in bdfs:
	bdf2hex(b)

