#include "helpers.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int direction = 1;
  int show_hidden = 0;
  int flag;

  while ((flag = getopt(argc, argv, "ra")) != -1) {
    printf("flag: %d\n", flag);
    switch (flag) {
    case 'r':
      direction = 0; // set direction to reverse
      break;
    case 'a':
      show_hidden = 1;
      break;
    default:
      printf("usage: -[ra]\n");
    }
  }

  struct dirent **directory_entries;
  int file_count;
  char *directory = ".";

  if (argc > 1) {
    if (!starts_with("-", argv[1][0])) {
      directory = argv[1];
    }
  }

  file_count = scandir(directory, &directory_entries, NULL, alphasort);

  if (file_count < 0) {
    perror("scandir");
    exit(EXIT_FAILURE);
  } else {
    print_entries(direction, file_count, directory_entries, show_hidden);
    printf("\n");
    free(directory_entries);
    exit(EXIT_SUCCESS);
  }
}
