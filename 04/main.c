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

int part_1(const char* input)
{
  int rolls = 0;
  char roll[200][200] = {0};
  int i = 0;
  while (*input != '\0') {
    int j = 0;
    while (*input != '\0' && *input != '\n') {
      roll[i][j++] = *input;
      input++;
    }
    roll[i][j] = '\0';
    i++;
    if (*input == '\n') input++;
  }
  int num_rows = i;
  for (int r = 0; r < num_rows; r++) {
    int num_cols = strlen(roll[r]);
    for (int c = 0; c < num_cols; c++) {
      if (roll[r][c] != '@') continue;
      int count = 0;
      for (int dr = -1; dr <= 1; dr++) {
	for (int dc = -1; dc <= 1; dc++) {
	  if (dr == 0 && dc == 0) continue;
	  int nr = r + dr;
	  int nc = c + dc;
	  if (nr < 0 || nr >= num_rows) continue;
	  if (nc < 0 || nc >= (int)strlen(roll[nr])) continue;
	  if (roll[nr][nc] == '@') count++;
	}
      }
      if (count < 4)
        rolls++;
    }
  }
  return rolls;
}

int part_2(const char* input)
{
  int rolls = 0;
  char roll[200][200] = {0};
  int i = 0;
  while (*input != '\0') {
    int j = 0;
    while (*input != '\0' && *input != '\n') {
      roll[i][j++] = *input;
      input++;
    }
    roll[i][j] = '\0';
    i++;
    if (*input == '\n') input++;
  }
  int end = 1;
  while(end) {
    end = 0;
    int num_rows = i;
    for (int r = 0; r < num_rows; r++) {
      int num_cols = strlen(roll[r]);
      for (int c = 0; c < num_cols; c++) {
	if (roll[r][c] != '@') continue;
	int count = 0;
	for (int dr = -1; dr <= 1; dr++) {
	  for (int dc = -1; dc <= 1; dc++) {
	    if (dr == 0 && dc == 0) continue;
	    int nr = r + dr;
	    int nc = c + dc;
	    if (nr < 0 || nr >= num_rows) continue;
	    if (nc < 0 || nc >= (int)strlen(roll[nr])) continue;
	    if (roll[nr][nc] == '@') count++;
	  }
	}
	if (count < 4) {
	  roll[r][c] = '.';
	  rolls++;
	  end = 1;
	}
      }
    }
  }
  return rolls;
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
