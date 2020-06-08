lines = open('../r1b.h','r').read().split("\n")

for l in lines:
	if len(l.split(" "))<2:
		continue

	ll = l.split(" ");
	if ll[1].startswith("r1b_") and ll[0] != "}" and l.strip().endswith("{"):
		print(l.replace("{",";"))