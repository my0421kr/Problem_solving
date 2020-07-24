#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    long long num, w;
} Node;
typedef struct _Info
{
    long long num, w, minw;
} Info;
typedef struct _cmp
{
    bool operator()(Info a, Info b) {
        return a.w > b.w;
    }
} cmp;

int n, m;
vector<long long> cost;
vector<vector<Node>> arr;
vector<vector<long long>> last_dist;

long long Dijk()
{
    priority_queue<Info, vector<Info>, cmp> pq;
    pq.push({1, 0, cost[1]});

    while(!pq.empty()) {
        long long num = pq.top().num;
        long long w = pq.top().w;
        long long minw = pq.top().minw;
        int len = (int)arr[num].size();
        pq.pop();

        if(w >= last_dist[num][minw]) {
            continue;
        }
        last_dist[num][minw] = w;

        if(num == n) {
            return w;
        }

        for(int i=0; i<len; i++) {
            long long next = arr[num][i].num;
            long long nextw = arr[num][i].w;
            long long target = min(minw, cost[next]);
            pq.push({next, w + minw*nextw, target});
        }
    }

}

int main()
{
    scanf("%d %d", &n, &m);
    cost.resize(n+1);
    arr.resize(n+1);
    last_dist.assign(n+1, vector<long long>(2501, (long long)2e18));
    
    long long head, tail, w;
    for(int i=1; i<=n; i++) {
        scanf("%lld", &cost[i]);
    }
    for(int i=1; i<=m; i++) {
        scanf("%lld %lld %lld", &head, &tail, &w);
        arr[head].push_back({tail, w});
        arr[tail].push_back({head, w});
    }

    printf("%lld\n", Dijk());
}