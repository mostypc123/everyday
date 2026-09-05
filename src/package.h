#pragma once

int package(
  const char* dir, const char* ver, const char* pkgname, const char* preurl
);

void print_gnu_ftp_url(
  const char* package, const char* version, char* ext
);

