#pragma once

char* run_cmd(const char *cmd);
void first_word(char* s);
void panic(const char* msg);

#define FAILED_ALLOC() panic("failed to alloc memory");
