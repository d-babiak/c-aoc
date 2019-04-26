#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "./void_vec.h"


VVec *VV_init() {
  VVec *v = malloc(sizeof(VVec));
  v->n = 0;
  v->n_max = 4;
  v->xs = malloc(v->n_max * sizeof(void *));
  memset(v->xs, '\0', v->n_max * sizeof(void *));
  return v;
}

void _VV_grow(VVec *v) {
  v->n_max *= 2;
  void **new_xs = malloc(v->n_max * sizeof(void*));
  memcpy(new_xs, v->xs, v->n * sizeof(void *));
  free(v->xs); // right...?
  v->xs = new_xs;
}

void _VV_shrink(VVec *v) {
  v->n_max /= 2;
  void **new_xs = malloc(v->n_max * sizeof(void*));
  memcpy(new_xs, v->xs, v->n * sizeof(void *));
  free(v->xs); // right...?
  v->xs = new_xs;
}

void VV_push(VVec *v, void *x) {
  assert(v->n < v->n_max);

  v->xs[v->n++] = x;

  if (v->n == v->n_max) 
    _VV_grow(v);
}

void *VV_pop(VVec *v) {
  assert(v->n > 0);
  void *x = v->xs[--(v->n)];

  if ( ((1.0 * v->n) / v->n_max) < 0.3 )
    _VV_shrink(v);

  return x;
}

void *VV_get(VVec *v, uint32_t i) {
  assert(0 <= i && i < v->n);
  return v->xs[i];
}

void VV_each(VVec *v, void(*f)(void*)) {
  for (int i = 0; i < v->n; i++)
    f(v->xs[i]);
}
