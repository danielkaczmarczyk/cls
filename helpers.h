#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
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
  /*
   * i'm operating on them sequentially, so
   * i can malloc just what is necessary for the
   * given file struct for statbuf and free it after printing
   */
  int i = 0;
  while (i < file_count) {
    struct stat stbuf;
    struct dirent *entry = directory_entries[i];
    const char *entry_name = entry->d_name;
    stat(entry_name, &stbuf);
    //if (!starts_with(entry_name, '.')) {
      printf("%s \n", entry_name);
      printf("%d \n", (int)stbuf.st_size);

      // below makes no sense, but this should help to pick up tomoz:
      // https://stackoverflow.com/questions/20238042/is-there-a-c-function-to-get-permissions-of-a-file
      printf("%d \n", (int)stbuf.st_mode);

    //}
    // printf("%hhu\n", directory_entries[file_count]->d_type);
    i++;
    // free the memory ?
  }
}

#endif
