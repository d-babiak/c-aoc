#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Brian Kernighan disapproves 
#define min(x,y) (x <= y ? x : y)
#define max(x,y) (x >= y ? x : y)

// hmm...
// what storage allocation?
const char s[] = "#1 @ 1,3: 4x4";

typedef struct Claim {
  uint32_t claim_id;
  uint32_t col;
  uint32_t row;
  uint32_t width;
  uint32_t height;
} Claim;

void print_claim(Claim *claim) {
  printf(
    "id: %d, col: %d, row: %d, w: %d, h: %d\n",
    claim->claim_id,
    claim->col,
    claim->row,
    claim->width,
    claim->height
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
    .claim_id = id,
    .col = c,
    .row = r,
    .width = w,
    .height = h
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

// exclusive ...?
uint32_t right(Claim *claim) {
  return claim->col + claim->width;
}

uint32_t bottom(Claim *claim) {
  return claim->row + claim->height;
}

uint32_t get_max_col(Claim claims[], size_t n) {
  uint32_t acc = right(&claims[0]);

  for (int i = 1; i < n; i++)
    acc = max(acc, right(&claims[i]));

  return acc;
}

uint32_t get_max_row(Claim claims[], size_t n) {
  uint32_t acc = bottom(&claims[0]);

  for (int i = 1; i < n; i++)
    acc = max(acc, bottom(&claims[i]));

  return acc;
}

void place_claim(Claim *claim, uint32_t max_row, uint32_t max_col, uint32_t grid[max_row][max_col]) {
  for (uint32_t row = claim->row; row < bottom(claim); row++)
    for (uint32_t col = claim->col; col < right(claim); col++) {
      //printf("row: %d, col: %d\n", row, col);
      grid[row][col] = grid[row][col] + 1;
    }
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

int main(int argc, char *argv[]) {
  assert(argc == 2);
  char *pathname = argv[1];
  size_t N = line_count(pathname);
  Claim claims[N];
  memset(claims, 0, sizeof claims);
  parse_claims(pathname, claims, N);

  //for (int i = 0; i < N; i++)
  //  print_claim(&claims[i]);

  uint32_t max_row = get_max_row(claims, N);
  uint32_t max_col = get_max_col(claims, N);

  printf("max_col: %d, max_row: %d\n", max_col, max_row);
  uint32_t grid[max_row][max_col];
  memset(grid, 0, sizeof grid);
  printf("sizeof grid: %zd\n", sizeof grid);

  for (int i = 0; i < N; i++)
    place_claim(&claims[i], max_row, max_col, grid);

  printf("claims placed\n");

  uint32_t n_conflicts = d3_p1(max_row, max_col, grid);
  printf("part 1: %d\n", n_conflicts);
}
