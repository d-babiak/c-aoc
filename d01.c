#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_space(char c) {
  return c == 32 || c == 10;
}

// yolo
void strip(char *s) {
  char *p = s;
  size_t n = strlen(s) - 1;
  while (n >= 0 && is_space(s[n])) {
    s[n--] = '\0';
  }
}

int sum(int xs[], size_t n) {
  int acc = 0;
  for (int i = 0; i < n; i++)
    acc += xs[i];
  return acc;
}

void read_input(int xs[], size_t N) {
  FILE *fp = fopen("./inputs/d01.text", "r");
  char s[64];

  for (int i = 0; i < N; i++)
    xs[i] = atoi(fgets(s, sizeof s, fp));
}

int main(int argc, char *argv[]) {
  // ./d1_p01 $(wc -l ./inputs/d01.text) # lol
  int N = atoi(argv[1]);
  int xs[N];

  read_input(xs, N);

  int d1_p1 = sum(xs, N);

  printf("part 1: %d\n", d1_p1);
}
