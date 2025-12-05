#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct range_t
{
  unsigned long first;
  unsigned long last;
};

int cmp_range(const void* r0, const void* r1)
{
  if (((struct range_t*)r0)->first < ((struct range_t*)r1)->first) return -1;
  if (((struct range_t*)r0)->first > ((struct range_t*)r1)->first) return 1;
  return 0;
}

int merge_ranges(struct range_t *ranges, int count) {
  int m = 0;
  for (int i = 1; i < count; i++) {
    if (ranges[m].last >= ranges[i].first - 1) {
      if (ranges[i].last > ranges[m].last)
	ranges[m].last = ranges[i].last;
    } else {
      m++;
      ranges[m] = ranges[i];
    }
  }
  return m + 1;
}

int search(struct range_t* ranges, int n, unsigned long x) {
  int low = 0, high = n - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (x < ranges[mid].first)
      high = mid - 1;
    else if (x > ranges[mid].last)
      low = mid + 1;
    else
      return 1;
  }

  return 0;
}

int part_1(const char* input)
{
  int fresh = 0;
  struct range_t ranges[200] = {0};
  int i = 0;
  while(*input != '\0' && *input != '\n') {
    unsigned long num1 = 0;
    while(*input != '-') {
      num1 = num1 * 10 + (*input - '0');
      input++;
    }
    unsigned long num2 = 0;
    input++;
    while(*input != '\n') {
      num2 = num2 * 10 + (*input - '0');
      input++;
    }
    struct range_t range = {num1, num2};
    ranges[i] = range;
    i++;
    input++;
  }
  qsort(ranges, i, sizeof(struct range_t), cmp_range);
  i = merge_ranges(ranges, i);
  input++;
  while(*input != '\0') {
    unsigned long num = 0;
    while(*input != '\0' && *input != '\n') {
      num = num * 10 + (*input - '0');
      input++;
    }
    for(int j = 0; j < i; j++) {
      struct range_t range = ranges[j];
      if (num < range.first && num > range.last) continue;
      if (search(ranges, i, num)) {
	fresh++;
	break;
      }
    }
    input++;
  }
  return fresh;
}

unsigned long part_2(const char* input)
{
  unsigned long fresh = 0;
  struct range_t ranges[200] = {0};
  int i = 0;
  while(*input != '\0' && *input != '\n') {
    unsigned long num1 = 0;
    while(*input != '-') {
      num1 = num1 * 10 + (*input - '0');
      input++;
    }
    unsigned long num2 = 0;
    input++;
    while(*input != '\n') {
      num2 = num2 * 10 + (*input - '0');
      input++;
    }
    struct range_t range = {num1, num2};
    ranges[i] = range;
    i++;
    input++;
  }
  qsort(ranges, i, sizeof(struct range_t), cmp_range);
  i = merge_ranges(ranges, i);
  input++;
  for(int j = 0; j < i; j++) {
    struct range_t range = ranges[j];
    fresh += range.last - range.first + 1;
  }
  return fresh;
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
  printf("Part 1: %d\n", part_1(input));
  printf("Part 2: %lu\n", part_2(input));
  return 0;
}
