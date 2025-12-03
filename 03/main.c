#include <stdio.h>
#include <stdlib.h>

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

unsigned long part_1(const char* input)
{
  unsigned long out = 0;
  while(*input != '\0')
    {
      int digits[10000];
      int m = 0;
      while (*input >= '0' && *input <= '9') {
	digits[m++] = *input - '0';
	input++;
      }
      int best = 0;
      for (int i = 0; i < m - 1; i++) {
	int first = digits[i];
	int second_max = -1;
	for (int j = i + 1; j < m; j++) {
	  if (digits[j] > second_max)
	    second_max = digits[j];
	}
	int candidate = first * 10 + second_max;
	if (candidate > best)
	  best = candidate;
      }
      out += best;
      input++;
    }
  return out;
}

unsigned long part_2(const char* input)
{
  unsigned long out = 0;
  while(*input != '\0')
    {
      int digits[10000];
      int m = 0;
      while (*input >= '0' && *input <= '9') {
        digits[m++] = *input - '0';
	input++;
      }
      int result[12];
      int top = 0;
      for (int i = 0; i < m; i++) {
        int d = digits[i];
        while (top > 0 && result[top-1] < d && (top-1 + (m-i)) >= 12) {
	  top--;
        }
        if (top < 12) {
	  result[top++] = d;
        }
      }
      unsigned long num = 0;
      for (int i = 0; i < 12; i++) {
        num = num * 10 + (result[i] - 0);
      }
      out += num;
      input++;
    }
  return out;
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
  printf("Part 2: %lu\n", part_2(input));
  return 0;
}
