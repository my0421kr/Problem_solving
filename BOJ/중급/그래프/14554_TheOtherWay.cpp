#include <iostream>
#include <queue>
#include <vector>
#define MOD 1000000009
using namespace std;

typedef struct _Node
{
    int index;
    long long cost;
} Node;
typedef struct _Dist
{
    long long cost, cnt;
} Dist;
typedef struct _Point
{
    int index;
    long long cost, cnt;
} Point;
typedef struct _cmp
{
    bool operator()(Point a, Point b) {
        return a.cost > b.cost;
    }
} cmp;

int n, m, s, e;
vector<vector<Node>> arr;
vector<Dist> last_dist;
vector<int> visited;

void Dijk()
{
    priority_queue<Point, vector<Point>, cmp> pq;
    pq.push({s, 0, 1});
    last_dist[s] = {0, 1};

    while(!pq.empty()) {
        int index = pq.top().index;
        long long cost = pq.top().cost;
        long long cnt = pq.top().cnt;
        int len = arr[index].size();
        pq.pop();

        if(cost < last_dist[index].cost) {
            continue;
        } else if(cost == last_dist[index].cost) {
            if(cnt != last_dist[index].cnt) {
                continue;
            }
        }

        if(visited[index] == 1) {
            continue;
        }
        visited[index] = 1;

        for(int i=0; i<len; i++) {
            int nextindex = arr[index][i].index;
            long long nextcost = arr[index][i].cost + cost;

            if(nextcost < last_dist[nextindex].cost) {
                last_dist[nextindex] = {nextcost, cnt};
                pq.push({nextindex, nextcost, cnt});
            } else if (nextcost == last_dist[nextindex].cost) {
                last_dist[nextindex].cnt += cnt;
                last_dist[nextindex].cnt %= MOD;
                pq.push({nextindex, nextcost, last_dist[nextindex].cnt});
            }
        }
    }
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &s, &e);
    arr.resize(n+1);
    last_dist.assign(n+1, {(long long)2e18, 0});
    visited.assign(n+1, 0);

    int head, tail;
    long long cost;
    for(int i=0; i<m; i++) {
        scanf("%d %d %lld", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
        arr[tail].push_back({head, cost});
    }

    Dijk();
    printf("%lld\n", last_dist[e].cnt);
}