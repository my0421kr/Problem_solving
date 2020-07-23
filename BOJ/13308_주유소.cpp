// Not solved
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int num;
    long long w;
} Node;
typedef struct _Info
{
    int num;
    long long w, minw;
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
vector<vector<int>> visited;

long long Dijk()
{
    priority_queue<Info, vector<Info>, cmp> pq;
    pq.push({1, 0, cost[1]});

    while(!pq.empty()) {
        int num = pq.top().num;
        long long w = pq.top().w;
        long long minw = pq.top().minw;
        int len = (int)arr[num].size();
        pq.pop();

        if(visited[num][minw] == 1) {
            continue;
        }
        visited[num][minw] = 1;
        if(num == n) {
            return w;
        }

        for(int i=0; i<len; i++) {
            int next = arr[num][i].num;
            int nextw = arr[num][i].w;
            pq.push({next, w + minw*nextw, min(minw, cost[next])});
        }
    }

}

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    cost.resize(n+1);
    arr.resize(n+1);
    visited.assign(n+1, vector<int>(2501, 0));
    
    int head, tail;
    long long w;
    for(int i=1; i<=n; i++) {
        scanf("%lld", &cost[i]);
    }
    for(int i=1; i<=n; i++) {
        scanf("%d %d %lld", &head, &tail, &w);
        arr[head].push_back({tail, w});
        arr[tail].push_back({head, w});
    }

    printf("%lld\n", Dijk());
}