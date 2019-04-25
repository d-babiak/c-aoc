#include <assert.h>
#include <stdbool.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Brian Kernighan disapproves 
#define max(x,y) (x >= y ? x : y)

// hmm...
// what storage allocation?
const char s[] = "#1 @ 1,3: 4x4";

typedef struct Interval {
  uint32_t lo;
  uint32_t hi;
} Interval;

typedef struct Claim {
  uint32_t id;
  Interval rows;
  Interval cols;
} Claim;

void print_claim(Claim *claim) {
  printf(
    "id: %d, cl: %d, ch: %d, rl: %d, rh: %d\n",
    claim->id,
    claim->cols.lo,
    claim->cols.hi,
    claim->rows.lo,
    claim->rows.hi
  );
}

Claim parse_claim(char *s) {
  uint32_t id, c, r, w, h;

  sscanf(
    s, 
    "#%d @ %d,%d: %dx%d", 
     &id,  &c,&r, &w,&h  
  );

  Claim claim = {
    .id = id,
    .cols = { .lo = c, .hi = c + w - 1 },
    .rows = { .lo = r, .hi = r + h - 1 }
  };
  return claim;
}


// ssize_t...?
size_t parse_claims(char *pathname, Claim claims[], size_t n) {
  FILE *fp = fopen(pathname, "r");
  assert(fp != NULL);
  char buf[1024];
  int i = 0;

  while (fgets(buf, sizeof buf, fp))
    claims[i++] = parse_claim(buf);

  fclose(fp);

  assert(i == n);
  return i;
}

size_t line_count(char *pathname) {
  int fd = open(pathname, O_RDONLY);
  assert(fd >= 0);
  char buf[4096];
  size_t n_lines = 0;
  ssize_t n;

  while ((n = read(fd, buf, sizeof buf)) > 0)
    for (int i = 0; i < n; i++)
      if (buf[i] == '\n')
        n_lines++; 

  close(fd);
  return n_lines;
}

uint32_t get_max_col(Claim claims[], size_t n) {
  uint32_t acc = claims[0].cols.hi;

  for (int i = 1; i < n; i++)
    acc = max(acc, claims[i].cols.lo);

  return acc + 1;
}

uint32_t get_max_row(Claim claims[], size_t n) {
  uint32_t acc = claims[0].rows.hi;

  for (int i = 1; i < n; i++)
    acc = max(acc, claims[i].rows.hi);

  return acc + 1;
}

void place_claim(
  Claim *claim, 
  uint32_t max_row, uint32_t max_col, uint32_t grid[max_row][max_col]
) {
  for (uint32_t r = claim->rows.lo; r <= claim->rows.hi; r++)
    for (uint32_t c = claim->cols.lo; c <= claim->cols.hi; c++)
      grid[r][c]++;
}

/*
"From C99, C language supports variable sized arrays to be passed simply by specifying the variable dimensions 

(dimensions must be passed before the array)

otherwise: (arr+ row * n_cols) + col 
*/
uint32_t d3_p1(uint32_t max_row, uint32_t max_col, uint32_t grid[max_row][max_col]) {
  uint32_t n_conflicts = 0;

  for (uint32_t row = 0; row < max_row; row++)
    for (uint32_t col = 0; col < max_col; col++)
      if (grid[row][col] > 1)
        n_conflicts++;

  return n_conflicts;
}

void find_conflict_free(
  uint32_t *R, uint32_t *C, 
  uint32_t nrow, uint32_t ncol, uint32_t grid[nrow][ncol]
) {
  for (uint32_t row = 0; row < nrow; row++)
    for (uint32_t col = 0; col < ncol; col++)
      if (grid[row][col] == 1) {
        *R = row;
        *C = col;
        return;
      }
}

bool I_contains(Interval *I, int x) {
  return I->lo <= x && x <= I->hi;
}

bool I_intersects(Interval *ab, Interval *cd) {
  return I_contains(ab, cd->lo) 
      || I_contains(ab, cd->hi)
      || I_contains(cd, ab->lo)
      || I_contains(cd, ab->hi);
}


bool claims_overlap(Claim *c1, Claim *c2) {
  return I_intersects(&c1->rows, &c2->rows) 
      && I_intersects(&c1->cols, &c2->cols);
}

bool all_disjoint(Claim *claim, Claim claims[], size_t N) {
  for (int j = claim->id + 1; j < N; j++)
    if (claims_overlap(claim, &claims[j]))
      return false;

  return true;
}

Claim d3_p2(Claim claims[], size_t N) {
  for (int i = 0; i < N - 1; i++)
    if (all_disjoint(&claims[i], claims, N))
      return claims[i];
  assert(false);
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  char *pathname = argv[1];
  size_t N = line_count(pathname);
  Claim claims[N];
  memset(claims, 0, sizeof claims);
  parse_claims(pathname, claims, N);

  // ffs
  uint32_t max_row = 1000; // get_max_row(claims, N);
  uint32_t max_col = 1000; // get_max_col(claims, N);

  printf("max_col: %d, max_row: %d\n", max_col, max_row);
  uint32_t grid[max_row][max_col];
  memset(grid, 0, sizeof grid);
  printf("sizeof grid: %zd\n", sizeof grid);

  for (int i = 0; i < N; i++)
    place_claim(&claims[i], max_row, max_col, grid);

  printf("claims placed\n");

  uint32_t n_conflicts = d3_p1(max_row, max_col, grid);
  printf("part 1: %d\n", n_conflicts);

  Claim conflict_free = d3_p2(claims, N);
  printf("part2: %d\n", conflict_free.id);
}
