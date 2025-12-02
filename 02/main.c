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


int is_repeated_twice(const char *s, int n) {
  if (n % 2 != 0) return 0;
  int len = n / 2;
  for (int i = 0; i < len; i++) {
    if (s[i] != s[i + len]) return 0;
  }
  return 1;
}

int is_repeated(const char *s, int n) {
  for (int len = 1; len <= n / 2; len++) {
    if (n % len != 0) continue;
    int ok = 1;
    for (int i = 0; i < len; i++) {
      for (int j = i + len; j < n; j += len) {
	if (s[j] != s[i]) { ok = 0; break; }
      }
      if (!ok) break;
    }
    if (ok) return 1;
  }
  return 0;
}

unsigned long part_1(const char* input)
{
  unsigned long invalid_ids = 0;
  while(*input != '\0')
    {
      unsigned long first_id = 0;
      unsigned long last_id = 0;
      while (*input >= '0' && *input <= '9') {
        first_id = first_id * 10 + (*input - '0');
        input++;
      }
      input++;
      while (*input >= '0' && *input <= '9') {
        last_id = last_id * 10 + (*input - '0');
        input++;
      }
      for (unsigned long i = first_id; i <= last_id; i++)
	{
	  char buf[16];
	  sprintf(buf, "%lu", i);
	  if (is_repeated_twice(buf, strlen(buf))) {
	    invalid_ids += i;
	  }
	}
      
      input++;
    }
  return invalid_ids;
}

unsigned long part_2(const char* input)
{
  unsigned long invalid_ids = 0;
  while(*input != '\0')
    {
      unsigned long first_id = 0;
      unsigned long last_id = 0;
      while (*input >= '0' && *input <= '9') {
        first_id = first_id * 10 + (*input - '0');
        input++;
      }
      input++;
      while (*input >= '0' && *input <= '9') {
        last_id = last_id * 10 + (*input - '0');
        input++;
      }
      for (unsigned long i = first_id; i <= last_id; i++)
	{
	  char buf[16];
	  sprintf(buf, "%lu", i);
	  if (is_repeated(buf, strlen(buf))) {
	    invalid_ids += i;
	  }
	}
      
      input++;
    }
  return invalid_ids;
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
