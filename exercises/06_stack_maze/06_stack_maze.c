#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
    int row;
    int col;
} Position;

int visited[MAX_ROW][MAX_COL] = {0};
int prev_row[MAX_ROW][MAX_COL] = {0};
int prev_col[MAX_ROW][MAX_COL] = {0};

Position stack[MAX_ROW * MAX_COL];
int top = -1;

void push(Position p) { stack[++top] = p; }
Position pop(void) { return stack[top--]; }
int is_empty(void) { return top == -1; }

int main(void) {
    Position start = {0, 0};
    Position end = {MAX_ROW - 1, MAX_COL - 1};

    push(start);
    visited[0][0] = 1;
    prev_row[0][0] = -1;
    prev_col[0][0] = -1;

    int directions[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

    while (!is_empty()) {
        Position cur = pop();

        if (cur.row == end.row && cur.col == end.col) {
            Position path[MAX_ROW * MAX_COL];
            int count = 0;
            Position p = end;
            while (p.row != -1) {
                path[count++] = p;
                p = (Position){prev_row[p.row][p.col], prev_col[p.row][p.col]};
            }
            for (int i = 0; i < count; i++) {
                printf("(%d, %d)\n", path[i].row, path[i].col);
            }
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.row + directions[i][0];
            int nc = cur.col + directions[i][1];
            if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL
                && maze[nr][nc] == 0 && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                prev_row[nr][nc] = cur.row;
                prev_col[nr][nc] = cur.col;
                push((Position){nr, nc});
            }
        }
    }
    return 0;
}