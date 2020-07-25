#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Point
{
    int row, col;
} Point;
typedef struct _Node
{
    Point pos;
    int cost;
} Node;
typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;

int n, m, t, d;
int map[25][25];
int arr[25][25][25][25];
int last_dist[25][25][25][25];
int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
vector<Node> distarr;

bool IsValid(int row, int col)
{
    return (0 <= row && row < n && 0 <= col && col < m) ? true : false;
}

bool cmp2(Node a, Node b)
{
    return a.cost > b.cost;
}

void InitDist()
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            for(int k=0; k<n; k++) {
                for(int p=0; p<m; p++) {
                    last_dist[i][j][k][p] = (int)1e9;
                }
            }
        }
    }
}

void Dijk(Point first)
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({first, 0});
    last_dist[first.row][first.col][first.row][first.col] = 0;

    while(!pq.empty()) {
        int row = pq.top().pos.row;
        int col = pq.top().pos.col;
        int cost = pq.top().cost;
        pq.pop();

        for(int i=0; i<4; i++) {
            int new_row = row+dir[0][i];
            int new_col = col+dir[1][i];
            if(IsValid(new_row, new_col)) {
                if(arr[row][col][new_row][new_col] == 0) {
                    continue;
                }
                if(cost + arr[row][col][new_row][new_col] < last_dist[first.row][first.col][new_row][new_col]) {
                    last_dist[first.row][first.col][new_row][new_col] = cost + arr[row][col][new_row][new_col];
                    pq.push({{new_row, new_col}, last_dist[first.row][first.col][new_row][new_col]});
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &t, &d);

    char c;
    for(int i=0; i<n; i++) {
        getchar();
        for(int j=0; j<m; j++) {
            c = getchar();
            if('A' <= c && c <= 'Z') {
                map[i][j] = c - 'A';
            } else {
                map[i][j] = c - 'a' + 26;
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            for(int k=0; k<4; k++) {
                int row = i+dir[0][k];
                int col = j+dir[1][k];
                if(IsValid(row, col)) {
                    int pr = abs(map[row][col] - map[i][j]);
                    if(pr <= t) {
                        if(map[i][j] >= map[row][col]) {
                            arr[i][j][row][col] = 1;
                        } else {
                            arr[i][j][row][col] = pr*pr;
                        }
                    }
                }
            }
        }
    }

    InitDist();
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            Dijk({i, j});
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            distarr.push_back({{i, j}, map[i][j]});
        }
    }
    sort(distarr.begin(), distarr.end(), cmp2);

    int len = (int)distarr.size();
    for(int i=0; i<len; i++) {
        int row = distarr[i].pos.row;
        int col = distarr[i].pos.col;
        int height = distarr[i].cost;
        if(last_dist[0][0][row][col] + last_dist[row][col][0][0] <= d) {
            printf("%d\n", height);
            break;
        }
    }
}