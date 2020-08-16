#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _Point
{
    int index;
    long long cost;
} Point;

typedef struct _Node
{
    int index;
    long long cost;
    int cnt;
} Node;

int n, m, k, s, d;
long long pluscost[30001];
long long last_dist[1001][1001];
vector<vector<Point>> arr;

typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;

void Init()
{
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=n; j++) {
            last_dist[i][j] = 1e18;
        }
    }
}

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({s, 0, 0});
    last_dist[s][0] = 0;

    while(!pq.empty()) {
        int index = pq.top().index;
        long long cost = pq.top().cost;
        int cnt = pq.top().cnt;
        int len = arr[index].size();
        pq.pop();

        int flag = 0;
        for(int i=0; i<=cnt; i++) {
            if(last_dist[index][i] < cost) {
                flag = 1;
                break;
            }
        }
        if(flag == 1) {
            continue;
        }

        for(int i=0; i<len; i++) {
            int nextindex = arr[index][i].index;
            long long nextcost = cost + arr[index][i].cost;
            int nextcnt = cnt+1;

            if(nextcost < last_dist[nextindex][nextcnt] && nextcnt < n) {
                last_dist[nextindex][nextcnt] = nextcost;
                pq.push({nextindex, nextcost, nextcnt});
            }
        }
    }

}

int main()
{
    scanf("%d %d %d %d %d", &n, &m, &k, &s, &d);
    Init();
    arr.resize(n+1);

    int a, b;
    long long c;
    for(int i=1; i<=m; i++) {
        scanf("%d %d %lld", &a, &b, &c);
        arr[a].push_back({b, c});
        arr[b].push_back({a, c});
    }

    pluscost[0] = 0;
    for(int i=1; i<=k; i++) {
        scanf("%lld", &pluscost[i]);
    }
    Dijk();
    for(int i=0; i<=k; i++) {
        long long result = 1e18;
        for(int j=0; j<n; j++) {
            last_dist[d][j] += ((long long)j*pluscost[i]);
        }
        for(int j=0; j<n; j++) {
            result = min(result, last_dist[d][j]);
        }
        printf("%lld\n", result);
    }
}