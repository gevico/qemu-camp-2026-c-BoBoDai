#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 获取头指针（供外部文件使用）
link get_head(void) {
    return head;
}

// 创建新节点
link make_node(unsigned char item) {
    link p = malloc(sizeof(*p));
    p->item = item;
    p->next = NULL;
    return p;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    link p = head;
    while (p != NULL) {
        if (p->item == key) return p;
        p = p->next;
    }
    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    p->next = head;
    head = p;
}

// 删除指定节点
void delete(link p) {
    if (p == head) {
        head = head->next;
        return;
    }
    link prev = head;
    while (prev != NULL && prev->next != p) {
        prev = prev->next;
    }
    if (prev != NULL) {
        prev->next = p->next;
    }
}

// 遍历链表
void traverse(void (*visit)(link)) {
    link p = head;
    while (p != NULL) {
        visit(p);
        p = p->next;
    }
}

// 销毁整个链表
void destroy(void) {
    link p = head;
    while (p != NULL) {
        link next = p->next;
        free(p);
        p = next;
    }
    head = NULL;
}

// 在链表头部推入节点
void push(link p) {
    insert(p);
}

// 从链表头部弹出节点
link pop(void) {
    if (head == NULL) return NULL;
    link p = head;
    head = head->next;
    return p;
}

// 释放链表内存
void free_list(link list_head) {
    link p = list_head;
    while (p != NULL) {
        link next = p->next;
        free(p);
        p = next;
    }
}
