//gcc examples/fonts.c
#include "../r1b.h"

int main(){

  r1b_im_t im = r1b_zeros(384,4000);

printf("testing spleen-32x64...\n");
r1b_font_t font_spleen_32x64 = r1b_load_font_hex("fonts/tecate/64/spleen-32x64.hex",64,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"spleen-32x64: Sphinx of black quartz, judge my vow! 0.123456789",2,2,&font_spleen_32x64,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_spleen_32x64);

printf("testing ter-u32n...\n");
r1b_font_t font_ter_u32n = r1b_load_font_hex("fonts/tecate/32/ter-u32n.hex",32,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u32n: Sphinx of black quartz, judge my vow! 0.123456789",2,68,&font_ter_u32n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u32n);

printf("testing spleen-16x32...\n");
r1b_font_t font_spleen_16x32 = r1b_load_font_hex("fonts/tecate/32/spleen-16x32.hex",32,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"spleen-16x32: Sphinx of black quartz, judge my vow! 0.123456789",2,102,&font_spleen_16x32,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_spleen_16x32);

printf("testing ter-u32b...\n");
r1b_font_t font_ter_u32b = r1b_load_font_hex("fonts/tecate/32/ter-u32b.hex",32,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u32b: Sphinx of black quartz, judge my vow! 0.123456789",2,136,&font_ter_u32b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u32b);

printf("testing ter-u28n...\n");
r1b_font_t font_ter_u28n = r1b_load_font_hex("fonts/tecate/28/ter-u28n.hex",28,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u28n: Sphinx of black quartz, judge my vow! 0.123456789",2,170,&font_ter_u28n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u28n);

printf("testing ter-u28b...\n");
r1b_font_t font_ter_u28b = r1b_load_font_hex("fonts/tecate/28/ter-u28b.hex",28,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u28b: Sphinx of black quartz, judge my vow! 0.123456789",2,200,&font_ter_u28b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u28b);

printf("testing ter-u24n...\n");
r1b_font_t font_ter_u24n = r1b_load_font_hex("fonts/tecate/24/ter-u24n.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u24n: Sphinx of black quartz, judge my vow! 0.123456789",2,230,&font_ter_u24n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u24n);

printf("testing neep-post-ampersand-12x24...\n");
r1b_font_t font_neep_post_ampersand_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-post-ampersand-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-post-ampersand-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,256,&font_neep_post_ampersand_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_post_ampersand_12x24);

printf("testing neep-iso8859-15-12x24...\n");
r1b_font_t font_neep_iso8859_15_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-15-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,282,&font_neep_iso8859_15_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_12x24);

printf("testing neep-iso8859-2-part-12x24...\n");
r1b_font_t font_neep_iso8859_2_part_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-2-part-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-part-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,308,&font_neep_iso8859_2_part_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_part_12x24);

printf("testing spleen-12x24...\n");
r1b_font_t font_spleen_12x24 = r1b_load_font_hex("fonts/tecate/24/spleen-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"spleen-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,334,&font_spleen_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_spleen_12x24);

printf("testing neep-alt-iso8859-1-12x24-bold...\n");
r1b_font_t font_neep_alt_iso8859_1_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-1-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-1-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,360,&font_neep_alt_iso8859_1_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_1_12x24_bold);

printf("testing neep-alt-iso8859-9-12x24-bold...\n");
r1b_font_t font_neep_alt_iso8859_9_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-9-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-9-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,386,&font_neep_alt_iso8859_9_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_9_12x24_bold);

printf("testing neep-alt-iso8859-1-12x24...\n");
r1b_font_t font_neep_alt_iso8859_1_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-1-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-1-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,412,&font_neep_alt_iso8859_1_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_1_12x24);

printf("testing neep-iso8859-15-12x24-bold...\n");
r1b_font_t font_neep_iso8859_15_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-15-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,438,&font_neep_iso8859_15_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_12x24_bold);

printf("testing neep-iso8859-9-part-12x24...\n");
r1b_font_t font_neep_iso8859_9_part_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-9-part-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-part-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,464,&font_neep_iso8859_9_part_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_part_12x24);

printf("testing neep-iso8859-1-12x24...\n");
r1b_font_t font_neep_iso8859_1_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-1-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,490,&font_neep_iso8859_1_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_12x24);

printf("testing neep-iso8859-1-part-12x24...\n");
r1b_font_t font_neep_iso8859_1_part_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-1-part-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-part-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,516,&font_neep_iso8859_1_part_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_part_12x24);

printf("testing neep-iso8859-15-part-12x24-bold...\n");
r1b_font_t font_neep_iso8859_15_part_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-15-part-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-part-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,542,&font_neep_iso8859_15_part_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_part_12x24_bold);

printf("testing neep-pre-ampersand-12x24...\n");
r1b_font_t font_neep_pre_ampersand_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-pre-ampersand-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-pre-ampersand-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,568,&font_neep_pre_ampersand_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_pre_ampersand_12x24);

printf("testing neep-alt-iso8859-2-12x24-bold...\n");
r1b_font_t font_neep_alt_iso8859_2_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-2-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-2-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,594,&font_neep_alt_iso8859_2_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_2_12x24_bold);

printf("testing neep-post-ampersand-12x24-bold...\n");
r1b_font_t font_neep_post_ampersand_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-post-ampersand-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-post-ampersand-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,620,&font_neep_post_ampersand_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_post_ampersand_12x24_bold);

printf("testing neep-alt-iso8859-2-12x24...\n");
r1b_font_t font_neep_alt_iso8859_2_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-2-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-2-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,646,&font_neep_alt_iso8859_2_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_2_12x24);

printf("testing neep-pre-ampersand-12x24-bold...\n");
r1b_font_t font_neep_pre_ampersand_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-pre-ampersand-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-pre-ampersand-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,672,&font_neep_pre_ampersand_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_pre_ampersand_12x24_bold);

printf("testing neep-iso8859-2-12x24...\n");
r1b_font_t font_neep_iso8859_2_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-2-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,698,&font_neep_iso8859_2_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_12x24);

printf("testing neep-iso8859-15-part-12x24...\n");
r1b_font_t font_neep_iso8859_15_part_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-15-part-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-part-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,724,&font_neep_iso8859_15_part_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_part_12x24);

printf("testing neep-iso8859-9-12x24...\n");
r1b_font_t font_neep_iso8859_9_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-9-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,750,&font_neep_iso8859_9_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_12x24);

printf("testing neep-iso8859-2-part-12x24-bold...\n");
r1b_font_t font_neep_iso8859_2_part_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-2-part-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-part-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,776,&font_neep_iso8859_2_part_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_part_12x24_bold);

printf("testing neep-iso8859-1-part-12x24-bold...\n");
r1b_font_t font_neep_iso8859_1_part_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-1-part-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-part-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,802,&font_neep_iso8859_1_part_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_part_12x24_bold);

printf("testing neep-iso8859-1-12x24-bold...\n");
r1b_font_t font_neep_iso8859_1_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-1-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,828,&font_neep_iso8859_1_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_12x24_bold);

printf("testing neep-alt-iso8859-9-12x24...\n");
r1b_font_t font_neep_alt_iso8859_9_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-9-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-9-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,854,&font_neep_alt_iso8859_9_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_9_12x24);

printf("testing neep-iso8859-9-12x24-bold...\n");
r1b_font_t font_neep_iso8859_9_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-9-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,880,&font_neep_iso8859_9_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_12x24_bold);

printf("testing neep-alt-iso8859-15-12x24-bold...\n");
r1b_font_t font_neep_alt_iso8859_15_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-15-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-15-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,906,&font_neep_alt_iso8859_15_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_15_12x24_bold);

printf("testing neep-iso8859-9-part-12x24-bold...\n");
r1b_font_t font_neep_iso8859_9_part_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-9-part-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-part-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,932,&font_neep_iso8859_9_part_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_part_12x24_bold);

printf("testing neep-alt-iso8859-15-12x24...\n");
r1b_font_t font_neep_alt_iso8859_15_12x24 = r1b_load_font_hex("fonts/tecate/24/neep-alt-iso8859-15-12x24.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-15-12x24: Sphinx of black quartz, judge my vow! 0.123456789",2,958,&font_neep_alt_iso8859_15_12x24,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_15_12x24);

printf("testing ter-u24b...\n");
r1b_font_t font_ter_u24b = r1b_load_font_hex("fonts/tecate/24/ter-u24b.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u24b: Sphinx of black quartz, judge my vow! 0.123456789",2,984,&font_ter_u24b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u24b);

printf("testing neep-iso8859-2-12x24-bold...\n");
r1b_font_t font_neep_iso8859_2_12x24_bold = r1b_load_font_hex("fonts/tecate/24/neep-iso8859-2-12x24-bold.hex",24,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-12x24-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1010,&font_neep_iso8859_2_12x24_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_12x24_bold);

printf("testing t0-22...\n");
r1b_font_t font_t0_22 = r1b_load_font_hex("fonts/tecate/22/t0-22.hex",22,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-22: Sphinx of black quartz, judge my vow! 0.123456789",2,1036,&font_t0_22,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_22);

printf("testing t0-22b...\n");
r1b_font_t font_t0_22b = r1b_load_font_hex("fonts/tecate/22/t0-22b.hex",22,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-22b: Sphinx of black quartz, judge my vow! 0.123456789",2,1060,&font_t0_22b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_22b);

printf("testing ter-u22n...\n");
r1b_font_t font_ter_u22n = r1b_load_font_hex("fonts/tecate/22/ter-u22n.hex",22,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u22n: Sphinx of black quartz, judge my vow! 0.123456789",2,1084,&font_ter_u22n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u22n);

printf("testing ter-u22b...\n");
r1b_font_t font_ter_u22b = r1b_load_font_hex("fonts/tecate/22/ter-u22b.hex",22,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u22b: Sphinx of black quartz, judge my vow! 0.123456789",2,1108,&font_ter_u22b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u22b);

printf("testing neep-iso8859-15-10x20...\n");
r1b_font_t font_neep_iso8859_15_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-15-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1132,&font_neep_iso8859_15_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_10x20);

printf("testing neep-post-ampersand-10x20...\n");
r1b_font_t font_neep_post_ampersand_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-post-ampersand-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-post-ampersand-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1154,&font_neep_post_ampersand_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_post_ampersand_10x20);

printf("testing TamzenForPowerline10x20b...\n");
r1b_font_t font_TamzenForPowerline10x20b = r1b_load_font_hex("fonts/tecate/20/TamzenForPowerline10x20b.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline10x20b: Sphinx of black quartz, judge my vow! 0.123456789",2,1176,&font_TamzenForPowerline10x20b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline10x20b);

printf("testing neep-iso8859-2-part-10x20...\n");
r1b_font_t font_neep_iso8859_2_part_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-2-part-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-part-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1198,&font_neep_iso8859_2_part_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_part_10x20);

printf("testing TamzenForPowerline10x20r...\n");
r1b_font_t font_TamzenForPowerline10x20r = r1b_load_font_hex("fonts/tecate/20/TamzenForPowerline10x20r.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline10x20r: Sphinx of black quartz, judge my vow! 0.123456789",2,1220,&font_TamzenForPowerline10x20r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline10x20r);

printf("testing neep-alt-iso8859-1-10x20-bold...\n");
r1b_font_t font_neep_alt_iso8859_1_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-1-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-1-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1242,&font_neep_alt_iso8859_1_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_1_10x20_bold);

printf("testing neep-alt-iso8859-9-10x20-bold...\n");
r1b_font_t font_neep_alt_iso8859_9_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-9-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-9-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1264,&font_neep_alt_iso8859_9_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_9_10x20_bold);

printf("testing 10x20O...\n");
r1b_font_t font_10x20O = r1b_load_font_hex("fonts/tecate/20/10x20O.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"10x20O: Sphinx of black quartz, judge my vow! 0.123456789",2,1286,&font_10x20O,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_10x20O);

printf("testing neep-alt-iso8859-1-10x20...\n");
r1b_font_t font_neep_alt_iso8859_1_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-1-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-1-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1308,&font_neep_alt_iso8859_1_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_1_10x20);

printf("testing neep-iso8859-1-part-10x20...\n");
r1b_font_t font_neep_iso8859_1_part_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-1-part-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-part-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1330,&font_neep_iso8859_1_part_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_part_10x20);

printf("testing Gomme10x20n...\n");
r1b_font_t font_Gomme10x20n = r1b_load_font_hex("fonts/tecate/20/Gomme10x20n.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Gomme10x20n: Sphinx of black quartz, judge my vow! 0.123456789",2,1352,&font_Gomme10x20n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Gomme10x20n);

printf("testing neep-iso8859-1-10x20...\n");
r1b_font_t font_neep_iso8859_1_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-1-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1374,&font_neep_iso8859_1_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_10x20);

printf("testing neep-iso8859-15-10x20-bold...\n");
r1b_font_t font_neep_iso8859_15_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-15-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1396,&font_neep_iso8859_15_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_10x20_bold);

printf("testing neep-iso8859-9-part-10x20...\n");
r1b_font_t font_neep_iso8859_9_part_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-9-part-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-part-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1418,&font_neep_iso8859_9_part_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_part_10x20);

printf("testing neep-pre-ampersand-10x20...\n");
r1b_font_t font_neep_pre_ampersand_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-pre-ampersand-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-pre-ampersand-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1440,&font_neep_pre_ampersand_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_pre_ampersand_10x20);

printf("testing ter-u20b...\n");
r1b_font_t font_ter_u20b = r1b_load_font_hex("fonts/tecate/20/ter-u20b.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u20b: Sphinx of black quartz, judge my vow! 0.123456789",2,1462,&font_ter_u20b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u20b);

printf("testing neep-alt-iso8859-2-10x20-bold...\n");
r1b_font_t font_neep_alt_iso8859_2_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-2-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-2-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1484,&font_neep_alt_iso8859_2_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_2_10x20_bold);

printf("testing neep-iso8859-15-part-10x20-bold...\n");
r1b_font_t font_neep_iso8859_15_part_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-15-part-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-part-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1506,&font_neep_iso8859_15_part_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_part_10x20_bold);

printf("testing neep-pre-ampersand-10x20-bold...\n");
r1b_font_t font_neep_pre_ampersand_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-pre-ampersand-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-pre-ampersand-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1528,&font_neep_pre_ampersand_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_pre_ampersand_10x20_bold);

printf("testing Tamzen10x20b...\n");
r1b_font_t font_Tamzen10x20b = r1b_load_font_hex("fonts/tecate/20/Tamzen10x20b.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen10x20b: Sphinx of black quartz, judge my vow! 0.123456789",2,1550,&font_Tamzen10x20b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen10x20b);

printf("testing neep-alt-iso8859-2-10x20...\n");
r1b_font_t font_neep_alt_iso8859_2_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-2-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-2-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1572,&font_neep_alt_iso8859_2_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_2_10x20);

printf("testing 10x20BO...\n");
r1b_font_t font_10x20BO = r1b_load_font_hex("fonts/tecate/20/10x20BO.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"10x20BO: Sphinx of black quartz, judge my vow! 0.123456789",2,1594,&font_10x20BO,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_10x20BO);

printf("testing neep-iso8859-2-10x20...\n");
r1b_font_t font_neep_iso8859_2_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-2-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1616,&font_neep_iso8859_2_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_10x20);

printf("testing ter-u20n...\n");
r1b_font_t font_ter_u20n = r1b_load_font_hex("fonts/tecate/20/ter-u20n.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u20n: Sphinx of black quartz, judge my vow! 0.123456789",2,1638,&font_ter_u20n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u20n);

printf("testing neep-post-ampersand-10x20-bold...\n");
r1b_font_t font_neep_post_ampersand_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-post-ampersand-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-post-ampersand-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1660,&font_neep_post_ampersand_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_post_ampersand_10x20_bold);

printf("testing neep-iso8859-1-10x20-bold...\n");
r1b_font_t font_neep_iso8859_1_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-1-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1682,&font_neep_iso8859_1_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_10x20_bold);

printf("testing neep-iso8859-1-part-10x20-bold...\n");
r1b_font_t font_neep_iso8859_1_part_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-1-part-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-part-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1704,&font_neep_iso8859_1_part_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_part_10x20_bold);

printf("testing neep-iso8859-9-10x20...\n");
r1b_font_t font_neep_iso8859_9_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-9-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1726,&font_neep_iso8859_9_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_10x20);

printf("testing neep-alt-iso8859-15-10x20-bold...\n");
r1b_font_t font_neep_alt_iso8859_15_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-15-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-15-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1748,&font_neep_alt_iso8859_15_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_15_10x20_bold);

printf("testing neep-iso8859-15-part-10x20...\n");
r1b_font_t font_neep_iso8859_15_part_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-15-part-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-part-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1770,&font_neep_iso8859_15_part_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_part_10x20);

printf("testing neep-iso8859-9-10x20-bold...\n");
r1b_font_t font_neep_iso8859_9_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-9-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1792,&font_neep_iso8859_9_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_10x20_bold);

printf("testing Tamzen10x20r...\n");
r1b_font_t font_Tamzen10x20r = r1b_load_font_hex("fonts/tecate/20/Tamzen10x20r.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen10x20r: Sphinx of black quartz, judge my vow! 0.123456789",2,1814,&font_Tamzen10x20r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen10x20r);

printf("testing neep-iso8859-2-part-10x20-bold...\n");
r1b_font_t font_neep_iso8859_2_part_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-2-part-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-part-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1836,&font_neep_iso8859_2_part_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_part_10x20_bold);

printf("testing 10x20B...\n");
r1b_font_t font_10x20B = r1b_load_font_hex("fonts/tecate/20/10x20B.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"10x20B: Sphinx of black quartz, judge my vow! 0.123456789",2,1858,&font_10x20B,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_10x20B);

printf("testing neep-alt-iso8859-9-10x20...\n");
r1b_font_t font_neep_alt_iso8859_9_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-9-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-9-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1880,&font_neep_alt_iso8859_9_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_9_10x20);

printf("testing knxt...\n");
r1b_font_t font_knxt = r1b_load_font_hex("fonts/tecate/20/knxt.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"knxt: Sphinx of black quartz, judge my vow! 0.123456789",2,1902,&font_knxt,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_knxt);

printf("testing neep-iso8859-2-10x20-bold...\n");
r1b_font_t font_neep_iso8859_2_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-2-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1924,&font_neep_iso8859_2_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_10x20_bold);

printf("testing 10x20...\n");
r1b_font_t font_10x20 = r1b_load_font_hex("fonts/tecate/20/10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1946,&font_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_10x20);

printf("testing neep-iso8859-9-part-10x20-bold...\n");
r1b_font_t font_neep_iso8859_9_part_10x20_bold = r1b_load_font_hex("fonts/tecate/20/neep-iso8859-9-part-10x20-bold.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-part-10x20-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,1968,&font_neep_iso8859_9_part_10x20_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_part_10x20_bold);

printf("testing neep-alt-iso8859-15-10x20...\n");
r1b_font_t font_neep_alt_iso8859_15_10x20 = r1b_load_font_hex("fonts/tecate/20/neep-alt-iso8859-15-10x20.hex",20,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-15-10x20: Sphinx of black quartz, judge my vow! 0.123456789",2,1990,&font_neep_alt_iso8859_15_10x20,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_15_10x20);

printf("testing t0-18...\n");
r1b_font_t font_t0_18 = r1b_load_font_hex("fonts/tecate/18/t0-18.hex",18,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-18: Sphinx of black quartz, judge my vow! 0.123456789",2,2012,&font_t0_18,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_18);

printf("testing t0-18b...\n");
r1b_font_t font_t0_18b = r1b_load_font_hex("fonts/tecate/18/t0-18b.hex",18,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-18b: Sphinx of black quartz, judge my vow! 0.123456789",2,2032,&font_t0_18b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_18b);

printf("testing ter-u18n...\n");
r1b_font_t font_ter_u18n = r1b_load_font_hex("fonts/tecate/18/ter-u18n.hex",18,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u18n: Sphinx of black quartz, judge my vow! 0.123456789",2,2052,&font_ter_u18n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u18n);

printf("testing t0-18i...\n");
r1b_font_t font_t0_18i = r1b_load_font_hex("fonts/tecate/18/t0-18i.hex",18,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-18i: Sphinx of black quartz, judge my vow! 0.123456789",2,2072,&font_t0_18i,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_18i);

printf("testing ter-u18b...\n");
r1b_font_t font_ter_u18b = r1b_load_font_hex("fonts/tecate/18/ter-u18b.hex",18,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u18b: Sphinx of black quartz, judge my vow! 0.123456789",2,2092,&font_ter_u18b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u18b);

printf("testing t0-17i...\n");
r1b_font_t font_t0_17i = r1b_load_font_hex("fonts/tecate/17/t0-17i.hex",17,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-17i: Sphinx of black quartz, judge my vow! 0.123456789",2,2112,&font_t0_17i,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_17i);

printf("testing t0-17b...\n");
r1b_font_t font_t0_17b = r1b_load_font_hex("fonts/tecate/17/t0-17b.hex",17,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-17b: Sphinx of black quartz, judge my vow! 0.123456789",2,2131,&font_t0_17b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_17b);

printf("testing t0-17...\n");
r1b_font_t font_t0_17 = r1b_load_font_hex("fonts/tecate/17/t0-17.hex",17,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-17: Sphinx of black quartz, judge my vow! 0.123456789",2,2150,&font_t0_17,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_17);

printf("testing zevv-peep-iso8859-15-08x16...\n");
r1b_font_t font_zevv_peep_iso8859_15_08x16 = r1b_load_font_hex("fonts/tecate/16/zevv-peep-iso8859-15-08x16.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"zevv-peep-iso8859-15-08x16: Sphinx of black quartz, judge my vow! 0.123456789",2,2169,&font_zevv_peep_iso8859_15_08x16,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_zevv_peep_iso8859_15_08x16);

printf("testing zevv-peep-iso8859-1-08x16...\n");
r1b_font_t font_zevv_peep_iso8859_1_08x16 = r1b_load_font_hex("fonts/tecate/16/zevv-peep-iso8859-1-08x16.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"zevv-peep-iso8859-1-08x16: Sphinx of black quartz, judge my vow! 0.123456789",2,2187,&font_zevv_peep_iso8859_1_08x16,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_zevv_peep_iso8859_1_08x16);

printf("testing t0-16i...\n");
r1b_font_t font_t0_16i = r1b_load_font_hex("fonts/tecate/16/t0-16i.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-16i: Sphinx of black quartz, judge my vow! 0.123456789",2,2205,&font_t0_16i,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_16i);

printf("testing spleen-8x16...\n");
r1b_font_t font_spleen_8x16 = r1b_load_font_hex("fonts/tecate/16/spleen-8x16.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"spleen-8x16: Sphinx of black quartz, judge my vow! 0.123456789",2,2223,&font_spleen_8x16,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_spleen_8x16);

printf("testing ter-u16v...\n");
r1b_font_t font_ter_u16v = r1b_load_font_hex("fonts/tecate/16/ter-u16v.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u16v: Sphinx of black quartz, judge my vow! 0.123456789",2,2241,&font_ter_u16v,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u16v);

printf("testing ter-u16b...\n");
r1b_font_t font_ter_u16b = r1b_load_font_hex("fonts/tecate/16/ter-u16b.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u16b: Sphinx of black quartz, judge my vow! 0.123456789",2,2259,&font_ter_u16b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u16b);

printf("testing t0-16b...\n");
r1b_font_t font_t0_16b = r1b_load_font_hex("fonts/tecate/16/t0-16b.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-16b: Sphinx of black quartz, judge my vow! 0.123456789",2,2277,&font_t0_16b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_16b);

printf("testing ter-u16n...\n");
r1b_font_t font_ter_u16n = r1b_load_font_hex("fonts/tecate/16/ter-u16n.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u16n: Sphinx of black quartz, judge my vow! 0.123456789",2,2295,&font_ter_u16n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u16n);

printf("testing t0-16...\n");
r1b_font_t font_t0_16 = r1b_load_font_hex("fonts/tecate/16/t0-16.hex",16,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-16: Sphinx of black quartz, judge my vow! 0.123456789",2,2313,&font_t0_16,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_16);

printf("testing envypn7x15...\n");
r1b_font_t font_envypn7x15 = r1b_load_font_hex("fonts/tecate/15/envypn7x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"envypn7x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2331,&font_envypn7x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_envypn7x15);

printf("testing neep-post-ampersand-08x15-bold...\n");
r1b_font_t font_neep_post_ampersand_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-post-ampersand-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-post-ampersand-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2348,&font_neep_post_ampersand_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_post_ampersand_08x15_bold);

printf("testing neep-iso8859-2-08x15...\n");
r1b_font_t font_neep_iso8859_2_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-2-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2365,&font_neep_iso8859_2_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_08x15);

printf("testing neep-pre-ampersand-08x15-bold...\n");
r1b_font_t font_neep_pre_ampersand_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-pre-ampersand-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-pre-ampersand-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2382,&font_neep_pre_ampersand_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_pre_ampersand_08x15_bold);

printf("testing neep-alt-iso8859-2-08x15...\n");
r1b_font_t font_neep_alt_iso8859_2_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-2-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-2-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2399,&font_neep_alt_iso8859_2_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_2_08x15);

printf("testing neep-iso8859-2-part-08x15-bold...\n");
r1b_font_t font_neep_iso8859_2_part_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-2-part-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-part-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2416,&font_neep_iso8859_2_part_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_part_08x15_bold);

printf("testing neep-alt-iso8859-9-08x15...\n");
r1b_font_t font_neep_alt_iso8859_9_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-9-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-9-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2433,&font_neep_alt_iso8859_9_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_9_08x15);

printf("testing neep-iso8859-15-part-08x15...\n");
r1b_font_t font_neep_iso8859_15_part_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-15-part-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-part-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2450,&font_neep_iso8859_15_part_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_part_08x15);

printf("testing neep-iso8859-9-08x15...\n");
r1b_font_t font_neep_iso8859_9_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-9-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2467,&font_neep_iso8859_9_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_08x15);

printf("testing neep-iso8859-9-08x15-bold...\n");
r1b_font_t font_neep_iso8859_9_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-9-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2484,&font_neep_iso8859_9_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_08x15_bold);

printf("testing neep-alt-iso8859-15-08x15-bold...\n");
r1b_font_t font_neep_alt_iso8859_15_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-15-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-15-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2501,&font_neep_alt_iso8859_15_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_15_08x15_bold);

printf("testing neep-iso8859-1-part-08x15-bold...\n");
r1b_font_t font_neep_iso8859_1_part_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-1-part-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-part-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2518,&font_neep_iso8859_1_part_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_part_08x15_bold);

printf("testing neep-iso8859-1-08x15-bold...\n");
r1b_font_t font_neep_iso8859_1_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-1-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2535,&font_neep_iso8859_1_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_08x15_bold);

printf("testing TamzenForPowerline8x15r...\n");
r1b_font_t font_TamzenForPowerline8x15r = r1b_load_font_hex("fonts/tecate/15/TamzenForPowerline8x15r.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline8x15r: Sphinx of black quartz, judge my vow! 0.123456789",2,2552,&font_TamzenForPowerline8x15r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline8x15r);

printf("testing neep-iso8859-9-part-08x15-bold...\n");
r1b_font_t font_neep_iso8859_9_part_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-9-part-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-part-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2569,&font_neep_iso8859_9_part_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_part_08x15_bold);

printf("testing neep-alt-iso8859-15-08x15...\n");
r1b_font_t font_neep_alt_iso8859_15_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-15-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-15-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2586,&font_neep_alt_iso8859_15_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_15_08x15);

printf("testing neep-iso8859-2-08x15-bold...\n");
r1b_font_t font_neep_iso8859_2_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-2-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2603,&font_neep_iso8859_2_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_08x15_bold);

printf("testing TamzenForPowerline8x15b...\n");
r1b_font_t font_TamzenForPowerline8x15b = r1b_load_font_hex("fonts/tecate/15/TamzenForPowerline8x15b.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline8x15b: Sphinx of black quartz, judge my vow! 0.123456789",2,2620,&font_TamzenForPowerline8x15b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline8x15b);

printf("testing t0-15b...\n");
r1b_font_t font_t0_15b = r1b_load_font_hex("fonts/tecate/15/t0-15b.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-15b: Sphinx of black quartz, judge my vow! 0.123456789",2,2637,&font_t0_15b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_15b);

printf("testing Tamzen8x15b...\n");
r1b_font_t font_Tamzen8x15b = r1b_load_font_hex("fonts/tecate/15/Tamzen8x15b.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen8x15b: Sphinx of black quartz, judge my vow! 0.123456789",2,2654,&font_Tamzen8x15b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen8x15b);

printf("testing neep-iso8859-2-part-08x15...\n");
r1b_font_t font_neep_iso8859_2_part_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-2-part-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-2-part-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2671,&font_neep_iso8859_2_part_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_2_part_08x15);

printf("testing neep-post-ampersand-08x15...\n");
r1b_font_t font_neep_post_ampersand_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-post-ampersand-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-post-ampersand-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2688,&font_neep_post_ampersand_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_post_ampersand_08x15);

printf("testing neep-iso8859-15-08x15...\n");
r1b_font_t font_neep_iso8859_15_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-15-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2705,&font_neep_iso8859_15_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_08x15);

printf("testing t0-15i...\n");
r1b_font_t font_t0_15i = r1b_load_font_hex("fonts/tecate/15/t0-15i.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-15i: Sphinx of black quartz, judge my vow! 0.123456789",2,2722,&font_t0_15i,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_15i);

printf("testing Tamzen8x15r...\n");
r1b_font_t font_Tamzen8x15r = r1b_load_font_hex("fonts/tecate/15/Tamzen8x15r.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen8x15r: Sphinx of black quartz, judge my vow! 0.123456789",2,2739,&font_Tamzen8x15r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen8x15r);

printf("testing neep-alt-iso8859-9-08x15-bold...\n");
r1b_font_t font_neep_alt_iso8859_9_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-9-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-9-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2756,&font_neep_alt_iso8859_9_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_9_08x15_bold);

printf("testing neep-alt-iso8859-1-08x15-bold...\n");
r1b_font_t font_neep_alt_iso8859_1_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-1-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-1-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2773,&font_neep_alt_iso8859_1_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_1_08x15_bold);

printf("testing neep-iso8859-15-08x15-bold...\n");
r1b_font_t font_neep_iso8859_15_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-15-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2790,&font_neep_iso8859_15_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_08x15_bold);

printf("testing neep-iso8859-9-part-08x15...\n");
r1b_font_t font_neep_iso8859_9_part_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-9-part-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-9-part-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2807,&font_neep_iso8859_9_part_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_9_part_08x15);

printf("testing neep-iso8859-1-08x15...\n");
r1b_font_t font_neep_iso8859_1_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-1-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2824,&font_neep_iso8859_1_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_08x15);

printf("testing neep-iso8859-1-part-08x15...\n");
r1b_font_t font_neep_iso8859_1_part_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-1-part-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-1-part-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2841,&font_neep_iso8859_1_part_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_1_part_08x15);

printf("testing neep-alt-iso8859-1-08x15...\n");
r1b_font_t font_neep_alt_iso8859_1_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-1-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-1-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2858,&font_neep_alt_iso8859_1_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_1_08x15);

printf("testing neep-iso8859-15-part-08x15-bold...\n");
r1b_font_t font_neep_iso8859_15_part_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-iso8859-15-part-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-iso8859-15-part-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2875,&font_neep_iso8859_15_part_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_iso8859_15_part_08x15_bold);

printf("testing neep-alt-iso8859-2-08x15-bold...\n");
r1b_font_t font_neep_alt_iso8859_2_08x15_bold = r1b_load_font_hex("fonts/tecate/15/neep-alt-iso8859-2-08x15-bold.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-alt-iso8859-2-08x15-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,2892,&font_neep_alt_iso8859_2_08x15_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_alt_iso8859_2_08x15_bold);

printf("testing neep-pre-ampersand-08x15...\n");
r1b_font_t font_neep_pre_ampersand_08x15 = r1b_load_font_hex("fonts/tecate/15/neep-pre-ampersand-08x15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"neep-pre-ampersand-08x15: Sphinx of black quartz, judge my vow! 0.123456789",2,2909,&font_neep_pre_ampersand_08x15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_neep_pre_ampersand_08x15);

printf("testing t0-15...\n");
r1b_font_t font_t0_15 = r1b_load_font_hex("fonts/tecate/15/t0-15.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-15: Sphinx of black quartz, judge my vow! 0.123456789",2,2926,&font_t0_15,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_15);

printf("testing envypn7x15e...\n");
r1b_font_t font_envypn7x15e = r1b_load_font_hex("fonts/tecate/15/envypn7x15e.hex",15,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"envypn7x15e: Sphinx of black quartz, judge my vow! 0.123456789",2,2943,&font_envypn7x15e,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_envypn7x15e);

printf("testing Tamzen7x14b...\n");
r1b_font_t font_Tamzen7x14b = r1b_load_font_hex("fonts/tecate/14/Tamzen7x14b.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen7x14b: Sphinx of black quartz, judge my vow! 0.123456789",2,2960,&font_Tamzen7x14b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen7x14b);

printf("testing gohufont-uni-14...\n");
r1b_font_t font_gohufont_uni_14 = r1b_load_font_hex("fonts/tecate/14/gohufont-uni-14.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"gohufont-uni-14: Sphinx of black quartz, judge my vow! 0.123456789",2,2976,&font_gohufont_uni_14,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_gohufont_uni_14);

printf("testing gohufont-14...\n");
r1b_font_t font_gohufont_14 = r1b_load_font_hex("fonts/tecate/14/gohufont-14.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"gohufont-14: Sphinx of black quartz, judge my vow! 0.123456789",2,2992,&font_gohufont_14,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_gohufont_14);

printf("testing Tamzen7x14r...\n");
r1b_font_t font_Tamzen7x14r = r1b_load_font_hex("fonts/tecate/14/Tamzen7x14r.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen7x14r: Sphinx of black quartz, judge my vow! 0.123456789",2,3008,&font_Tamzen7x14r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen7x14r);

printf("testing gohufont-14b...\n");
r1b_font_t font_gohufont_14b = r1b_load_font_hex("fonts/tecate/14/gohufont-14b.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"gohufont-14b: Sphinx of black quartz, judge my vow! 0.123456789",2,3024,&font_gohufont_14b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_gohufont_14b);

printf("testing ter-u14n...\n");
r1b_font_t font_ter_u14n = r1b_load_font_hex("fonts/tecate/14/ter-u14n.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u14n: Sphinx of black quartz, judge my vow! 0.123456789",2,3040,&font_ter_u14n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u14n);

printf("testing t0-14b...\n");
r1b_font_t font_t0_14b = r1b_load_font_hex("fonts/tecate/14/t0-14b.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-14b: Sphinx of black quartz, judge my vow! 0.123456789",2,3056,&font_t0_14b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_14b);

printf("testing 14x14...\n");
r1b_font_t font_14x14 = r1b_load_font_hex("fonts/tecate/14/14x14.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"14x14: Sphinx of black quartz, judge my vow! 0.123456789",2,3072,&font_14x14,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_14x14);

printf("testing 14x14O...\n");
r1b_font_t font_14x14O = r1b_load_font_hex("fonts/tecate/14/14x14O.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"14x14O: Sphinx of black quartz, judge my vow! 0.123456789",2,3088,&font_14x14O,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_14x14O);

printf("testing boxxy-bold...\n");
r1b_font_t font_boxxy_bold = r1b_load_font_hex("fonts/tecate/14/boxxy-bold.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"boxxy-bold: Sphinx of black quartz, judge my vow! 0.123456789",2,3104,&font_boxxy_bold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_boxxy_bold);

printf("testing boxxy...\n");
r1b_font_t font_boxxy = r1b_load_font_hex("fonts/tecate/14/boxxy.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"boxxy: Sphinx of black quartz, judge my vow! 0.123456789",2,3120,&font_boxxy,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_boxxy);

printf("testing zevv-peep-iso8859-1-07x14...\n");
r1b_font_t font_zevv_peep_iso8859_1_07x14 = r1b_load_font_hex("fonts/tecate/14/zevv-peep-iso8859-1-07x14.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"zevv-peep-iso8859-1-07x14: Sphinx of black quartz, judge my vow! 0.123456789",2,3136,&font_zevv_peep_iso8859_1_07x14,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_zevv_peep_iso8859_1_07x14);

printf("testing ter-u14v...\n");
r1b_font_t font_ter_u14v = r1b_load_font_hex("fonts/tecate/14/ter-u14v.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u14v: Sphinx of black quartz, judge my vow! 0.123456789",2,3152,&font_ter_u14v,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u14v);

printf("testing 14x14B...\n");
r1b_font_t font_14x14B = r1b_load_font_hex("fonts/tecate/14/14x14B.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"14x14B: Sphinx of black quartz, judge my vow! 0.123456789",2,3168,&font_14x14B,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_14x14B);

printf("testing ter-u14b...\n");
r1b_font_t font_ter_u14b = r1b_load_font_hex("fonts/tecate/14/ter-u14b.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u14b: Sphinx of black quartz, judge my vow! 0.123456789",2,3184,&font_ter_u14b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u14b);

printf("testing zevv-peep-iso8859-15-07x14...\n");
r1b_font_t font_zevv_peep_iso8859_15_07x14 = r1b_load_font_hex("fonts/tecate/14/zevv-peep-iso8859-15-07x14.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"zevv-peep-iso8859-15-07x14: Sphinx of black quartz, judge my vow! 0.123456789",2,3200,&font_zevv_peep_iso8859_15_07x14,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_zevv_peep_iso8859_15_07x14);

printf("testing 14x14BO...\n");
r1b_font_t font_14x14BO = r1b_load_font_hex("fonts/tecate/14/14x14BO.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"14x14BO: Sphinx of black quartz, judge my vow! 0.123456789",2,3216,&font_14x14BO,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_14x14BO);

printf("testing TamzenForPowerline7x14r...\n");
r1b_font_t font_TamzenForPowerline7x14r = r1b_load_font_hex("fonts/tecate/14/TamzenForPowerline7x14r.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline7x14r: Sphinx of black quartz, judge my vow! 0.123456789",2,3232,&font_TamzenForPowerline7x14r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline7x14r);

printf("testing gohufont-uni-14b...\n");
r1b_font_t font_gohufont_uni_14b = r1b_load_font_hex("fonts/tecate/14/gohufont-uni-14b.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"gohufont-uni-14b: Sphinx of black quartz, judge my vow! 0.123456789",2,3248,&font_gohufont_uni_14b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_gohufont_uni_14b);

printf("testing t0-14...\n");
r1b_font_t font_t0_14 = r1b_load_font_hex("fonts/tecate/14/t0-14.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-14: Sphinx of black quartz, judge my vow! 0.123456789",2,3264,&font_t0_14,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_14);

printf("testing TamzenForPowerline7x14b...\n");
r1b_font_t font_TamzenForPowerline7x14b = r1b_load_font_hex("fonts/tecate/14/TamzenForPowerline7x14b.hex",14,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline7x14b: Sphinx of black quartz, judge my vow! 0.123456789",2,3280,&font_TamzenForPowerline7x14b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline7x14b);

printf("testing ctrld-fixed-13b-i...\n");
r1b_font_t font_ctrld_fixed_13b_i = r1b_load_font_hex("fonts/tecate/13/ctrld-fixed-13b-i.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ctrld-fixed-13b-i: Sphinx of black quartz, judge my vow! 0.123456789",2,3296,&font_ctrld_fixed_13b_i,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ctrld_fixed_13b_i);

printf("testing envypn7x13...\n");
r1b_font_t font_envypn7x13 = r1b_load_font_hex("fonts/tecate/13/envypn7x13.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"envypn7x13: Sphinx of black quartz, judge my vow! 0.123456789",2,3311,&font_envypn7x13,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_envypn7x13);

printf("testing bitocra-13-full...\n");
r1b_font_t font_bitocra_13_full = r1b_load_font_hex("fonts/tecate/13/bitocra-13-full.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"bitocra-13-full: Sphinx of black quartz, judge my vow! 0.123456789",2,3326,&font_bitocra_13_full,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_bitocra_13_full);

printf("testing 7x13...\n");
r1b_font_t font_7x13 = r1b_load_font_hex("fonts/tecate/13/7x13.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"7x13: Sphinx of black quartz, judge my vow! 0.123456789",2,3341,&font_7x13,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_7x13);

printf("testing t0-13b...\n");
r1b_font_t font_t0_13b = r1b_load_font_hex("fonts/tecate/13/t0-13b.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-13b: Sphinx of black quartz, judge my vow! 0.123456789",2,3356,&font_t0_13b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_13b);

printf("testing 7x13O...\n");
r1b_font_t font_7x13O = r1b_load_font_hex("fonts/tecate/13/7x13O.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"7x13O: Sphinx of black quartz, judge my vow! 0.123456789",2,3371,&font_7x13O,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_7x13O);

printf("testing Tamzen7x13r...\n");
r1b_font_t font_Tamzen7x13r = r1b_load_font_hex("fonts/tecate/13/Tamzen7x13r.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen7x13r: Sphinx of black quartz, judge my vow! 0.123456789",2,3386,&font_Tamzen7x13r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen7x13r);

printf("testing Tamzen7x13b...\n");
r1b_font_t font_Tamzen7x13b = r1b_load_font_hex("fonts/tecate/13/Tamzen7x13b.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen7x13b: Sphinx of black quartz, judge my vow! 0.123456789",2,3401,&font_Tamzen7x13b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen7x13b);

printf("testing mplus_f12b...\n");
r1b_font_t font_mplus_f12b = r1b_load_font_hex("fonts/tecate/13/mplus_f12b.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"mplus_f12b: Sphinx of black quartz, judge my vow! 0.123456789",2,3416,&font_mplus_f12b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_mplus_f12b);

printf("testing ctrld-fixed-13b...\n");
r1b_font_t font_ctrld_fixed_13b = r1b_load_font_hex("fonts/tecate/13/ctrld-fixed-13b.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ctrld-fixed-13b: Sphinx of black quartz, judge my vow! 0.123456789",2,3431,&font_ctrld_fixed_13b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ctrld_fixed_13b);

printf("testing TamzenForPowerline7x13b...\n");
r1b_font_t font_TamzenForPowerline7x13b = r1b_load_font_hex("fonts/tecate/13/TamzenForPowerline7x13b.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline7x13b: Sphinx of black quartz, judge my vow! 0.123456789",2,3446,&font_TamzenForPowerline7x13b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline7x13b);

printf("testing ctrld-fixed-13r-i...\n");
r1b_font_t font_ctrld_fixed_13r_i = r1b_load_font_hex("fonts/tecate/13/ctrld-fixed-13r-i.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ctrld-fixed-13r-i: Sphinx of black quartz, judge my vow! 0.123456789",2,3461,&font_ctrld_fixed_13r_i,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ctrld_fixed_13r_i);

printf("testing ctrld-fixed-13r...\n");
r1b_font_t font_ctrld_fixed_13r = r1b_load_font_hex("fonts/tecate/13/ctrld-fixed-13r.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ctrld-fixed-13r: Sphinx of black quartz, judge my vow! 0.123456789",2,3476,&font_ctrld_fixed_13r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ctrld_fixed_13r);

printf("testing bitocra-13...\n");
r1b_font_t font_bitocra_13 = r1b_load_font_hex("fonts/tecate/13/bitocra-13.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"bitocra-13: Sphinx of black quartz, judge my vow! 0.123456789",2,3491,&font_bitocra_13,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_bitocra_13);

printf("testing mplus_f12r...\n");
r1b_font_t font_mplus_f12r = r1b_load_font_hex("fonts/tecate/13/mplus_f12r.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"mplus_f12r: Sphinx of black quartz, judge my vow! 0.123456789",2,3506,&font_mplus_f12r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_mplus_f12r);

printf("testing envypn7x13e...\n");
r1b_font_t font_envypn7x13e = r1b_load_font_hex("fonts/tecate/13/envypn7x13e.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"envypn7x13e: Sphinx of black quartz, judge my vow! 0.123456789",2,3521,&font_envypn7x13e,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_envypn7x13e);

printf("testing 7x13BO...\n");
r1b_font_t font_7x13BO = r1b_load_font_hex("fonts/tecate/13/7x13BO.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"7x13BO: Sphinx of black quartz, judge my vow! 0.123456789",2,3536,&font_7x13BO,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_7x13BO);

printf("testing TamzenForPowerline7x13r...\n");
r1b_font_t font_TamzenForPowerline7x13r = r1b_load_font_hex("fonts/tecate/13/TamzenForPowerline7x13r.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline7x13r: Sphinx of black quartz, judge my vow! 0.123456789",2,3551,&font_TamzenForPowerline7x13r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline7x13r);

printf("testing 7x13B...\n");
r1b_font_t font_7x13B = r1b_load_font_hex("fonts/tecate/13/7x13B.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"7x13B: Sphinx of black quartz, judge my vow! 0.123456789",2,3566,&font_7x13B,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_7x13B);

printf("testing t0-13...\n");
r1b_font_t font_t0_13 = r1b_load_font_hex("fonts/tecate/13/t0-13.hex",13,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-13: Sphinx of black quartz, judge my vow! 0.123456789",2,3581,&font_t0_13,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_13);

printf("testing ter-u12n...\n");
r1b_font_t font_ter_u12n = r1b_load_font_hex("fonts/tecate/12/ter-u12n.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u12n: Sphinx of black quartz, judge my vow! 0.123456789",2,3596,&font_ter_u12n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u12n);

printf("testing t0-12b...\n");
r1b_font_t font_t0_12b = r1b_load_font_hex("fonts/tecate/12/t0-12b.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-12b: Sphinx of black quartz, judge my vow! 0.123456789",2,3610,&font_t0_12b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_12b);

printf("testing kakwafont-12-b...\n");
r1b_font_t font_kakwafont_12_b = r1b_load_font_hex("fonts/tecate/12/kakwafont-12-b.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"kakwafont-12-b: Sphinx of black quartz, judge my vow! 0.123456789",2,3624,&font_kakwafont_12_b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_kakwafont_12_b);

printf("testing Tamzen6x12r...\n");
r1b_font_t font_Tamzen6x12r = r1b_load_font_hex("fonts/tecate/12/Tamzen6x12r.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen6x12r: Sphinx of black quartz, judge my vow! 0.123456789",2,3638,&font_Tamzen6x12r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen6x12r);

printf("testing Tamzen6x12b...\n");
r1b_font_t font_Tamzen6x12b = r1b_load_font_hex("fonts/tecate/12/Tamzen6x12b.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen6x12b: Sphinx of black quartz, judge my vow! 0.123456789",2,3652,&font_Tamzen6x12b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen6x12b);

printf("testing TamzenForPowerline6x12b...\n");
r1b_font_t font_TamzenForPowerline6x12b = r1b_load_font_hex("fonts/tecate/12/TamzenForPowerline6x12b.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline6x12b: Sphinx of black quartz, judge my vow! 0.123456789",2,3666,&font_TamzenForPowerline6x12b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline6x12b);

printf("testing TamzenForPowerline6x12r...\n");
r1b_font_t font_TamzenForPowerline6x12r = r1b_load_font_hex("fonts/tecate/12/TamzenForPowerline6x12r.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline6x12r: Sphinx of black quartz, judge my vow! 0.123456789",2,3680,&font_TamzenForPowerline6x12r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline6x12r);

printf("testing kakwafont-12-n...\n");
r1b_font_t font_kakwafont_12_n = r1b_load_font_hex("fonts/tecate/12/kakwafont-12-n.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"kakwafont-12-n: Sphinx of black quartz, judge my vow! 0.123456789",2,3694,&font_kakwafont_12_n,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_kakwafont_12_n);

printf("testing t0-12...\n");
r1b_font_t font_t0_12 = r1b_load_font_hex("fonts/tecate/12/t0-12.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-12: Sphinx of black quartz, judge my vow! 0.123456789",2,3708,&font_t0_12,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_12);

printf("testing ter-u12b...\n");
r1b_font_t font_ter_u12b = r1b_load_font_hex("fonts/tecate/12/ter-u12b.hex",12,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ter-u12b: Sphinx of black quartz, judge my vow! 0.123456789",2,3722,&font_ter_u12b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ter_u12b);

printf("testing MonteCarloMedium...\n");
r1b_font_t font_MonteCarloMedium = r1b_load_font_hex("fonts/tecate/11/MonteCarloMedium.hex",11,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"MonteCarloMedium: Sphinx of black quartz, judge my vow! 0.123456789",2,3736,&font_MonteCarloMedium,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_MonteCarloMedium);

printf("testing HaxorMedium-10...\n");
r1b_font_t font_HaxorMedium_10 = r1b_load_font_hex("fonts/tecate/11/HaxorMedium-10.hex",11,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"HaxorMedium-10: Sphinx of black quartz, judge my vow! 0.123456789",2,3749,&font_HaxorMedium_10,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_HaxorMedium_10);

printf("testing t0-11...\n");
r1b_font_t font_t0_11 = r1b_load_font_hex("fonts/tecate/11/t0-11.hex",11,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-11: Sphinx of black quartz, judge my vow! 0.123456789",2,3762,&font_t0_11,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_11);

printf("testing t0-11b...\n");
r1b_font_t font_t0_11b = r1b_load_font_hex("fonts/tecate/11/t0-11b.hex",11,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"t0-11b: Sphinx of black quartz, judge my vow! 0.123456789",2,3775,&font_t0_11b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_t0_11b);

printf("testing MonteCarloBold...\n");
r1b_font_t font_MonteCarloBold = r1b_load_font_hex("fonts/tecate/11/MonteCarloBold.hex",11,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"MonteCarloBold: Sphinx of black quartz, judge my vow! 0.123456789",2,3788,&font_MonteCarloBold,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_MonteCarloBold);

printf("testing 6x10B...\n");
r1b_font_t font_6x10B = r1b_load_font_hex("fonts/tecate/10/6x10B.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"6x10B: Sphinx of black quartz, judge my vow! 0.123456789",2,3801,&font_6x10B,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_6x10B);

printf("testing bitbuntu-full...\n");
r1b_font_t font_bitbuntu_full = r1b_load_font_hex("fonts/tecate/10/bitbuntu-full.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"bitbuntu-full: Sphinx of black quartz, judge my vow! 0.123456789",2,3813,&font_bitbuntu_full,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_bitbuntu_full);

printf("testing ctrld-fixed-10r...\n");
r1b_font_t font_ctrld_fixed_10r = r1b_load_font_hex("fonts/tecate/10/ctrld-fixed-10r.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ctrld-fixed-10r: Sphinx of black quartz, judge my vow! 0.123456789",2,3825,&font_ctrld_fixed_10r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ctrld_fixed_10r);

printf("testing ctrld-fixed-10b...\n");
r1b_font_t font_ctrld_fixed_10b = r1b_load_font_hex("fonts/tecate/10/ctrld-fixed-10b.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"ctrld-fixed-10b: Sphinx of black quartz, judge my vow! 0.123456789",2,3837,&font_ctrld_fixed_10b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_ctrld_fixed_10b);

printf("testing cherry-10-r...\n");
r1b_font_t font_cherry_10_r = r1b_load_font_hex("fonts/tecate/10/cherry-10-r.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"cherry-10-r: Sphinx of black quartz, judge my vow! 0.123456789",2,3849,&font_cherry_10_r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_cherry_10_r);

printf("testing 6x10...\n");
r1b_font_t font_6x10 = r1b_load_font_hex("fonts/tecate/10/6x10.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"6x10: Sphinx of black quartz, judge my vow! 0.123456789",2,3861,&font_6x10,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_6x10);

printf("testing cherry-10-b...\n");
r1b_font_t font_cherry_10_b = r1b_load_font_hex("fonts/tecate/10/cherry-10-b.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"cherry-10-b: Sphinx of black quartz, judge my vow! 0.123456789",2,3873,&font_cherry_10_b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_cherry_10_b);

printf("testing 6x10BO...\n");
r1b_font_t font_6x10BO = r1b_load_font_hex("fonts/tecate/10/6x10BO.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"6x10BO: Sphinx of black quartz, judge my vow! 0.123456789",2,3885,&font_6x10BO,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_6x10BO);

printf("testing 6x10O...\n");
r1b_font_t font_6x10O = r1b_load_font_hex("fonts/tecate/10/6x10O.hex",10,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"6x10O: Sphinx of black quartz, judge my vow! 0.123456789",2,3897,&font_6x10O,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_6x10O);

printf("testing TamzenForPowerline5x9r...\n");
r1b_font_t font_TamzenForPowerline5x9r = r1b_load_font_hex("fonts/tecate/9/TamzenForPowerline5x9r.hex",9,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline5x9r: Sphinx of black quartz, judge my vow! 0.123456789",2,3909,&font_TamzenForPowerline5x9r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline5x9r);

printf("testing Tamzen5x9b...\n");
r1b_font_t font_Tamzen5x9b = r1b_load_font_hex("fonts/tecate/9/Tamzen5x9b.hex",9,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen5x9b: Sphinx of black quartz, judge my vow! 0.123456789",2,3920,&font_Tamzen5x9b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen5x9b);

printf("testing TamzenForPowerline5x9b...\n");
r1b_font_t font_TamzenForPowerline5x9b = r1b_load_font_hex("fonts/tecate/9/TamzenForPowerline5x9b.hex",9,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"TamzenForPowerline5x9b: Sphinx of black quartz, judge my vow! 0.123456789",2,3931,&font_TamzenForPowerline5x9b,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_TamzenForPowerline5x9b);

printf("testing Tamzen5x9r...\n");
r1b_font_t font_Tamzen5x9r = r1b_load_font_hex("fonts/tecate/9/Tamzen5x9r.hex",9,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"Tamzen5x9r: Sphinx of black quartz, judge my vow! 0.123456789",2,3942,&font_Tamzen5x9r,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_Tamzen5x9r);

printf("testing spleen-5x8...\n");
r1b_font_t font_spleen_5x8 = r1b_load_font_hex("fonts/tecate/8/spleen-5x8.hex",8,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"spleen-5x8: Sphinx of black quartz, judge my vow! 0.123456789",2,3953,&font_spleen_5x8,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_spleen_5x8);

printf("testing bitocra7...\n");
r1b_font_t font_bitocra7 = r1b_load_font_hex("fonts/tecate/7/bitocra7.hex",7,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"bitocra7: Sphinx of black quartz, judge my vow! 0.123456789",2,3963,&font_bitocra7,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_bitocra7);

printf("testing 5thElement...\n");
r1b_font_t font_5thElement = r1b_load_font_hex("fonts/tecate/5/5thElement.hex",5,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"5thElement: Sphinx of black quartz, judge my vow! 0.123456789",2,3972,&font_5thElement,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_5thElement);

printf("testing 4thD...\n");
r1b_font_t font_4thD = r1b_load_font_hex("fonts/tecate/4/4thD.hex",4,0,INT_MAX,R1B_FLAG_SORTED);
r1b_text(&im, L"4thD: Sphinx of black quartz, judge my vow! 0.123456789",2,3979,&font_4thD,1,R1B_BLIT_SET,0);
r1b_destroy_font(&font_4thD);

  r1b_snapshot("examples/out/fonts.png",&im);

  r1b_lpr("Printer_USB_Thermal_Printer",&im);

  r1b_free(&im);
  r1b_cleanup();
}
