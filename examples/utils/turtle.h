
typedef struct {
  float x;
  float y;
  float a;
} turtle_state_t;

typedef struct {
  r1b_im_t* im;
  turtle_state_t* st;
  int n_st;
  int m_st;
  char pd;
} turtle_t;

turtle_t turtle_init(r1b_im_t* im){
  turtle_t t;
  t.im = im;
  t.st = (turtle_state_t*)calloc(1,sizeof(turtle_state_t));
  t.n_st = 1;
  t.m_st = 1;
  t.pd = 0;
  return t;
}

void turtle_goto(turtle_t* t, float x, float y){
  float x0 = t->st[t->n_st-1].x;
  float y0 = t->st[t->n_st-1].y;

  t->st[t->n_st-1].x = x;
  t->st[t->n_st-1].y = y;

  if (t->pd){
    r1b_line(t->im,x0,y0,t->st[t->n_st-1].x,t->st[t->n_st-1].y,1,R1B_BLIT_SET);
  }
}

void turtle_forward(turtle_t* t, float d){
  turtle_goto(t,t->st[t->n_st-1].x+cos(t->st[t->n_st-1].a)*d, 
                t->st[t->n_st-1].y+sin(t->st[t->n_st-1].a)*d);
}

void turtle_turn(turtle_t* t, float a){
  t->st[t->n_st-1].a += a;
}

void turtle_push(turtle_t* t){
  if (!(t->m_st > t->n_st)){
    t->m_st = t->n_st+10;
    t->st = realloc(t->st,(t->m_st)*sizeof(turtle_state_t));
  }
  t->n_st ++;
  memcpy(&(t->st[t->n_st-1]),&(t->st[t->n_st-2]),sizeof(turtle_state_t));
}

void turtle_pop(turtle_t* t){
  t->n_st --;
}

void turtle_pendown(turtle_t* t){
  t->pd = 1;
}
void turtle_penup(turtle_t* t){
  t->pd = 0;
}

void turtle_destroy(turtle_t* t){
  free(t->st);
}


