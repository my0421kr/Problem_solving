#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef struct _Node
{
    int num;
    long long cost;
} Node;

typedef struct _Info
{
    int num;
    long long cost;
    int prev;
} Info;

typedef struct _cmp
{
    bool operator()(Info a, Info b) {
        return a.cost > b.cost;
    }
} cmp;

int n, m;
int head, tail;
vector<Node> last_dist;
vector<vector<Node>> arr;

void Dijk()
{
    priority_queue<Info, vector<Info>, cmp> pq;
    pq.push({head, 0, -1});

    while(!pq.empty()) {
        int num = pq.top().num;
        long long cost = pq.top().cost;
        int prev = pq.top().prev;
        pq.pop();

        if(cost < last_dist[num].cost) {
            last_dist[num] = {prev, cost};
            int len = (int)arr[num].size();
            for(int i=0; i<len; i++) {
                pq.push({arr[num][i].num, cost + arr[num][i].cost, num});
            }
        }
    }
}

void Print(int index, int count)
{
    if(index == -1) {
        printf("%d\n", count);
        return;
    } else {
        Print(last_dist[index].num, count+1);
        printf("%d ", index);
        return;
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    arr.resize(n+1);
    last_dist.assign(n+1, {-1, (long long)2e18});

    long long cost;
    for(int i=0; i<m; i++) {
        scanf("%d %d %lld", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
    }
    scanf("%d %d", &head, &tail);

    Dijk();
    printf("%lld\n", last_dist[tail].cost);
    Print(tail, 0);
}