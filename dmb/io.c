#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "./io.h"
#include "./vec.h"

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

// todo - max line...?
Vec *IO_read_input(char *pathname) {
  FILE *fp = fopen(pathname, "r");
  assert(fp != NULL);

  Vec *v = V_init();

  char line[4096];
  while (NULL != fgets(line, sizeof line, fp)) {
    V_push(v, strip(line));
  }

  int err = fclose(fp);
  assert(!err);

  return v;
}
