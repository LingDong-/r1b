

typedef struct _lsys_char_t {
  char c;
  struct _lsys_char_t* prev;
  struct _lsys_char_t* next;
} lsys_char_t;

typedef struct{
  lsys_char_t* head;
  lsys_char_t* tail;
} lsys_str_t;

typedef struct{
  char  lhs;
  char* rhs;
} lsys_rule_t;

lsys_str_t* lsys_make_str(char* s) {
  lsys_str_t* ss = (lsys_str_t*)malloc(sizeof(lsys_str_t));
  ss->head = NULL;
  ss->tail = NULL;
  int sl = strlen(s);
  for (int i = 0; i < sl; i++){
    lsys_char_t* cc = (lsys_char_t*) malloc(sizeof(lsys_char_t));
    cc->c = s[i];
    cc->prev = ss->tail;
    cc->next = NULL;
    if (ss->tail == NULL){
      ss->head = cc;
    }else{
      ss->tail->next = cc;
    }
    ss->tail = cc;
  }
  return ss;
}

void lsys_print_str(lsys_str_t* state){
  lsys_char_t* it = state->head;
  while (it != NULL) {
    lsys_char_t*jt = it->next;
    printf("%c",it->c);
    it = jt;
  }
  printf("\n");
}

void lsys_destroy_str(lsys_str_t* state){
  lsys_char_t* it = state->head;
  while (it != NULL) {
    lsys_char_t*jt = it->next;
    free(it);
    it = jt;
  }
  free(state);
}

void lsys_step(lsys_str_t* state, lsys_rule_t* rules, int n_rules){
  lsys_char_t* it = state->head;
  while (it != NULL){
    lsys_char_t* jt = it->next;
    for (int i = 0; i < n_rules; i++ ){
      if (it->c == rules[i].lhs) {
        lsys_str_t* ss = lsys_make_str(rules[i].rhs);

        if (it->prev != NULL){
          it->prev->next = ss->head;
        }else{
          state->head = ss->head;
        }
        if (it->next != NULL){
          it->next->prev = ss->tail;
        }else{
          state->tail = ss->tail;
        }
        ss->head->prev = it->prev;
        ss->tail->next = it->next;
        free(it);
      }
    }
    it = jt;
  }
}