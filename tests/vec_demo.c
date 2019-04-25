#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../dmb/vec.h" 

bool is_space(char c) {
  return c == ' ' || c == '\n';
}

char *strip(char *s) {
  char *p = s;
  size_t n = strlen(p) - 1;
  while (n > 0 && is_space(p[n])) {
    p[n] = '\0';
    n--;
  }
  return s;
}

int main(int argc, char *argv[]) {
  Vec *v = V_init();
  FILE *fp = fopen(argv[1], "r");
  char line[4096];

  while (NULL != fgets(line, sizeof line, fp)) {
    V_push(v, strip(line));
  }

  V_each(v, puts);
}
