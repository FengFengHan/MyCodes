#include <stdio.h>

//#define CAN_NOT_ACCESS 1
//#define CAN_ACCESS 0


char s[110];
int N, M;
//maze[][][0] save maze
//maze[][][1] save numbers of changed after heads right
//maze[][][2] save numbers of changed after heads down
int maze[110][110][3];

int min(int a, int b) {
    if (a > b) return b;
    else return a;
}
void checkMaze(int x, int y) {
    if (x == 0 && y == 0) {
        maze[y][x][1] = !maze[y][x][0];
        maze[y][x][2] = maze[y][x][1] + 1;
        return;
    }

    if (y == 0) {
        maze[y][x][1] = maze[y][x - 1][1] + maze[y][x][0];
        maze[y][x][2] = maze[y][x][1] + !(maze[y][x + 1][0]);
        return;
    }


    if (x == 0) {
        maze[y][x][2] = maze[y - 1][x][2] + maze[y][x][0];
        maze[y][x][1] = maze[y][x][2] + !(maze[y+1][x][0]);
        return;
    }


    int from_top_then_head_down = maze[y - 1][x][2] + maze[y][x][0];
    int from_top_then_head_right = from_top_then_head_down + !(maze[y + 1][x][0]);
    int from_left_then_head_right = maze[y][x - 1][1] +maze[y][x][0];
    int from_left_then_head_down = from_left_then_head_right + !(maze[y][x + 1][0]);

    maze[y][x][1] = min(from_top_then_head_right, from_left_then_head_right);
    maze[y][x][2] = min(from_top_then_head_down, from_left_then_head_down);

    return;

}

int main(void) {

    int i, j;

    while (scanf("%d %d", &N, &M) != EOF) {

        for (i = 0; i < 110; i++) {
            for (j = 0; j < 110; j++) {
                maze[i][j][0] = 1;
            }
        }

        for (i = 0; i < N; i++) {
            scanf("%s", s);
            for (j = 0; j < M; j++) {
                if (s[j] == '.') maze[i][j][0] = 0;
            }
        }

        for (int x_add_y = 0; x_add_y < N + M - 1; x_add_y++) {
            if (x_add_y < M) {
                int x = x_add_y;
                int y = 0;
                for (; x >= 0 && y < N; x--, y++) {
                    checkMaze(x, y);
                }
            }
            else {
                int x = M - 1;
                int y = x_add_y - x;
                for (; x >= 0 && y < N; x--, y++) {
                    checkMaze(x, y);
                }
            }
        }
        printf("%d\n", min(maze[N - 1][M - 1][1], maze[N - 1][M - 1][2]));
    }

    return 0;

}