#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef struct _Node
{
    int row, col, cost;
} Node;

int n, m, arr[51][51], cache[51][51], answer = 2e9;
int dir[2][4] = {{0,0,1,-1}, {1,-1,0,0}};
vector<Node> mylist, bfslist;

void Init()
{
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cache[i][j] = -1;
        }
    }
}

int BFS()
{
    queue<Node> pq;
    for(int i=0; i<m; i++) {
        pq.push(bfslist[i]);
    }

    while(!pq.empty()) {
        int row = pq.front().row;
        int col = pq.front().col;
        int cost = pq.front().cost;
        pq.pop();

        if(row < 1 || row > n || col < 1 || col > n) {
            continue;
        } else if(cache[row][col] != -1) {
            continue;
        } else if(arr[row][col] == 1) {
            continue;
        }
        cache[row][col] = cost;

        for(int i=0; i<4; i++) {
            int nextrow = row + dir[0][i];
            int nextcol = col + dir[1][i];
            pq.push({nextrow, nextcol, cost+1});
        }
    }

    int result = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(cache[i][j] == -1) {
                if(arr[i][j] != 1) {
                    return 2e9;
                }
            } else {
                result = max(result, cache[i][j]);
            }
        }
    }
    return result;
}

void DFS(int index, int cnt)
{
    if(cnt == m) {
        Init();
        answer = min(answer, BFS());
    } else {
        for(int i=index+1; i<mylist.size(); i++) {
            bfslist.push_back(mylist[i]);
            DFS(i, cnt+1);
            bfslist.pop_back();
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            scanf("%d", &arr[i][j]);
            if(arr[i][j] == 2) {
                arr[i][j] = 0;
                mylist.push_back({i, j, 0});
            }
        }
    }

    for(int i=0; i<mylist.size(); i++) {
        bfslist.push_back(mylist[i]);
        DFS(i, 1);
        bfslist.pop_back();
    }
    if(answer == 2e9) {
        printf("-1\n");
    } else {
        printf("%d\n", answer);
    }
}