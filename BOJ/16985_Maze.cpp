#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;

typedef struct _Node
{
    int row, col, h, cost;
} Node;

int answer = 2e9, cache[5][5][5];
int dir[3][6] = {{1,-1,0,0,0,0}, {0,0,1,-1,0,0}, {0,0,0,0,1,-1}};
vector<int> mylist;
vector<vector<vector<int>>> arr, arr2;

void Rotate(vector<vector<int>> &space)
{
    vector<vector<int>> temp(5, vector<int>(5));
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            temp[i][j] = space[4-j][i];
        }
    }
    space = temp;
}

void BFS()
{
    queue<Node> pq;
    if(arr2[0][0][0] == 1) {
        pq.push({0,0,0,0});
        cache[0][0][0] = 0;
    }

    while(!pq.empty()) {
        int row = pq.front().row;
        int col = pq.front().col;
        int h = pq.front().h;
        int cost = pq.front().cost;
        pq.pop();

        cost++;
        for(int i=0; i<6; i++) {
            int nr = row+dir[0][i];
            int nc = col+dir[1][i];
            int nh = h+dir[2][i];
            if(nr < 0 || nr > 4 || nc < 0 || nc > 4 || nh < 0 || nh > 4) {
                continue;
            } else if(arr2[nr][nc][nh] == 0) {
                continue;
            } else if(cache[nr][nc][nh] != -1) {
                continue;
            }
            cache[nr][nc][nh] = cost;
            pq.push({nr, nc, nh, cost});
        }
    }
}

void DFS(int index, int path, int cnt)
{
    if(cnt == 5) {
        for(int i=0; i<5; i++) {
            arr2[i] = arr[mylist[i]];
        }
        memset(cache, -1, 500);
        BFS();
        if(cache[4][4][4] != -1) {
            answer = min(answer, cache[4][4][4]);
        }
    } else {
        for(int i=0; i<5; i++) {
            if(!(path & (1<<i))) {
                mylist.push_back(i);
                DFS(i, path|(1<<i), cnt+1);
                mylist.pop_back();
            }
        }
    }
}

void Cal(int index)
{
    if(index == 5) {
        for(int i=0; i<5; i++) {
            mylist.push_back(i);
            DFS(i, 1<<i, 1);
            mylist.pop_back();
        }
    } else {
        Cal(index+1);
        for(int i=0; i<3; i++) {
            Rotate(arr[index]);
            Cal(index+1);
        }
    }
}

int main()
{
    arr.assign(5, vector<vector<int>>(5, vector<int>(5)));
    arr2.resize(5);

    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            for(int k=0; k<5; k++) {
                scanf("%d", &arr[i][j][k]);
            }
        }
    }

    Cal(0);
    if(answer == 2e9) {
        printf("-1\n");
    } else {
        printf("%d\n", answer);
    }
}