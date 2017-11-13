#
#		Generator
#
import re

src = [x.replace("\t"," ").replace("\n"," ") for x in open("scmp.def").readlines()]
src = [x if x.find("//") < 0 else x[:x.find("//")] for x in src]
src = [x.strip() for x in src if x.strip() != ""]

open("_scmp_support.h","w").write("\n".join([x[1:] for x in src if x[0] == ':']))
src = [x for x in src if x[0] != ':']
codes = [ None ] * 256
mnemonics = [ None ] * 256

for l in src:
	m = re.match("^([0-9A-F\-]+)\s*(\d+)\s*\"(.*?)\"\s*(.*)$",l)
	assert m is not None,"Syntax in "+l
	m1 = m.group(1)
	cycles = int(m.group(2))
	orange = [int(m1,16)] if len(m1) == 2 else range(int(m1[:2],16),int(m1[-2:],16)+1)
	for opcode in orange:
		assert mnemonics[opcode] is None,"Duplicate "+l
		mnemonics[opcode] = m.group(3).replace("%P",str(opcode%4)).lower()
		codes[opcode] = m.group(4).replace("%P",str(opcode%4))+";CYCLES += {0};break;".format(cycles)

for i in range(0,256):
	if mnemonics[i] is None:
		mnemonics[i] = "db {0:02x}".format(i)
		codes[i] = "break;"

mlist = ",".join(['"'+x+'"' for x in mnemonics])
open("_scmp_mnemonics.h","w").write("{"+mlist+" };\n")

h = open("_scmp_case.h","w")
for i in range(0,256):
	h.write("case 0x{0:02x}: /**** {1} ****/\n".format(i,mnemonics[i]))
	h.write("    "+codes[i]+"\n")
h.close()