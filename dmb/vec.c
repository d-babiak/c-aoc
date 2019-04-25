#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./vec.h"

Vec *V_init() {
  Vec *v = malloc(sizeof(Vec));
  v->max = 2;
  v->n = 0;
  v->xs = malloc(v->max * sizeof(char *));
  return v;
}


void V_push(Vec *v, char *s) {
  assert(v->n < v->max);
  v->xs[v->n++] = strdup(s);

  if (v->n == v->max)
    _grow(v);
}

char *V_pop(Vec *v) {
  assert(v->n > 0);
  char *s = v->xs[--v->n];

  if (((1.0 * v->n) / v->max) < 0.3)
    _shrink(v);

  return s;
}

void _grow(Vec *v) {
  size_t new_max = 2 * v->max;
  printf("%zd -> %zd\n", v->max, new_max);
  char **new_xs = malloc(new_max * sizeof(char *));

  for (int i = 0; i < v->max; i++)
    new_xs[i] = v->xs[i];

  //free(v->xs);
  v->max = new_max;
  v->xs = new_xs;
}

void _shrink(Vec *v) {
  size_t new_max = v->max / 2;
  printf("%zd -> %zd\n", v->max, new_max);
  char **new_xs = malloc(new_max * sizeof(char *));

  for (int i = 0; i < v->max; i++)
    new_xs[i] = v->xs[i];

  /*
  free(v->xs);
vec_test(20763,0x10772a5c0) malloc: Incorrect checksum for freed object 0x7fd3f4d00a68: probably modified after being freed.
Corrupt value: 0x7fd3f4d009d0
vec_test(20763,0x10772a5c0) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    20763 abort      ./target/vec_test a b c d e f g

  */
  v->max = new_max;
  v->xs = new_xs;
}
