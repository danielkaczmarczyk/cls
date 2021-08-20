#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
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

#endif
