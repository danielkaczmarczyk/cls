#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

bool starts_with(const char *string, const char c) { return string[0] == c; }

void print_entries(bool going_up, int file_count,
                   struct dirent **directory_entries, int show_hidden) {

  int i = 0;

  if (!going_up) {
    i = file_count - 1;
  }
  int done = 0;
  /*
   * going up is 0..10
   * going down is 10..0
   */

  while (!done) {
    printf("i: %d\n", i);
    struct stat stbuf;
    struct dirent *entry = directory_entries[i];
    const char *entry_name = entry->d_name;
    stat(entry_name, &stbuf);
    if (!show_hidden) {
      if (starts_with(entry_name, '.')) {
        if (going_up) {
          i++;
        } else {
          i--;
        }
        if (going_up) {
          if (i == file_count) {
            printf("swapping done! in going up");
            done = 1;
          }
        } else {
          if (i == 0) {
            printf("swapping done! in going down");
            done = 1;
          }
        }
        continue;
      }
    }
    printf("%s \n", entry_name);
    printf("%d \n", (int)stbuf.st_size);

    // below makes no sense, but this should help to pick up tomoz:
    // https://stackoverflow.com/questions/20238042/is-there-a-c-function-to-get-permissions-of-a-file
    printf("mode int: %d \n", (int)stbuf.st_mode);
    // printf("%hhu\n", directory_entries[file_count]->d_type);
    if (going_up) {
      i++;
    } else {
      i--;
    }
    if (going_up) {
      if (i == file_count) {
        printf("swapping done! in going up");
        done = 1;
      }
    } else {
      if (i == 0) {
        printf("swapping done! in going down");
        done = 1;
      }
    }
  }
}

#endif
