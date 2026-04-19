#include "doubly_circular_queue.h"

#include <stdlib.h>

// 使用两个哨兵节点：head 哨兵和 tail 哨兵，组成双向循环链表
// 初始化时创建哨兵节点
static link head_sentinel = NULL;
static link tail_sentinel = NULL;

void init_queue(void) {
    if (head_sentinel != NULL) {
        // 已经初始化，直接返回
        return;
    }
    // 创建哨兵节点
    head_sentinel = malloc(sizeof(*head_sentinel));
    tail_sentinel = malloc(sizeof(*tail_sentinel));

    // 建立双向循环关系
    head_sentinel->next = tail_sentinel;
    head_sentinel->prev = tail_sentinel;
    tail_sentinel->next = head_sentinel;
    tail_sentinel->prev = head_sentinel;
}

void destroy_queue(void) {
    if (head_sentinel == NULL) return;
    // 先用 destroy 清空所有数据节点
    destroy();
    // 然后释放哨兵节点
    free(head_sentinel);
    free(tail_sentinel);
    head_sentinel = NULL;
    tail_sentinel = NULL;
}

// 创建新节点
link make_node(int data) {
    link p = malloc(sizeof(*p));
    p->data = data;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(int key) {
    if (head_sentinel == NULL) return NULL;
    link p = head_sentinel->next;
    while (p != tail_sentinel) {
        if (p->data == key) return p;
        p = p->next;
    }
    return NULL;
}

// 在 head 之后插入（头插）
void insert(link p) {
    if (head_sentinel == NULL) init_queue();
    p->next = head_sentinel->next;
    p->prev = head_sentinel;
    head_sentinel->next->prev = p;
    head_sentinel->next = p;
}

// 删除指定节点
void delete(link p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;
}

// 遍历链表
void traverse(void (*visit)(link)) {
    if (head_sentinel == NULL) return;
    link p = head_sentinel->next;
    while (p != tail_sentinel) {
        visit(p);
        p = p->next;
    }
}

// 销毁整个链表
void destroy(void) {
    if (head_sentinel == NULL) return;
    link p = head_sentinel->next;
    while (p != tail_sentinel) {
        link next = p->next;
        free(p);
        p = next;
    }
    // 恢复哨兵节点的初始状态
    head_sentinel->next = tail_sentinel;
    head_sentinel->prev = tail_sentinel;
    tail_sentinel->next = head_sentinel;
    tail_sentinel->prev = head_sentinel;
}
