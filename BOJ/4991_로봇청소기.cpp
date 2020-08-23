#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct _Point
{
    int row, col;
} Point;
typedef struct _Node
{
    int row, col, cost;
} Node;

int n, m, answer, visit[21][21], dist[21][21][21][21], visited[11];
char arr[21][21];
Point start, dir[4] = {{1,0},{-1,0},{0,1},{0,-1}};
vector<Point> mylist;

void InitVisit()
{
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            visit[i][j] = 0;
        }
    }
}

void InitDist()
{
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            for(int k=1; k<=n; k++) {
                for(int p=1; p<=m; p++) {
                    dist[i][j][k][p] = 0;
                }
            }
        }
    }
}

void BFS(int index)
{
    queue<Node> pq;
    pq.push({mylist[index].row, mylist[index].col, 0});

    while(!pq.empty()) {
        int row = pq.front().row;
        int col = pq.front().col;
        int cost = pq.front().cost;
        pq.pop();

        if(row < 1 || row > n || col < 1 || col > m) {
            continue;
        } else if(visit[row][col] == 1) {
            continue;
        } else if(arr[row][col] == 'x') {
            continue;
        }
        visit[row][col] = 1;
        if(arr[row][col] == '*') {
            dist[mylist[index].row][mylist[index].col][row][col] = cost;
        }

        for(int i=0; i<4; i++) {
            int nextrow = row+dir[i].row;
            int nextcol = col+dir[i].col;
            pq.push({nextrow, nextcol, cost+1});
        }
    }
}

void DFS(int index, int cost, int cnt)
{
    if(cnt == mylist.size()) {
        answer = min(answer, cost);
        return;
    } else {
        int len = mylist.size();
        for(int i=0; i<len; i++) {
            if(visited[i] == 0) {
                visited[i] = 1;
                DFS(i, cost+dist[mylist[index].row][mylist[index].col][mylist[i].row][mylist[i].col], cnt+1);
                visited[i] = 0;
            }
        }
    }
}

bool IsValid()
{
    int len = mylist.size();
    for(int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            if(i == j) {
                continue;
            } else if(mylist[j].row == start.row && mylist[j].col == start.col) {
                continue;
            }
            if(dist[mylist[i].row][mylist[i].col][mylist[j].row][mylist[j].col] == 0) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    while(1) {
        scanf("%d %d", &m, &n);
        if(n == 0 && m == 0) {
            break;
        }
        mylist.clear();
        answer = 2e9;
        
        for(int i=1; i<=n; i++) {
            getchar();
            for(int j=1; j<=m; j++) {
                arr[i][j] = getchar();
                if(arr[i][j] == 'o') {
                    start = {i, j};
                    mylist.push_back({i, j});
                } else if(arr[i][j] == '*') {
                    mylist.push_back({i, j});
                }
            }
        }

        InitDist();
        int len = mylist.size();
        for(int i=0; i<len; i++) {
            InitVisit();
            BFS(i);
        }

        if(!IsValid()) {
            printf("-1\n");
            continue;
        }

        for(int i=0; i<len; i++) {
            visited[i] = 0;
            if(mylist[i].row == start.row && mylist[i].col == start.col) {
                visited[i] = 1;
            }
        }
        for(int i=0; i<len; i++) {
            if(visited[i] == 0) {
                visited[i] = 1;
                DFS(i, dist[start.row][start.col][mylist[i].row][mylist[i].col], 2);
                visited[i] = 0;
            }
        }

        if(answer == 2e9) {
            printf("0\n");
        } else {
            printf("%d\n", answer);
        }
    }
}