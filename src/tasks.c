#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int exec_task(const char* name) {
  char* everyday_path = getenv("EVERYDAY_TASKS_DIR");
  if (!everyday_path) {
    everyday_path = "/var/everyday";
  }

  char* everyday_task_args = getenv("TASK_ARGS");
  if (!everyday_task_args) {
    everyday_task_args = "";
  }

  const size_t task_path_format_size = strlen(everyday_path) + strlen(name) + 2;
  char task_path_format[task_path_format_size];
  snprintf(
    task_path_format, task_path_format_size, "%s/%s", everyday_path, name
  );

  if (access(task_path_format, F_OK) != 0) {
    return -2;
  }

  printf("- running task %s\n\n", name);

  const size_t task_cmd_format_size =
    task_path_format_size + strlen(everyday_task_args) + 2;
  char task_cmd_format[task_path_format_size];
  snprintf(
    task_cmd_format, task_cmd_format_size, "%s %s",
    task_path_format, everyday_task_args
  );

  return system(task_cmd_format);
}

