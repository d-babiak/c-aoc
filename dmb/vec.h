#ifndef DMB_VEC
#define DMB_VEC

// is there any hope for "reusable" data structures
typedef struct Vec {
  size_t n;
  size_t max;
  char **xs;
} Vec;

Vec *V_init();

void V_push(Vec *v, char *s);

char *V_pop(Vec *v);

void _grow(Vec *v);

void _shrink(Vec *v);

#endif
