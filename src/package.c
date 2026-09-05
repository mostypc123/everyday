#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "helpers.h"
#include "package.h"

int package(
  const char* dir, const char* ver, const char* pkgname, const char* preurl
) {
  struct stat st;

  if (stat(dir, &st) != 0) {
    printf("%s does not exist\n", dir);
    return 2;
  }

  if (!S_ISDIR(st.st_mode)) {
    printf("%s is not a dir\n", dir);
    return 2;
  }

  char carfile_path[strlen(dir) + 5]; // 5 = /car\0
  snprintf(carfile_path, sizeof(carfile_path), "%s/car", dir);

  FILE* carfile = fopen(carfile_path, "w");
  if (!carfile) {
    printf("failed to open %s\n", carfile_path);
    perror("fopen");
  }

  fprintf(carfile, "version %s", ver);

  fclose(carfile);
  
  const char* prefix = "fakeroot tar -I zstd -cf ";
  const char* suffix1 = ".tar.zst";
  const size_t size =
    strlen(prefix) + strlen(suffix1) + strlen(dir) + strlen(pkgname) + 2;
  char buf[size];
  snprintf(buf, size, "%s%s%s %s", prefix, pkgname, suffix1, dir);
  run_cmd(buf);

  char shacmd[strlen(pkgname) + strlen(suffix1) + 16];
  snprintf(shacmd, sizeof(shacmd), "sha256sum %s%s", pkgname, suffix1);
  char* sha256 = run_cmd(shacmd);
  first_word(sha256);

  printf("- preurl is set to %s\n", preurl);
  printf("- packagelist entry:\n\n");
  
  const size_t size2 = 
    strlen(pkgname) + strlen(preurl) + strlen(suffix1) + strlen(dir) + 3;
  char buf2[size2];
  snprintf(buf2, size2, "%s%s%s", preurl, pkgname, suffix1);

  printf("%s - %s - %s\n", pkgname, buf2, sha256);
  printf("version %s\n", ver);
  
  free(sha256);

  return 0;
}

void print_gnu_ftp_url(const char* package, const char* version, char* ext) {
  if (ext[0] == '.') {
    // remove trailing dot
    strcpy(ext, ext+1);
  }

  printf("https://ftp.gnu.org/gnu/%s/%s-%s.%s\n", package, package, version, ext);
}

