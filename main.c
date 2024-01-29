#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct config {
  _Bool append;
};

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s [-a] file1 file2\n", argv[0]);
    return 1;
  }

  int i;
  FILE **files;

  struct config cfg = {};
  for (i = 1; i < argc; i++) {
    // to keep the pointer point out into flag value only.
    if (strcmp(argv[i], "-a") == 0) {
      cfg.append = 1;
    } else {
      break;
    }
  }

  size_t files_counter = 0;
  files = malloc(sizeof(FILE) * (argc - i));
  while (i < argc) {
    FILE *file = fopen(argv[i], cfg.append == 1 ? "a" : "w");
    if (file == NULL) {
      printf("Failed to open file: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
    files[files_counter] = file;

    files_counter++;
    i++;
  }

  // i have to wrote to two source which is stdout and the given files.
  // accept the stdin -> stdout & files
  char buf[1024];
  size_t bytes_read;
  while ((bytes_read = fread(buf, 1, sizeof(buf), stdin)) > 0) {
    fwrite(buf, 1, bytes_read, stdout);
    for (size_t i = 0; i < files_counter; i++) {
      fwrite(buf, 1, bytes_read, files[i]);
    }
  }

  for (size_t i = 0; i < files_counter; i++) {
    fclose(files[i]);
  }

  free(files);

  return 0;
}

int len(char *s) {
  int i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}
