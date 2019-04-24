#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./tree.h"

// https://doc.rust-lang.org/std/cmp/enum.Ordering.html
#define LESS   -1
#define EQUAL   0
#define GREATER 1

int sign(int x) {
  if (x  < 0) return -1;
  if (x == 0) return  0;
  if (x  > 0) return  1;
  assert(false);
}

Map *M_init(int k, int v) {
  Map *m = malloc(sizeof(Map));
  m->k = k;
  m->v = v;
  m->L = NULL;
  m->R = NULL;
  return m;
}

// *_*
void M_set(Map **m, int k, int v) {
  if (*m == NULL) {
    *m = M_init(k, v);
    return;
  }

  int cmp = sign((*m)->k - k); 

  switch (cmp) {
    case LESS:    M_set(&(*m)->L, k, v); break;
    case GREATER: M_set(&(*m)->R, k, v); break;
    case EQUAL:   (*m)->v = v;
  }
}

int *M_get(Map *m, int k) {
  if (m == NULL) {
    return NULL;
  }

  int cmp = sign(m->k - k); 

  switch (cmp) {
    case LESS:    return M_get(m->L, k);
    case GREATER: return M_get(m->R, k);
    case EQUAL:   return &(m->v);
    default: assert(false);
  }
}
