#include <stdio.h>
#include <string.h>

#include "dmb/io.h"
#include "dmb/vec.h"

void character_counts(char *s, int counts[], size_t n) { 
  memset(counts, 0, n * sizeof(int));

  for (char *c = s; *c != '\0'; c++)
    counts[*c] += 1;
}

bool has_char_with_k(int counts[], int k) {
  size_t acc = 0;

  for (int i = 'A'; i <= 'Z'; i++)
    if (counts[i] == k)
      return true;

  for (int i = 'a'; i <= 'z'; i++)
    if (counts[i] == k)
      return true;

  return false;
}

int main(int argc, char *argv[]) {
  Vec *lines  = IO_read_input(argv[1]);

  int counts['z' + 1]; // n_n

  size_t twos = 0;
  size_t threes = 0;

  for (int i = 0; i < lines->n; i++) {
    char *line = V_get(lines, i);
    character_counts(line, counts, 'z' + 1);
    twos   += has_char_with_k(counts, 2);
    threes += has_char_with_k(counts, 3);
  }

  int d2_p1 = twos * threes;

  printf("part 1: %d\n", d2_p1);
}
