//gcc examples/plants.c
#include "../r1b.h"
#include "utils/lsys.h"
#include "utils/turtle.h"


void draw_lsys(turtle_t* tur, lsys_str_t* state, float d, float ang){
  turtle_pendown(tur);
  lsys_char_t* it = state->head;
  while (it) {
    switch (it->c) {
      case 'X':break;
      case 'F':
        turtle_forward(tur,d);
        break;
      case '+':
        turtle_turn(tur,ang);
        break;
      case '-':
        turtle_turn(tur,-ang);
        break;
      case '[':
        turtle_push(tur);
        break;
      case ']':
        turtle_pop(tur);
        break;
      default:
        break;
    }
    it = it->next;
  }
  turtle_penup(tur);
}


void branch(r1b_im_t* im, float x, float y){
  lsys_str_t* state = lsys_make_str("X");
  lsys_rule_t rules[2];
  rules[0].lhs = 'X'; rules[0].rhs = "F+[[X]-X]-F[-FX]+X";
  rules[1].lhs = 'F'; rules[1].rhs = "FF";

  for (int i=0; i < 6; i++){
    lsys_step(state,rules,2);
  }
  turtle_t tur = turtle_init(im);
  turtle_goto(&tur,x,y);
  turtle_turn(&tur,-1.15);
  draw_lsys(&tur,state,4,0.4);
  lsys_destroy_str(state);
  turtle_destroy(&tur);
}

void weed(r1b_im_t* im, float x, float y){
  lsys_str_t* state = lsys_make_str("F");
  lsys_rule_t rules[3];
  rules[0].lhs = 'X'; rules[0].rhs = "+FY";
  rules[1].lhs = 'Y'; rules[1].rhs = "-FX";
  rules[2].lhs = 'F'; rules[2].rhs = "FF-[XY]+[XY]";

  for (int i=0; i < 6; i++){
    lsys_step(state,rules,3);
  }
  turtle_t tur = turtle_init(im);
  turtle_goto(&tur,x,y);
  turtle_turn(&tur,-1.57);
  draw_lsys(&tur,state,6,0.4);
  lsys_destroy_str(state);
  turtle_destroy(&tur);
}

void bush(r1b_im_t* im, float x, float y){
  lsys_str_t* state = lsys_make_str("F");
  lsys_rule_t rules[1];
  rules[0].lhs = 'F'; rules[0].rhs = "FF+[+F-F-F]-[-F+F+F]";

  for (int i=0; i < 4; i++){
    lsys_step(state,rules,1);
  }
  turtle_t tur = turtle_init(im);
  turtle_goto(&tur,x,y);
  turtle_turn(&tur,-1.57);
  draw_lsys(&tur,state,10,0.4);
  lsys_destroy_str(state);
  turtle_destroy(&tur);
}

int main(){

  r1b_im_t im = r1b_zeros(384, 768*3);

  bush(&im,125,768);
  r1b_text(&im, L"Bush", 20, 20, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 1);

  weed(&im,192,768*2);
  r1b_text(&im, L"Weed", 20, 768+20, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 1);

  branch(&im,40,768*3);
  r1b_text(&im, L"Branch", 20, 768*2+20, R1B_FONT_FG8X12, 1, R1B_BLIT_SET, 1);

  r1b_snapshot("examples/out/plants.png", &im);

  // r1b_lpr("Printer_USB_Thermal_Printer",&im);

  r1b_free(&im);
  r1b_cleanup();
}