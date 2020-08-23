#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct _Node
{
    int index, dist, cost;
} Node;
typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.dist > b.dist;
    }
} cmp;

int n, m, k, head, tail;
vector<vector<Node>> arr;
vector<vector<int>> last_dist;

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({head, 0, 0});
    last_dist[head][0] = 0;

    while(!pq.empty()) {
        int index = pq.top().index;
        int dist = pq.top().dist;
        int cost = pq.top().cost;
        int len = arr[index].size();
        pq.pop();

        if(index == tail) {
            return;
        }

        for(int i=0; i<len; i++) {
            int nextindex = arr[index][i].index;
            int nextdist = arr[index][i].dist + dist;
            int nextcost = arr[index][i].cost + cost;
            if(nextcost >= k) {
                continue;
            }
            if(nextdist < last_dist[nextindex][nextcost]) {
                for(int j=nextcost; j<k; j++) {
                    last_dist[nextindex][j] = min(last_dist[nextindex][j], nextdist);
                }
                pq.push({nextindex, nextdist, nextcost});
            }
        }

    }
}

int main()
{
    scanf("%d %d %d", &k, &n, &m);
    arr.resize(n+1);
    last_dist.assign(n+1, vector<int>(k+1, (int)2e9));

    int a, b, c, d;
    for(int i=1; i<=m; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        arr[a].push_back({b, c, d});
        arr[b].push_back({a, c, d});
    }
    scanf("%d %d", &head, &tail);
    Dijk();
    int answer = 2e9;
    for(int i=0; i<k; i++) {
        answer = min(answer, last_dist[tail][i]);
    }
    if(answer == 2e9) {
        printf("-1\n");
    } else {
        printf("%d\n", answer);
    }
}