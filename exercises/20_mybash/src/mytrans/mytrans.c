// mytrans.c
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myhash.h"

void trim(char *str) {
  if (str == NULL) {
    return;
  }

  /* 去掉前导空白 */
  char *start = str;
  while (*start && isspace((unsigned char)*start)) {
    start++;
  }
  if (start != str) {
    memmove(str, start, strlen(start) + 1);
  }

  /* 去掉尾部空白 */
  char *end = str + strlen(str) - 1;
  while (end >= str && isspace((unsigned char)*end)) {
    *end = '\0';
    end--;
  }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  // TODO: 在这里添加你的代码
  while (1) {
    if (!fgets(line, sizeof(line), file)) {
      break;
    }

    if (line[0] != '#') {
      continue;
    }
    strncpy(current_word, line + 1, sizeof(current_word) - 1);
    current_word[sizeof(current_word) - 1] = '\0';
    trim(current_word);

    if (!fgets(line, sizeof(line), file)) {
      break;
    }

    char *begin = strchr(line, ':');
    if (!begin) {
      continue;
    }
    begin++;

    strncpy(current_translation, begin, sizeof(current_translation) - 1);
    current_translation[sizeof(current_translation) - 1] = '\0';
    trim(current_translation);

    if (hash_table_insert(table, current_word, current_translation)) {
      (*dict_count)++;
    }
  }

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char *filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  uint64_t dict_count = 0;
  if (load_dictionary("src/mytrans/dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
      continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(line, " ");
    while (word != NULL) {
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
        printf("翻译: %s\n", translation);
      } else {
        printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}
