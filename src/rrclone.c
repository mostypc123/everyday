#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int rrclone(const char* repo) {
  const char* prefix = "git clone --depth 1 https://github.com/redroselinux/";
  char buf[strlen(prefix) + strlen(repo) + 1];
  snprintf(buf, sizeof(buf), "%s%s", prefix, repo);

  return system(buf);
}
