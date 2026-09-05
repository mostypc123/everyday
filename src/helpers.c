#define  _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

char* run_cmd(const char *cmd) {
  printf("> %s\n", cmd);

  char full[1024];
  snprintf(full, sizeof(full), "%s 2>&1", cmd);

  FILE *fp = popen(full, "r");
  if (!fp) FAILED_ALLOC();

  size_t cap = 4096, len = 0;
  char *buf = malloc(cap);
  if (!buf) { pclose(fp); FAILED_ALLOC(); }

  size_t n;
  while ((n = fread(buf + len, 1, cap - len, fp)) > 0) {
    len += n;
    if (len == cap) {
      cap *= 2;
      char *tmp = realloc(buf, cap);
      if (!tmp) { free(buf); pclose(fp); FAILED_ALLOC(); }
      buf = tmp;
    }
  }
  buf[len] = '\0';

  pclose(fp);
  return buf;
}

void first_word(char* s) {
  char* p = s;
  while (p) {
    if (*p == ' ') {
      *p = '\0';
      break;
    }
    p++;
  }
}

void panic(const char* msg) {
  puts(msg);
  exit(1);
}

