# typedef struct {
#   int h;
#   char* glyphs;
#   int n;
#   uint32_t* offsets;
#   uint8_t*  sizes;
#   uint16_t* cmap;
#   int flags;
# } r1b_font_t;

path = "../fonts/freeglut8x12.hex"

B = [[int(x[0:4],16),[int(x[i+5:i+7],16) for i in range(0,len(x)-5,2)]] for x in open(path,'r').read().split("\n") if len(x)][0:95]

flatten = lambda l: [item for sublist in l for item in sublist]

C = "static char     R1B_FG8X12_GLYPHS [] = {"+",".join([str(y) for y in flatten([x[1] for x in B])])+"};"
D = "static uint32_t R1B_FG8X12_OFFSETS[] = {"+",".join([str(x*2) for x in range(len(B))])+" };"
E = "static uint8_t  R1B_FG8X12_SIZES  [] = {"+",".join([str(2) for x in range(len(B))])+" };"
F = "static uint16_t R1B_FG8X12_CMAP   [] = {"+",".join([str(x[0]) for x in B])+"};"
# C = [y for y in C for x in y]


print("\n".join([C,D,E,F]))

