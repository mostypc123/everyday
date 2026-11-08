#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "package.h"
#include "rrclone.h"
#include "tasks.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    puts("not enough args");
    return 2;
  }

  if (!strcmp("package", argv[1])) {

    if (argc < 5) {
      puts("usage: everyday package <dir> <pkgver> <pkgname> [--pre-url=...] [--push=...] [--update]");
      return 2;
    }

    char* preurl =
      "https://github.com/redroselinux/car3-pkgs/raw/refs/heads/main/";
    _Bool need_to_free_preurl = 0;

    char* override_repo = NULL;
    _Bool need_to_free_override_repo = 0;

    _Bool push = 0;
    _Bool update = 0;

    for (int i = 1; i < argc; i++) {
      const char* arg = argv[i];

      if (!strncmp("--pre-url=", arg, 10)) {
        preurl = strdup(&arg[10]);
        need_to_free_preurl = 1;
      }

      if (!strncmp("--push", arg, 6)) {
        push = 1;
        if (strlen(arg) > 6 && arg[7] == '=') override_repo = strdup(&arg[7]);
      }

      if (!strcmp("--update", arg)) {
        update = 1;
      }
    }

    int result = package(
      argv[2], argv[3], argv[4], preurl, push, update, override_repo
    );

    if (need_to_free_preurl) free(preurl);
    if (need_to_free_override_repo) free(override_repo);

    return result;

  } else if (!strcmp("gnuftp", argv[1])) {

    if (argc < 5) {
      puts("usage: everyday gnuftp <package> <pkgver> <fileext>");
      return 2;
    }

    print_gnu_ftp_url(argv[2], argv[3], argv[4]);
    return 0;

  } else if (!strcmp("rrclone", argv[1])) {

    if (argc < 3) {
      puts("usage: everyday rrclone <repo>");
      return 2;
    }

    return rrclone(argv[2]);

  } else {

    if (exec_task(argv[1]) == -2) {
      printf("unknown arg or task %s\n", argv[1]);
      return 2;
    }
    return 0;
  }
}
