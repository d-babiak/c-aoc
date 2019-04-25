#include <assert.h>
#include <inttypes.h>
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

uint32_t common_chars(char *s1, char *s2, char *buf, size_t N) {
  memset(buf, '\0', N);

  uint32_t n = 0;

  for (int i = 0; s1[i] && s2[i]; i++)
    if (s1[i] == s2[i])
      buf[n++] = s1[i];

  return n;
}

char *part_two(Vec *lines) {
  char buf[64];
  for (int i = 0; i < lines->n - 1; i++)
    for (int j = i + 1; j < lines->n; j++)
      
      if ((26/*✨🧙✨*/ - common_chars(V_get(lines, i), V_get(lines, j), buf, sizeof buf)) == 1)
        return strdup(buf);
  assert(false);
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

  char *d2_p2 = part_two(lines);
  printf("part 2: %s\n", d2_p2);
}
