#include <stdio.h>
#include <stdlib.h>

#include "circular_linked_list.h"

// 使用环形链表模拟约瑟夫环并打印出列顺序
static void josephus_problem(int n, int k, int m) {
    if (n <= 0 || k <= 0 || m <= 0) {
        printf("参数错误\n");
        return;
    }

    Node* head = create_circular_list(n);
    if (!head) {
        printf("\n");
        return;
    }

    // current 指向当前节点
    Node* current = head;
    // 找到起始位置第 k 个
    for (int i = 1; i < k; ++i) {
        current = current->next;
    }

    // 约瑟夫环出列
    while (n > 0) {
        // 数到第 m 个（移动 m-1 步）
        for (int i = 1; i < m; ++i) {
            current = current->next;
        }

        // current 指向要出列的人，打印
        printf("%d ", current->id);

        // 保存下一个节点
        Node* next_node = current->next;

        // 找到 current 的前一个节点
        Node* prev = head;
        while (prev->next != current) {
            prev = prev->next;
        }

        // 从环中删除 current
        prev->next = next_node;

        // 如果删除的是 head，需要更新 head
        if (current == head) {
            head = next_node;
        }

        // 释放节点
        free(current);
        current = next_node;
        n--;
    }

    printf("\n");
}

int main(void) {
    josephus_problem(5, 1, 2);  // 输出结果：2 4 1 5 3
    josephus_problem(7, 3, 1);  // 输出结果：3 4 5 6 7 1 2
    josephus_problem(9, 1, 8);  // 输出结果：8 7 9 2 5 4 1 6 3
    return 0;
}
