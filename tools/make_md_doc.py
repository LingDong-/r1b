import xml.etree.cElementTree as ET

print("# r1b API documentation")

tree = ET.ElementTree(file="../doc/xml/r1b_8h.xml")
sections = tree.iter("sectiondef")
for sec in sections:
	if sec.attrib['kind'] != "func":
		continue
	memdefs = sec.iter("memberdef")
	for defn in memdefs:
		typ = defn.find("type").text
		if not typ:
			typ = defn.find("type").find("ref").text
		name = defn.find("name").text;
		brief = defn.find("briefdescription").find("para")
		if brief != None:
			brief = brief.text

		detail = defn.find("detaileddescription").find("para")
		if detail != None:
			detail = detail.text;

		params = defn.iter("parameteritem")

		if brief == None and detail == None:
			continue

		if brief.startswith("(internal use)"):
			continue
		# print(typ,name,brief,detail)

		defstr = defn.find("definition").text
		argstr = defn.find("argsstring").text
		print("### `"+defstr+argstr+"`")

		print("```")
		if brief != None:
			print(brief)
		if detail != None:
			print(detail)
		print("```")

		print("|parameter|description|")
		print("|---|---|")
		for par in params:
			pname = par.find("parameternamelist").find("parametername").text
			pdesc = par.find("parameterdescription").find("para").text
			
			print("|`"+pname+"`|```"+pdesc+"```|")

		ret = defn.iter("simplesect")
		print("\n")
		for r in ret:
			print("**return** `"+r.find("para").text+"`\n")

		print("\n\n-----------------\n\n")
		
