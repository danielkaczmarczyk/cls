#include "helpers.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEBUG_ON 1

int main(int argc, char **argv) {
  if (DEBUG_ON) {
    printf("DEBUG MODE: ON\n");
    printf("--------------\n");
    printf("parsing flags...\n");
  }

  int direction = 0; // normal=0, reverse=1
  int show_hidden = 0;
  int flag;

  while ((flag = getopt(argc, argv, "r")) != -1) {
    printf("flag: %d\n", flag);
    switch (flag) {
    case 'r':
      if (DEBUG_ON)
        printf("setting direction: reverse\n");
      direction = 1;
      break;
    default:
      printf("usage: -[r]\n");
    }
  }
  if (DEBUG_ON) {
    printf("parsing flags complete...\n");
    printf("argc: %d\n", argc);
    printf("files: \n\n");
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
