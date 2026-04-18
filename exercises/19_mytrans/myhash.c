// hash_table.c
#include "myhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// djb2 哈希函数（经典字符串哈希，分布均匀）
unsigned long hash_function(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash;
}

// 创建哈希表
HashTable *create_hash_table() {
  HashTable *table = malloc(sizeof(HashTable));
  if (!table)
    return NULL;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

// 释放单个节点
void free_node(HashNode *node) {
  if (node) {
    free(node->key);
    free(node->value);
    free(node);
  }
}

// 释放整个哈希表
void free_hash_table(HashTable *table) {
  if (!table)
    return;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *curr = table->buckets[i];
    while (curr) {
      HashNode *tmp = curr;
      curr = curr->next;
      free_node(tmp);
    }
  }
  free(table);
}

// 插入键值对
int hash_table_insert(HashTable *table, const char *key, const char *value) {
  if (!table || !key || !value)
    return 0;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = malloc(sizeof(HashNode));
  node->key = strdup(key);
  node->value = strdup(value);
  node->next = table->buckets[hash];
  table->buckets[hash] = node;

  return 1;
}

// 查找键
const char *hash_table_lookup(HashTable *table, const char *key) {
  if (!table || !key)
    return NULL;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[hash];

  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node->value;
    }
    node = node->next;
  }

  return NULL; // 未找到
}

// 加载词典
int load_dictionary(const char *filename, HashTable *table, uint64_t* dict_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    char line[1024];
    char *key = NULL;
    *dict_count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '#') {
            // 去掉换行符
            line[strcspn(line, "\n")] = '\0';
            key = strdup(line + 1);  // 跳过 #
        } else if (strncmp(line, "Trans:", 6) == 0) {
            if (key != NULL) {
                char *value = line + 6;
                while (*value == ' ' || *value == ':') value++;
                value[strcspn(value, "\n")] = '\0';
                hash_table_insert(table, key, value);
                (*dict_count)++;
                free(key);
                key = NULL;
            }
        }
    }

    fclose(file);
    return 0;
}
