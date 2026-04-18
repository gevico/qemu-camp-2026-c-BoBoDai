#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->tree_node = tree_node;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

TreeNode* dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    QueueNode *node = q->front;
    TreeNode *tree_node = node->tree_node;
    q->front = node->next;
    if (q->front == NULL) q->rear = NULL;
    free(node);
    return tree_node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if (size == 0) return NULL;
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = level_order[0];
    root->left = root->right = NULL;

    Queue *q = create_queue();
    enqueue(q, root);

    int i = 1;
    while (!is_empty(q) && i < size) {
        TreeNode *node = dequeue(q);

        if (i < size && level_order[i] != INT_MIN) {
            node->left = (TreeNode*)malloc(sizeof(TreeNode));
            node->left->val = level_order[i];
            node->left->left = node->left->right = NULL;
            enqueue(q, node->left);
        }
        i++;

        if (i < size && level_order[i] != INT_MIN) {
            node->right = (TreeNode*)malloc(sizeof(TreeNode));
            node->right->val = level_order[i];
            node->right->left = node->right->right = NULL;
            enqueue(q, node->right);
        }
        i++;
    }

    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    if (root == NULL) return;
    TreeNode *stack[100];
    int top = -1;
    stack[++top] = root;
    while (top >= 0) {
        TreeNode *node = stack[top--];
        printf("%d ", node->val);
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
