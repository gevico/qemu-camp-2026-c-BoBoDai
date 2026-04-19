#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

void print_item(link p) { printf("%d ", p->item); }

void josephus_problem(int n, int k, int m) {
    if (n <= 0 || k <= 0 || m <= 0) return;

    // Use array-based approach for simplicity and correctness
    int *next = malloc((n + 1) * sizeof(int));  // 1-indexed

    // Build circle: 1->2->3->...->n->1
    for (int i = 1; i <= n; i++) {
        next[i] = i + 1;
    }
    next[n] = 1;

    // Start at k-th node
    int current = k;

    while (n > 0) {
        // Count m-1 steps to reach the node to eliminate
        for (int i = 0; i < m - 1; i++) {
            current = next[current];
        }

        // Print the node to eliminate
        printf("%d ", current);

        // Find predecessor of current
        int prev = 1;
        while (next[prev] != current) prev = next[prev];

        // Remove current from circle
        next[prev] = next[current];
        current = next[current];
        n--;
    }

    free(next);
    printf("\n");
}

int main(void) {
    josephus_problem(5, 1, 2);
    josephus_problem(7, 3, 1);
    josephus_problem(9, 1, 8);
    return 0;
}
