#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

bool starts_with(const char *string, const char c) { return string[0] == c; }

void print_entries(int direction, int file_count,
                   struct dirent **directory_entries, int show_hidden) {
  int i = 0;

  while (i < file_count) {
    struct stat stbuf;
    struct dirent *entry = directory_entries[i];
    const char *entry_name = entry->d_name;
    stat(entry_name, &stbuf);
    if (!show_hidden) {
      if (starts_with(entry_name, '.')) {
        i++;
        continue;
      }
    }
    printf("%s \n", entry_name);
    printf("%d \n", (int)stbuf.st_size);

    // below makes no sense, but this should help to pick up tomoz:
    // https://stackoverflow.com/questions/20238042/is-there-a-c-function-to-get-permissions-of-a-file
    printf("%d \n", (int)stbuf.st_mode);
    // printf("%hhu\n", directory_entries[file_count]->d_type);
    i++;
  }
}

#endif
