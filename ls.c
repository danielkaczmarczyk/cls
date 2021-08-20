#include "helpers.h"
#include <dirent.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DEBUG_ON 1

void print_entries(int direction, int file_count,
                   struct dirent **directory_entries) {
  int i = 0;
  while (i < file_count) {
    char *entry_name = directory_entries[i]->d_name;
    if (!starts_with(entry_name, '.')) {
      printf("%s ", entry_name);
    }
    // printf("%hhu\n", directory_entries[file_count]->d_type);
    i++;
  }
  printf("\n");
}

/*
 * file OR directory - same thing
 */
void get_file_stats(char *filename, struct stat *stbuf) {
  // man 2 stat to look up details
  stat(filename, stbuf);

  printf("no argument specified. acting on cwd.\n");
  printf("%llu\n", stbuf->st_ino);
  printf("%u\n", stbuf->st_uid);
  printf("%u\n", stbuf->st_gid);
  printf("%u\n", stbuf->st_rdev);
}

// make it accept a pointer to array to the config
void parse_flags(int argc, char **argv, int *direction) {
  int flag;
  printf("parsing flags...\n");
  while ((flag = getopt(argc, argv, "r")) != -1) {
    printf("flag: %d\n", flag);
    switch (flag) {
    case 'r':
      if (DEBUG_ON)
        printf("setting direction: reverse\n");
      *direction = 1;
      break;
    default:
      printf("usage: -[r]\n");
    }
  }
  printf("parsing flags complete...\n");
}

int main(int argc, char **argv) {
  if (DEBUG_ON)
    printf("DEBUG MODE: ON\n");
  if (DEBUG_ON)
    printf("--------------\n");

  int direction = 0; // normal=0, reverse=1
  int flag;

  printf("parsing flags...\n");
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
  printf("parsing flags complete...\n");

  // get the directory entries
  struct dirent **directory_entries;
  int file_count;
  char *directory = ".";
  printf("argc: %d\n", argc);

  // if the first argument starts with a `-`, then directory stays as default
  // if it does not, then it must be a directory name
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
    print_entries(direction, file_count, directory_entries);
    printf("\n");
    free(directory_entries);
  }
  exit(EXIT_SUCCESS);
}
