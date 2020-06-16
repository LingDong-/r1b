#include "../r1b.h"


wchar_t* read_file(char* path, int n){
    char* raw = (char*)malloc(sizeof(char)*n*2);
    FILE *fp;
    char c;
    int i = 0;
    fp = fopen(path,"r");
    while(1) {
       c = fgetc(fp);
       if( feof(fp) ) {
          break;
       }
       raw[i] = c;
       i++;
    }
    raw[i] = 0;
    fclose(fp);

    wchar_t* wstr = (wchar_t*)malloc(sizeof(wchar_t)*n);

    int len = i;

    void* next = (void*)raw;
    int e;
    i = 0;
    while((char*)next <= (char*)raw+len){
      next = r1b_utf8_decode(next, (uint32_t *)&wstr[i], &e);
      i++;
    }
    wstr[i] = 0;
    wstr[i+1] = 0;
    wstr[i+2] = 0;
    wstr[i+3] = 0;
    free(raw);
    return wstr;
}

int main(){
    r1b_font_t font = r1b_load_font_hex("fonts/unifont.hex",16,0,INT_MAX,R1B_FLAG_SORTED);


    wchar_t* txt = read_file("examples/assets/5000.txt",10000);

    r1b_im_t im = r1b_zeros(3976,384);

    r1b_line(&im,0.5,0.5,im.w-0.5,0.5,1,R1B_BLIT_SET);
    r1b_line(&im,im.w-0.5,0.5,im.w-0.5,im.h-0.5,1,R1B_BLIT_SET);
    r1b_line(&im,0.5,im.h-0.5,im.w-0.5,im.h-0.5,1,R1B_BLIT_SET);
    r1b_line(&im,0.5,0.5,0.5,im.h-0.5,1,R1B_BLIT_SET);
    
    int i = 0;
    int x = 3960;
    int y = 0;
    while(1){
        if (txt[i] == 0){
            break;
        }
        r1b_putchar(&im,(int)txt[i],x,y,&font,1,R1B_BLIT_SET,0);
        y += 16;
        if (y >= 384){
            y = 0;
            x -= 18;
            r1b_line(&im,x+16,0,x+16,384,1,R1B_BLIT_SET);
        }
        i++;
    }

    r1b_snapshot("examples/out/scroll.png",&im);

    r1b_transpose_flip(&im);
    r1b_lpr("Printer_USB_Thermal_Printer",&im);
}