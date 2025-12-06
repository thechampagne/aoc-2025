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

int parse_problems1(unsigned long* line, const char** in)
{
  const char* input = *in;
  int len = 0;
  while(*input != '\0' && *input != '\n') {
    if (*input != ' ' && *input != '\n') {
      unsigned long num = 0;
      while(*input != ' ' && *input != '\n') {
	num = num * 10 + (*input - '0');
	input++;
      }
      line[len] = num;
      len++;
    }
    while(*input != '\n' && *input == ' ') input++;
  }
  input++;
  *in = input;
  return len;
}

unsigned long part_1(const char* input)
{
  unsigned long total = 0;
  unsigned long line1[4000] = {0};
  unsigned long line2[4000] = {0};
  unsigned long line3[4000] = {0};
  unsigned long line4[4000] = {0};
  int len = 0;
  len = parse_problems1(line1, &input);
  parse_problems1(line2, &input);
  parse_problems1(line3, &input);
  parse_problems1(line4, &input);
  int i = 0;
  while(*input != '\0') {
    if (*input != ' ') {
      if (*input == '+') total += line1[i] + line2[i] + line3[i] + line4[i];
      else total += line1[i] * line2[i] * line3[i] * line4[i];
      i++;
    }
    input++;
  }
  return total;
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
  //printf("Part 2: %lu\n", part_2(input));
  return 0;
}
