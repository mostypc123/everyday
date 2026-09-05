#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "helpers.h"
#include "package.h"

char* make_pkglist_entry(
  const char *pkgname, const char *buf2, const char *sha256, const char *ver
) {
  const char *separator = " - ";
  const char *ver_ = "version ";
  size_t size =
    (strlen(separator) * 2) + strlen(pkgname) + strlen(buf2) +
    strlen(sha256) + strlen(ver_) + strlen(ver) + 3;
  char *out = malloc(size);
  if (!out) FAILED_ALLOC();
  snprintf(
    out, size, "%s%s%s%s%s\n%s%s\n", pkgname, separator, buf2,
    separator, sha256, ver_, ver
  );
  return out;
}

int package(
  const char* dir, const char* ver, const char* pkgname, const char* preurl,
  const _Bool push_to_git, const char* override_git_repo
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
    return 1;
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

  char* pkglist_entry = make_pkglist_entry(pkgname, buf2, sha256, ver);
  printf("%s", pkglist_entry);

  if (push_to_git) {
    const char* repo = override_git_repo ? override_git_repo :
      "https://github.com/redroselinux/car3-pkgs";

    printf("\npushing to %s\npress enter to continue", repo);
    (void)getchar();

    const char* prefix = "git clone --depth 1 ";
    char* suffix = " .packages_repo/";
    char command[strlen(prefix) + strlen(repo) + strlen(suffix) + 1];
    snprintf(command, sizeof(command), "%s%s%s", prefix, repo, suffix);
    suffix = ".packages_repo/";

    if (system(command) != 0) {
      puts("failed to clone");
      return 1;
    }

    char archive_name[strlen(pkgname) + strlen(suffix1) + 1];
    snprintf(archive_name, sizeof(archive_name), "%s%s", pkgname, suffix1);

    char new_path[strlen(suffix) + strlen(archive_name) + 1];
    snprintf(new_path, sizeof(new_path), "%s%s", suffix, archive_name);

    const char* readme = "README";
    char pkglist_path[strlen(suffix) + strlen(readme) + 1];
    snprintf(pkglist_path, sizeof(pkglist_path), "%s%s", suffix, readme);

    if (rename(archive_name, new_path) != 0) {
      puts("failed to move package archive");
      return 1;
    }

    FILE* fptr = fopen(pkglist_path, "a");
    if (!fptr) {
      puts("failed to open pkglist");
      return 1;
    }

    fprintf(fptr, "\n%s", pkglist_entry);

    fclose(fptr);

    if (system(
      "cd .packages_repo && git add . && git commit -m 'automatic addition "
      "of package using mostypc123/everyday' && git push") != 0
    ) {
      puts("failed to push");
      return 1;
    }

    if (system("rm -rf .packages_repo") != 0) {
      puts("failed to delete clone");
      return 1;
    }
  }
  
  free(pkglist_entry);
  free(sha256);

  return 0;
}

void print_gnu_ftp_url(const char* package, const char* version, char* ext) {
  if (ext[0] == '.') {
    // remove trailing dot
    strcpy(ext, ext+1);
  }

  printf(
    "https://ftp.gnu.org/gnu/%s/%s-%s.%s\n", package, package, version, ext
  );
}

