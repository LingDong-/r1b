import sys; sys.path.append("../")
import os
import re
import r1b

# person = "Pythagoras"
# person = "Socrates"
# person = "Plato"

person = "Aristotle"
# person = "Confucious"
# person = "Friedrich_Nietzsche"



os.system("curl https://en.wikipedia.org/wiki/"+person+" > tmp.html")
html = open("tmp.html",'r').read().replace("\n","");
os.system("rm tmp.html")

html = re.sub(r'&#.+?;',' ',html);

vcard = re.findall(r'<table class="infobox biography vcard.*?</table>',html)[0]
rows = re.findall(r'<tr.*?>.*?</tr>',vcard)

card = []
for r in rows:
	head = re.findall(r'<th.*?>(.*?)</th>',r)
	if len(head):
		head = head[0]
		head = re.sub(r'<.*?>',r'',head)
	else:
		head = ""

	items = re.findall(r'<td.*?>(.*?)</td>',r)
	items = " ".join([re.sub(r'<.*?>',r' ',x) for x in items])
	items = re.sub(r' +',' ',items);

	imgs = re.findall(r'<img.*src="(.*?)"',r)

	imgs = ["https:"+x if x.startswith("//") else x for x in imgs]
	
	if head or len(items) or len(imgs):
		card.append([head,items,imgs])

first = re.findall(r'<p>.+?</p>',html)[0]
first = re.sub(r'<.*?>',r'',first)

card.append(["",first,[]])

fonth = r1b.load_font_hex("../../fonts/tecate/32/spleen-16x32.hex",32,0,65535,r1b.FLAG_SORTED);
fontb = r1b.load_font_hex("../../fonts/tecate/16/spleen-8x16.hex",16,0,65535,r1b.FLAG_SORTED);
fontr = r1b.load_font_hex("../../fonts/unifont.hex",16,0,65535,r1b.FLAG_SORTED);

im = r1b.zeros(384,2000);

def is_ascii(s):
	return sum([ord(x)>=256 for x in s]) == 0

def text(im,s,x,y,f,v,m,h):
	if is_ascii(s):
		r1b.text_ascii(im,s,x,y,f,v,m,h);
	else:
		# if (len(s)<4):
			# s += " "
		r1b.text_utf8(im,s,x,y,f,v,m,h);

y = 0;
x = 0;
for i in range(len(card)):
	# print(card[i])
	if i == 0:
		text(im,card[i][0],4,y,fonth,1,r1b.BLIT_SET,0);
		y+=32
		continue;

	if len(card[i][2]):
		url = card[i][2][0]
		fmt = url.split(".")[-1]
		os.system("curl "+url+" > tmp."+fmt)
		pic = r1b.read("tmp."+fmt)
		os.system("rm tmp."+fmt)

		su = 0
		for k in range(pic.h):
			for l in range(pic.w):
				su += 1.0-r1b.get(pic,l,k,r1b.BRDR_ZERO)
		if su != 0:

			r1b.resample(pic,368,r1b.INFER,r1b.SMPL_BILINEAR)
			r1b.normalize(pic,-0.2,0.8)
			r1b.dither(pic,r1b.DTHR_FS)
			r1b.paste(im,pic,8,y)
			y+=pic.h

	text(im,card[i][0],4,y,fontb,1,r1b.BLIT_SET,0);
	x = len(card[i][0])*8+8

	words = card[i][1].split(" ")
	for w in words:
		if x+8*len(w) > 380:
			x = 4
			y += 16
		# print(w)
		text(im,w,x,y-2,fontr,1,r1b.BLIT_SET,0)
		x += 8*len(w)+8

	y+=16
	if i == len(card)-2:
		r1b.lines(im,[[0.5,2],[382,2],[382,y],[0.5,y]],1,1,r1b.BLIT_SET);
		y += 16
im.h = y

r1b.snapshot("out/wiki.png",im)

r1b.lpr("Printer_USB_Thermal_Printer",im);

r1b.destroy_font(fonth)
r1b.destroy_font(fontb)
r1b.destroy_font(fontr)
r1b.cleanup()


