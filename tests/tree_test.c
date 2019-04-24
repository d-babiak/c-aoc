#include <stdio.h>
#include "../dmb/tree.h"

void test_get(Map *m, int k) {
  int *v = M_get(m, k);
  if (NULL == v)
    printf("%d: null\n", k);
  else 
    printf("%d: %d\n", k, *v);

}

int main(int argc, char *argv[]) {
  Map *m = NULL;
  M_set(&m, 3, 4);
  test_get(m, 3);
  test_get(m, 42);
  M_set(&m, 42, 7);
  test_get(m, 42);
  test_get(m, 3);
  M_set(&m, 3, -1);
  test_get(m, 3);
}
