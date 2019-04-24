#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmb/tree.h"

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

int increment(Map **m, int k) {
  int *n = M_get(*m, k);

  if (NULL == n) {
    M_set(m, k, 1);
    return 1;
  } else {
    return *n += 1; // hmm...
  }
}

int d1_p2(int xs[], size_t N) {
  Map *m = NULL;
  int freq = 0;
  for (;;) {
    for (int i = 0; i < N; i++) {
      freq += xs[i];
      int n = increment(&m, freq);
      //printf("freq: %d, count: %d\n", freq, n);
      if (n > 1)
        return freq;
    }
  }
}

int main(int argc, char *argv[]) {
  // ./d1_p01 $(wc -l ./inputs/d01.text) # lol
  int N = atoi(argv[1]);
  int xs[N];

  read_input(xs, N);

  printf("part 1: %d\n",   sum(xs, N));
  printf("part 2: %d\n", d1_p2(xs, N));
}
