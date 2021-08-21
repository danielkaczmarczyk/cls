#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

void loop_controls(int going_up, int limit, int *done, int *i) {
  if (going_up) {
    (*i)++;
  } else {
    (*i)--;
  }
  if (going_up) {
    if (*i == limit) {
      *done = 1;
    }
  } else {
    if (*i == 0) {
      *done = 1;
    }
  }
}

bool starts_with(const char *string, const char c) { return string[0] == c; }

void print_entries(bool going_up, int file_count,
                   struct dirent **directory_entries, int show_hidden) {

  int i = 0;
  int done = 0;

  if (!going_up) {
    i = file_count - 1;
  }

  while (!done) {
    printf("i: %d\n", i);
    struct stat stbuf;
    struct dirent *entry = directory_entries[i];
    const char *entry_name = entry->d_name;
    stat(entry_name, &stbuf);

    loop_controls(going_up, file_count, &done, &i);

    // Permissions
    printf((S_ISDIR(stbuf.st_mode)) ? "d" : "-");
    printf((stbuf.st_mode & S_IRUSR) ? "r" : "-");
    printf((stbuf.st_mode & S_IWUSR) ? "w" : "-");
    printf((stbuf.st_mode & S_IXUSR) ? "x" : "-");
    printf((stbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf((stbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf((stbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf((stbuf.st_mode & S_IROTH) ? "r" : "-");
    printf((stbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf((stbuf.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %6d ", (int)stbuf.st_size);
    printf(" %s ", entry_name);
    printf("\n");
  }

  loop_controls(going_up, file_count, &done, &i);
}

#endif
