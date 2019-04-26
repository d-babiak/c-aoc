#ifndef DMB_VOID_VEC
#define DMB_VOID_VEC

#include <inttypes.h>
#include <sys/types.h>

typedef struct VVec {
  size_t n;
  size_t n_max;
  void **xs;
} VVec;

VVec *VV_init();

void VV_push(VVec *v, void *x);

void *VV_pop(VVec *v);

void *VV_get(VVec *v, uint32_t i);

void VV_each(VVec *v, void(*f)(void*));
#endif
