#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct _Node
{
    int num, cost;
} Node;
typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;

int n, m, k;
vector<vector<Node>> arr;
vector<vector<int>> last_dist;

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({1, 0});

    while(!pq.empty()) {
        int num = pq.top().num;
        int cost = pq.top().cost;
        int len = (int)arr[num].size();
        pq.pop();

        if((int)last_dist[num].size() < k) {
            last_dist[num].push_back(cost);
            for(int i=0; i<len; i++) {
                pq.push({arr[num][i].num, arr[num][i].cost + cost});
            }
        }
    }
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);
    arr.resize(n+1);
    last_dist.resize(n+1);

    int head, tail, cost;
    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
    }

    Dijk();
    for(int i=1; i<=n; i++) {
        if((int)last_dist[i].size() != k) {
            printf("-1\n");
        } else {
            printf("%d\n", last_dist[i][k-1]);
        }
    }
}