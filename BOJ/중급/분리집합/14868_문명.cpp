#include <iostream>
#include <queue>
using namespace std;

typedef struct _Node
{
    int row, col;
} Node;
typedef struct _Point
{
    int row, col, cost;
} Point;

int n, k, cnt = 0;
int parent[100001];
int arr[2001][2001];
Node dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void Print()
{
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int Find(int a)
{
    if(a != parent[a]) {
        parent[a] = Find(parent[a]);
    }
    return parent[a];
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    if(a < b) {
        parent[b] = a;
    } else {
        parent[a] = b;
    }
}

void InitBFS(int start_row, int start_col)
{
    queue<Node> pq;
    pq.push({start_row, start_col});
    arr[start_row][start_col] = cnt;

    while(!pq.empty()) {
        int row = pq.front().row;
        int col = pq.front().col;
        pq.pop();
        for(int i=0; i<4; i++) {
            int nextrow = row+dir[i].row;
            int nextcol = col+dir[i].col;
            if(nextrow < 1 || nextrow > n || nextcol < 1 || nextcol > n) {
                continue;
            }
            if(arr[nextrow][nextcol] == -1) {
                arr[nextrow][nextcol] = cnt;
                pq.push({nextrow, nextcol});
            }
        }
    }
}

int BFS()
{
    queue<Point> pq;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(arr[i][j] != 0) {
                pq.push({i, j, 0});
            }
        }
    }

    while(!pq.empty()) {
        int row = pq.front().row;
        int col = pq.front().col;
        int cost = pq.front().cost;
        pq.pop();

        for(int i=0; i<4; i++) {
            int nextrow = row+dir[i].row;
            int nextcol = col+dir[i].col;
            if(nextrow < 1 || nextrow > n || nextcol < 1 || nextcol > n) {
                continue;
            }
            if(arr[nextrow][nextcol] != 0) {
                if(Find(arr[row][col]) == Find(arr[nextrow][nextcol])) {
                    continue;
                } else {
                    cnt--;
                    Union(arr[row][col], arr[nextrow][nextcol]);
                    if(cnt == 1) {
                        return cost+1;
                    }
                }
            } else {
                arr[nextrow][nextcol] = arr[row][col];
                pq.push({nextrow, nextcol, cost+1});
            }
            for(int j=0; j<4; j++) {
                int nnrow = nextrow+dir[j].row;
                int nncol = nextcol+dir[j].col;
                if(nnrow < 1 || nnrow > n || nncol < 1 || nncol > n) {
                    continue;
                }
                if(arr[nnrow][nncol] != 0) {
                    if(Find(arr[nextrow][nextcol]) == Find(arr[nnrow][nncol])) {
                        continue;
                    } else {
                        cnt--;
                        Union(arr[nextrow][nextcol], arr[nnrow][nncol]);
                        if(cnt == 1) {
                            return cost+1;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &k);
    
    int a, b;
    for(int i=0; i<k; i++) {
        scanf("%d %d", &a, &b);
        arr[a][b] = -1;
    }

    for(int i=1; i<=k; i++) {
        parent[i] = i;
    }
    
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(arr[i][j] == -1) {
                cnt++;
                InitBFS(i, j);
            }
        }
    }

    if(cnt == 1) {
        printf("0\n");
    } else {
        printf("%d\n", BFS());
    }
}