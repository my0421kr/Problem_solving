#include <string>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

typedef struct _Node
{
    int row, col, flag, cost;
} Node;
typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;

int n, dir[2][4] = {{0,1,0,-1}, {1,0,-1,0}};
vector<vector<vector<int>>> lastdist;

void Dijk(vector<vector<int>> &arr)
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({0,0,0,0});
    pq.push({0,0,1,0});
    lastdist[0][0][0] = 0;
    lastdist[1][0][0] = 0;

    while(!pq.empty()) {
        int row = pq.top().row;
        int col = pq.top().col;
        int flag = pq.top().flag;
        int cost = pq.top().cost;
        pq.pop();

        for(int i=0; i<4; i++) {
            int nr = row + dir[0][i];
            int nc = col + dir[1][i];
            if(nr < 0 || nr >= n || nc < 0 || nc >= n) {
                continue;
            } else if(arr[nr][nc] == 1) {
                continue;
            }
            int ncost;
            if(flag%2 == i%2) {
                ncost = cost+100;
            } else {
                ncost = cost+600;
            }

            if(ncost < lastdist[i%2][nr][nc]) {
                lastdist[i%2][nr][nc] = ncost;
                pq.push({nr, nc, i%2, ncost});
            }
        }
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    n = board.size();
    lastdist.assign(2, vector<vector<int>>(n, vector<int>(n, (int)2e9)));

    Dijk(board);
    answer = min(lastdist[0][n-1][n-1], lastdist[1][n-1][n-1]);
    return answer;
}