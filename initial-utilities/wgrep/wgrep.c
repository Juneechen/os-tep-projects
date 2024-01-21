#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char *search;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  if (argc < 2) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  search = argv[1];
  if (argc == 2) { // if provided a search term, but no file
    fp = stdin;
    while ((nread = getline(&line, &len, fp)) != -1) {
      if (strstr(line, search) != NULL) {
        printf("%s", line);
      }
    }
  } else {
    for (int i = 2; i < argc; i++) {
      fp = fopen(argv[i], "r");
      if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }
      while ((nread = getline(&line, &len, fp)) != -1) {
        if (strstr(line, search) != NULL) {
          printf("%s", line);
        }
      }
      fclose(fp);
    }
  }
}
