#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Point
{
    int row, col;
} Point;
typedef struct _Node
{
    int num, state, row, col;
} Node;

int n, m, arr[8][8], len, answer = 2e9;
Point dir[4] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
vector<Node> cctv;

bool IsValid(int row, int col)
{
    return (0 <= row && row < n && 0 <= col && col < m) ? true : false;
}

void Move(int row, int col, int where)
{
    while(IsValid(row, col) && arr[row][col] != 6) {
        if(arr[row][col] == 0) {
            arr[row][col] = -1;
        }
        row += dir[where].row;
        col += dir[where].col;
    }
}

void Coloring()
{
    for(int i=0; i<len; i++) {
        int row = cctv[i].row;
        int col = cctv[i].col;
        int num = cctv[i].num;
        int state = cctv[i].state;

        switch(num) {
            case 1:
                switch(state) {
                    case 0: Move(row, col, 0); break;
                    case 1: Move(row, col, 1); break;
                    case 2: Move(row, col, 2); break;
                    case 3: Move(row, col, 3); break;
                } break;
            case 2: 
                switch(state) {
                    case 0: Move(row, col, 0); Move(row, col, 2); break;
                    case 1: Move(row, col, 1); Move(row, col, 3); break;
                } break;
            case 3: 
                switch(state) {
                    case 0: Move(row, col, 0); Move(row, col, 1); break;
                    case 1: Move(row, col, 1); Move(row, col, 2); break;
                    case 2: Move(row, col, 2); Move(row, col, 3); break;
                    case 3: Move(row, col, 3); Move(row, col, 0); break;
                } break;
            case 4: 
                switch(state) {
                    case 0: Move(row, col, 0); Move(row, col, 1); Move(row, col, 2); break;
                    case 1: Move(row, col, 1); Move(row, col, 2); Move(row, col, 3); break;
                    case 2: Move(row, col, 2); Move(row, col, 3); Move(row, col, 0); break;
                    case 3: Move(row, col, 3); Move(row, col, 0); Move(row, col, 1); break;
                } break;
            case 5: 
                switch(state) {
                    case 0: Move(row, col, 0); Move(row, col, 1); Move(row, col, 2); Move(row, col, 3); break;
                } break;
        }
    }
}

int Counting()
{
    int result = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(arr[i][j] == 0) {
                result++;
            }
        }
    }
    return result;
}

void Reversing()
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(arr[i][j] == -1) {
                arr[i][j] = 0;
            }
        }
    }
}

void DFS(int index)
{
    if(index == len) {
        Coloring();
        answer = min(answer, Counting());
        Reversing();
    } else {
        for(int i=0; i<4; i++) {
            if(cctv[index].num == 5 && i > 0) {
                continue;
            } else if(cctv[index].num == 2 && i > 1) {
                continue;
            } else {
                cctv[index].state = i;
                DFS(index+1);
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &arr[i][j]);
            if(1 <= arr[i][j] && arr[i][j] <= 5) {
                cctv.push_back({arr[i][j], 0, i, j});
            }
        }
    }

    len = cctv.size();
    DFS(0);
    printf("%d\n", answer);
}