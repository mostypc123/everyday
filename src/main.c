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

  } else if (
    !(
      strcmp("--help", argv[1]) || strcmp("help", argv[1]) || strcmp("-h", argv[1])
    )
  ) {

    puts(
      "Usage:\n"
      "  everyday package <stage directory> <package version> <package name> [options]\n"
      "  everyday gnuftp <package name> <package version> <file extension>\n"
      "  everyday rrclone <repository name>\n"
      "  everyday <task name>\n"
      "\n"
      "Commands:\n"
      "  package    Create a Car package archive and a package list entry.\n"
      "  gnuftp     Generate a GNU FTP URL for a package.\n"
      "  rrclone    Clone a GitHub repository from the Redrose Linux organization.\n"
      "  <task>     Execute a task from EVERYDAY_TASKS_DIR (default: /var/everyday).\n"
      "\n"
      "Package options:\n"
      "  --pre-url=<url>   Specify the base URL where the package files are hosted.\n"
      "                    Example: --pre-url=https://smth.org/pkg/\n"
      "  --push[=<url>]    Push the package to a repository. The repository URL is\n"
      "                    optional and can be omitted to use the default.\n"
      "  --update          Update an existing package. When Vim opens, copy the\n"
      "                    existing package list entry and edit it accordingly.\n"
      "\n"
      "Examples:\n"
      "  make install DESTDIR=$PWD/stage && everyday package stage 1.0 my-awesome-package\n"
      "  everyday package stage 1.0 my-awesome-package --pre-url=https://smth.org/pkg/\n"
      "  everyday package stage 1.0 my-awesome-package --push\n"
      "  everyday gnuftp binutils 2.47 .tar.zst\n"
      "  wget $(everyday gnuftp binutils 2.47 .tar.zst)\n"
      "  everyday rrclone car\n"
      "\n"
      "Notes:\n"
      "  gnuftp automatically removes a trailing dot from the file extension.\n"
      "  gnuftp does not check whether the requested package exists.\n"
      "  rrclone only supports repositories belonging to the Redrose Linux organization.\n"
      "  Tasks are executables located in EVERYDAY_TASKS_DIR and receive ARGS\n"
      "  as their arguments.\n"
      "  EVERYDAY_TASKS_DIR defaults to /var/everyday and does not support\n"
      "  PATH-like ':'-separated directory lists.\n"
    );

  } else {

    if (exec_task(argv[1]) == -2) {
      printf("unknown arg or task %s\ncheck --help", argv[1]);
      return 2;
    }
    return 0;
  }
}
