#pragma once

int package(
  const char* dir, const char* ver, const char* pkgname, const char* preurl,
  const _Bool push_to_git, const char* override_git_repo
);

void print_gnu_ftp_url(
  const char* package, const char* version, char* ext
);

char* make_pkglist_entry(
  const char *pkgname, const char *buf2, const char *sha256, const char *ver
);

