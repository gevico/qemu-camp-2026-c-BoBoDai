#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 16 LRU 缓存淘汰算法（哈希表 + 双向链表）
 *  - put(k,v)、get(k) 均为 O(1)
 *  - 容量满时淘汰最久未使用（LRU）的元素
 */

typedef struct LRUNode {
    int key;
    int value;
    struct LRUNode* prev;
    struct LRUNode* next;
} LRUNode;

typedef struct HashEntry {
    int key;
    LRUNode* node;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    int capacity;
    int size;
    LRUNode* head; /* 最近使用（MRU） */
    LRUNode* tail; /* 最久未使用（LRU） */
    /* 简单链式哈希表 */
    size_t bucket_count;
    HashEntry** buckets;
} LRUCache;

static unsigned hash_int(int key) {
    return (unsigned)(key * 31) % 1024;
}

static HashEntry* hash_find(LRUCache* c, int key, HashEntry*** pprev_next) {
    unsigned idx = hash_int(key) % c->bucket_count;
    HashEntry **prev = &c->buckets[idx];
    HashEntry *entry = c->buckets[idx];
    while (entry) {
        if (entry->key == key) {
            *pprev_next = prev;
            return entry;
        }
        prev = &entry->next;
        entry = entry->next;
    }
    return NULL;
}

static void list_add_to_head(LRUCache* c, LRUNode* node) {
    node->next = c->head->next;
    node->prev = c->head;
    c->head->next->prev = node;
    c->head->next = node;
}

static void list_remove(LRUCache* c, LRUNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static void list_move_to_head(LRUCache* c, LRUNode* node) {
    list_remove(c, node);
    list_add_to_head(c, node);
}

static LRUNode* list_pop_tail(LRUCache* c) {
    LRUNode *tail = c->tail->prev;
    if (tail == c->head) return NULL;
    list_remove(c, tail);
    return tail;
}

/* LRU 接口实现 */
static LRUCache* lru_create(int capacity) {
    LRUCache *c = malloc(sizeof(LRUCache));
    c->capacity = capacity;
    c->size = 0;
    c->bucket_count = 1024;
    c->buckets = calloc(c->bucket_count, sizeof(HashEntry *));
    c->head = malloc(sizeof(LRUNode));
    c->tail = malloc(sizeof(LRUNode));
    c->head->next = c->tail;
    c->tail->prev = c->head;
    return c;
}

static void lru_free(LRUCache* c) {
    LRUNode *p = c->head->next;
    while (p != c->tail) {
        LRUNode *next = p->next;
        free(p);
        p = next;
    }
    free(c->head);
    free(c->tail);
    for (size_t i = 0; i < c->bucket_count; i++) {
        HashEntry *e = c->buckets[i];
        while (e) {
            HashEntry *next = e->next;
            free(e);
            e = next;
        }
    }
    free(c->buckets);
    free(c);
}

static int lru_get(LRUCache* c, int key, int* out_value) {
    HashEntry **prev;
    HashEntry *entry = hash_find(c, key, &prev);
    if (!entry) return 0;
    *out_value = entry->node->value;
    list_move_to_head(c, entry->node);
    return 1;
}

static void lru_put(LRUCache* c, int key, int value) {
    HashEntry **prev;
    HashEntry *entry = hash_find(c, key, &prev);
    if (entry) {
        entry->node->value = value;
        list_move_to_head(c, entry->node);
        return;
    }
    if (c->size >= c->capacity) {
        LRUNode *tail = list_pop_tail(c);
        if (tail) {
            unsigned idx = hash_int(tail->key) % c->bucket_count;
            HashEntry **hprev = &c->buckets[idx];
            HashEntry *he = c->buckets[idx];
            while (he) {
                if (he->node == tail) {
                    *hprev = he->next;
                    free(he);
                    break;
                }
                hprev = &he->next;
                he = he->next;
            }
            free(tail);
            c->size--;
        }
    }
    LRUNode *node = malloc(sizeof(LRUNode));
    node->key = key;
    node->value = value;
    list_add_to_head(c, node);
    unsigned idx = hash_int(key) % c->bucket_count;
    entry = malloc(sizeof(HashEntry));
    entry->key = key;
    entry->node = node;
    entry->next = c->buckets[idx];
    c->buckets[idx] = entry;
    c->size++;
}

/* 打印当前缓存内容（从头到尾） */
static void lru_print(LRUCache* c) {
    LRUNode* p = c->head;
    int first = 1;
    while (p) {
        if (!first) printf(", ");
        first = 0;
        printf("%d:%d", p->key, p->value);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    /* 容量 3：put(1,1), put(2,2), put(3,3), put(4,4), get(2), put(5,5) */
    LRUCache* c = lru_create(3);
    if (!c) {
        fprintf(stderr, "创建 LRU 失败\n");
        return 1;
    }

    lru_put(c, 1, 1); /* 缓存：1 */
    lru_put(c, 2, 2); /* 缓存：2,1 */
    lru_put(c, 3, 3); /* 缓存：3,2,1 (满) */
    lru_put(c, 4, 4); /* 淘汰 LRU(1)，缓存：4,3,2 */

    int val;
    if (lru_get(c, 2, &val)) {
        /* 访问 2：缓存：2,4,3 */
        (void)val; /* 演示无需使用 */
    }

    lru_put(c, 5, 5); /* 淘汰 LRU(3)，缓存：5,2,4 */

    /* 期望最终键集合：{2,4,5}，顺序无关。此处按最近->最久打印：5:5, 2:2, 4:4 */
    lru_print(c);

    lru_free(c);
    return 0;
}
