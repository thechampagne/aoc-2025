#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *file_read(const char *filename) {
    FILE *file;
    int ch;
    if ((file = fopen(filename, "r")) == NULL)
        return NULL;
    if (fseek(file, 0L, SEEK_END))
        return NULL;
    long size = ftell(file);
    if (fseek(file, 0L, SEEK_SET))
        return NULL;
    char *content = (char *) malloc((size + 1) * sizeof(char));
    if (content == NULL)
        return NULL;
    int i = 0;
    while ((ch = getc(file)) != EOF) {
        content[i] = (char) ch;
        i++;
    }
    if (fclose(file))
        return NULL;
    return content;
}

struct pos_t
{
  int row;
  int col;
};

unsigned long part_1(const char* input)
{
  int rows = 0, cols = -1, current_len = 0;
  for (const char *p = input; ; p++) {
    if (*p == '\n' || *p == '\0') {
      if (current_len > 0) {
	if (cols == -1) cols = current_len;
	current_len = 0;
	rows++;
      }
      if (*p == '\0') break;
    } else {
      current_len++;
    }
  }
  char **grid = malloc(rows * sizeof(char*));
  const char *p = input;
  for (int r = 0; r < rows; r++) {
    grid[r] = malloc(cols + 1);
    int j = 0;
    while (*p != '\n' && *p != '\0')
      grid[r][j++] = *p++;
    grid[r][j] = '\0';
    if (*p == '\n') p++;
  }
  int sr = -1, sc = -1;
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      if (grid[r][c] == 'S') { sr = r; sc = c; }
  if (sr == -1) return -1;
  char **vis = malloc(rows * sizeof(char*));
  for (int r = 0; r < rows; r++)
    vis[r] = calloc(cols, 1);
  int qcap = 128, qlen = 0, qhead = 0;
  struct pos_t *q = malloc(qcap * sizeof(struct pos_t));
  if (qlen == qcap) { qcap *= 2; q = realloc(q, qcap*sizeof(struct pos_t)); }	\
  q[(qhead + qlen) % qcap] = (struct pos_t){sr, sc};					\
  qlen++;
  unsigned long triggered = 0;
  while (qlen > 0) {
    struct pos_t cur = q[qhead]; qhead = (qhead+1)%qcap; qlen--;
    int r = cur.row, c = cur.col;
    if (r < 0 || r >= rows || c < 0 || c >= cols) continue;
    if (vis[r][c]) continue;
    vis[r][c] = 1;
    char ch = grid[r][c];
    if (ch == '^') {
      triggered++;
      if (qlen == qcap) { qcap *= 2; q = realloc(q, qcap*sizeof(struct pos_t)); }
      q[(qhead + qlen) % qcap] = (struct pos_t){r, c-1};
      qlen++;
      if (qlen == qcap) { qcap *= 2; q = realloc(q, qcap*sizeof(struct pos_t)); }
      q[(qhead + qlen) % qcap] = (struct pos_t){r, c+1};
      qlen++;
    } else {
      if (qlen == qcap) { qcap *= 2; q = realloc(q, qcap*sizeof(struct pos_t)); }
      q[(qhead + qlen) % qcap] = (struct pos_t){r+1, c};
      qlen++;
    }
  }
  for (int r = 0; r < rows; r++) {
    free(grid[r]);
    free(vis[r]);
  }
  free(grid);
  free(vis);
  free(q);
  return triggered;
}

unsigned long long part_2(const char* input)
{
  int rows = 0, cols = -1, len = 0;
  for (const char *p = input; ; p++) {
    if (*p == '\n' || *p == '\0') {
      if (len > 0) {
	if (cols == -1) cols = len;
	len = 0;
	rows++;
      }
      if (*p == '\0') break;
    } else len++;
  }
  char **grid = malloc(rows * sizeof(char*));
  const char *p = input;
  for (int r = 0; r < rows; r++) {
    grid[r] = malloc(cols + 1);
    int j = 0;
    while (*p != '\n' && *p != '\0')
      grid[r][j++] = *p++;
    grid[r][j] = '\0';
    if (*p == '\n') p++;
  }
  int sr = -1, sc = -1;
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      if (grid[r][c] == 'S') { sr = r; sc = c; }
  if (sr < 0) return -1;
  unsigned long long **memo = malloc(rows * sizeof(unsigned long long*));
  for (int r = 0; r < rows; r++) {
    memo[r] = malloc(cols * sizeof(unsigned long long));
    for (int c = 0; c < cols; c++)
      memo[r][c] = -1;
  }
  unsigned long long dfs(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
      return 1;
    if (memo[r][c] != -1)
      return memo[r][c];
    char ch = grid[r][c];
    unsigned long long ways;
    if (ch == '^') {
      unsigned long long left  = dfs(r, c-1);
      unsigned long long right = dfs(r, c+1);
      ways = left + right;
    } else {
      ways = dfs(r+1, c);
    }
    memo[r][c] = ways;
    return ways;
  }
  unsigned long long result = dfs(sr, sc);
  for (int r = 0; r < rows; r++) {
    free(grid[r]);
    free(memo[r]);
  }
  free(grid);
  free(memo);
  return result;
}

int main(int argc, const char** argv)
{
  if (argc <= 1) {
    fprintf(stderr, "Error: Input file is not provided\n");
    return 1;
  }
  char* input = file_read(argv[1]);
  if (input == NULL) {
    perror("Error");
    return 1;
  }
  printf("Part 1: %lu\n", part_1(input));
  printf("Part 2: %llu\n", part_2(input));
  return 0;
}
