#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "package.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    puts("not enough args");
    return 2;
  }

  if (!strcmp("package", argv[1])) {
    if (argc < 5) {
      puts("usage: everyday package <dir> <pkgver> <pkgname>");
      return 2;
    }

    char* preurl =
      "https://github.com/redroselinux/car3-pkgs/raw/refs/heads/main/";
    _Bool need_to_free_preurl = 0;

    if (argc == 6) {
      if (!strncmp("--pre-url=", argv[5], 10)) {
        preurl = strdup(&argv[5][10]);
        need_to_free_preurl = 1;
      }
    }

    int result = package(argv[2], argv[3], argv[4], preurl);

    if (need_to_free_preurl) free(preurl);

    return result;
  } else {
    printf("unknown arg %s\n", argv[1]);
    return 2;
  }
}
