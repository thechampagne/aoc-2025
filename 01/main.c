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

int part_1(const char* input)
{
  int password = 0;
  int dial = 50;
  while(*input != '\0')
    {
      char c = *input;
      int num = 0;
      input++;
      while(*input != '\0' && *input != '\n')
	{
	  num = num * 10 + (*input - '0');
	  input++;
	}      
      if (c == 'L')
        dial = (dial - num) % 100;
      else if (c == 'R')
	dial = (dial + num) % 100;
      
      if (dial < 0) dial += 100;
      if (dial == 0) password++;
      if (*input != '\0') input++;
    }
  return password;
}

int part_2(const char* input)
{
  int password = 0;
  int dial = 50;
  while(*input != '\0')
    {
      char c = *input;
      int num = 0;
      input++;
      while(*input != '\0' && *input != '\n')
	{
	  num = num * 10 + (*input - '0');
	  input++;
	}

      while(num > 0)
	{
	  if (c == 'L') dial--;
	  else dial++;
	  if(dial == 100 || dial == -100) dial = 0;
	  if (dial == 0) password++;
	  num--;
	}
      if (*input != '\0') input++;
    }
  return password;
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
  printf("Part 2: %d\n", part_2(input));
  return 0;
}
