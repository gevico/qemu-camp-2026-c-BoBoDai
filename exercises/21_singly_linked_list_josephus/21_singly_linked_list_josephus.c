#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

void print_item(link p) { printf("%d ", p->item); }

static void create_list(int n) {
    if (n <= 0) return;
    destroy();

    // 创建有序链表：1->2->3->...->n
    // 使用数组存储节点，然后连接
    link* nodes = malloc(n * sizeof(link));
    for (int i = 0; i < n; i++) {
        nodes[i] = make_node(i + 1);
    }
    // 连接
    for (int i = 0; i < n - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    nodes[n - 1]->next = NULL;

    // 由于 insert 在头部插入，我们直接把 nodes[0] 作为 head
    // 但 head 是 static 的，不能直接访问
    // 所以我们用 insert 插入 nodes[0]，然后断开它后面多余的连接

    // 更好的方法：逆序插入然后不用环绕
    // 但约瑟夫环需要环绕，所以我们需要构造一个环

    // 最终方案：创建逆序链表，然后 josephus 时从 tail 开始数
    for (int i = n; i >= 1; i--) {
        insert(make_node(i));
    }
    // 现在链表是 n->n-1->...->1
    // 找到 tail
    link tail = get_head();
    while (tail->next != NULL) tail = tail->next;
    // tail->next = get_head(); // 形成环 - 暂时不形成环，用模拟环绕的方式
    free(nodes);
}

void josephus_problem(int n, int k, int m) {
    if (n <= 0 || k <= 0 || m <= 0) return;

    create_list(n);

    // 由于是逆序链表 n->n-1->...->1
    // 我们需要从 tail 开始数来得到正确的顺序
    // 找到 tail（next 为 NULL 的节点）
    link tail = get_head();
    while (tail->next != NULL) tail = tail->next;
    // 从 tail 开始，移动 k-1 步到达第 k 个节点（真正的起始位置）
    link current = tail;
    for (int i = 0; i < k - 1; i++) {
        current = current->next;
    }

    while (n > 0) {
        for (int i = 0; i < m - 1; i++) {
            current = current->next;
            if (current == NULL) current = get_head();
        }

        print_item(current);

        // 找前一个
        link prev = get_head();
        while (prev->next != current) prev = prev->next;

        prev->next = current->next;
        link next = current->next;
        free_node(current);
        current = next;
        if (current == NULL) current = get_head();
        n--;
    }
    printf("\n");
}

int main(void) {
    josephus_problem(5, 1, 2);
    josephus_problem(7, 3, 1);
    josephus_problem(9, 1, 8);
    return 0;
}
