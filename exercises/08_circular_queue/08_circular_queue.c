#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

void init(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool is_empty(Queue *q) {
    return q->count == 0;
}

bool is_full(Queue *q) {
    return q->count == MAX_PEOPLE;
}

void enqueue(Queue *q, People p) {
    if (!is_full(q)) {
        q->data[q->tail] = p;
        q->tail = (q->tail + 1) % MAX_PEOPLE;
        q->count++;
    }
}

People dequeue(Queue *q) {
    People p = q->data[q->head];
    q->head = (q->head + 1) % MAX_PEOPLE;
    q->count--;
    return p;
}

int main() {
    Queue q;
    int total_people = 50;
    int report_interval = 5;

    init(&q);

    for (int i = 1; i <= total_people; i++) {
        People p = {i};
        enqueue(&q, p);
    }

    int count = 1;
    while (q.count > 1) {
        People p = dequeue(&q);
        if (count % report_interval == 0) {
            printf("淘汰: %d\n", p.id);
        } else {
            enqueue(&q, p);
        }
        count++;
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}