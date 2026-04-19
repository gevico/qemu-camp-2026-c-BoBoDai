#ifndef DOUBLY_CIRCULAR_QUEUE_H
#define DOUBLY_CIRCULAR_QUEUE_H

typedef struct node *link;
struct node
{
    int data;
    link prev, next;
};

// 创建新节点
link make_node(int data);
// 释放节点
void free_node(link p);
// 查找节点
link search(int key);
// 在 head 之后插入（头插）
void insert(link p);
// 删除指定节点
void delete(link p);
// 遍历链表
void traverse(void (*visit)(link));
// 销毁整个链表
void destroy(void);
// 初始化队列
void init_queue(void);
// 销毁队列
void destroy_queue(void);

#endif // DOUBLY_CIRCULAR_QUEUE_H
