#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

bool starts_with(const char *string, const char c) { return string[0] == c; }

void get_file_stats(char *filename, struct stat *stbuf) {
  stat(filename, stbuf);
  printf("no argument specified. acting on cwd.\n");
  printf("%llu\n", stbuf->st_ino);
  printf("%u\n", stbuf->st_uid);
  printf("%u\n", stbuf->st_gid);
  printf("%u\n", stbuf->st_rdev);
}

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

#endif
