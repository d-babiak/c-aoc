#include <stdio.h>
#include <stdlib.h>

#include "../dmb/vec.h"

int main(int argc, char *argv[]) {
  Vec *v = V_init();

  for (int i = 1; i < argc; i++) {
    printf("Pushed: %s\n", argv[i]);
    V_push(v, argv[i]);
  }

  while(v->n > 0) {
    char *s = V_pop(v);
    printf("popped: %s\n", s);
  }
}
