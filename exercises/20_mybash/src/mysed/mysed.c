#include "mysed.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_replace_command(const char *cmd, char **old_str, char **new_str) {
  // 检查输入参数有效性
  if (!cmd || !old_str || !new_str) {
    return -1;
  }

  // 初始化输出参数
  *old_str = NULL;
  *new_str = NULL;

  // TODO: 在这里添加你的代码
  char *second = strchr(cmd + 2, '/');

  *old_str = (char *)malloc(sizeof(char) * (second - cmd - 1));
  strncpy(*old_str, cmd + 2, second - cmd - 2);
  (*old_str)[second - cmd - 2] = '\0';

  *new_str = (char *)malloc(strlen(cmd) - (second - cmd + 1));
  strncpy(*new_str, second + 1, strlen(cmd) - (second - cmd + 1) - 1);
  (*new_str)[strlen(cmd) - (second - cmd + 1) - 1] = '\0';

  return 0;

  return 0;
}

void replace_first_occurrence(char *str, const char *old, const char *new) {
  // 检查输入参数有效性
  if (!str || !old || !new) {
    return;
  }

  // TODO: 在这里添加你的代码
  char *pos = strstr(str, old);
  if (pos) {
    char buffer[MAX_LINE_LENGTH];
    size_t prefix_len = pos - str;
    snprintf(buffer, sizeof(buffer), "%.*s%s%s", (int)prefix_len, str, new,
             pos + strlen(old));
    strncpy(str, buffer, MAX_LINE_LENGTH - 1);
    str[MAX_LINE_LENGTH - 1] = '\0';
  }
}

int __cmd_mysed(const char *rules, const char *str) {
  // 检查输入参数有效性
  if (!rules || !str) {
    fprintf(stderr, "Error: NULL rules or str parameter\n");
    return 1;
  }

  printf("rules: %s\n", rules);
  printf("str: %s\n", str);

  char *old_str = NULL;
  char *new_str = NULL;

  // 解析规则，例如 "s/old/new/"
  if (parse_replace_command(rules, &old_str, &new_str) != 0) {
    fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
    return 1;
  }

  if (!old_str || !new_str) {
    fprintf(stderr, "Error: Failed to parse old/new strings from rules\n");
    free(old_str);
    free(new_str);
    return 1;
  }

  // 复制原始字符串，因为我们可能会修改它（避免修改输入参数）
  char line[1024];
  strncpy(line, str, sizeof(line) - 1);
  line[sizeof(line) - 1] = '\0'; // 确保终止

  // 执行替换：在 line 中把 old_str 替换为 new_str（第一次出现）
  replace_first_occurrence(line, old_str, new_str);

  // 输出结果（建议加上换行，除非 str 本身带了）
  printf("%s\n", line);

  // 释放动态分配的内存
  free(old_str);
  free(new_str);

  return 0;
}
