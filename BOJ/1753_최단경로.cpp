#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef struct _Node
{
    int num, cost;
} Node;

struct cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
};

int v, e, start;
vector<int> last_dist;
vector<vector<Node>> arr;

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int num = pq.top().num;
        int cost = pq.top().cost;
        pq.pop();

        if(cost < last_dist[num]) {
            last_dist[num] = cost;
            int len = (int)arr[num].size();
            for(int i=0; i<len; i++) {
                pq.push({arr[num][i].num, arr[num][i].cost + cost});
            }
        }
    }
}

int main()
{
    scanf("%d %d", &v, &e);
    scanf("%d", &start);
    arr.resize(v+1);
    last_dist.assign(v+1, 2e9);

    int head, tail, cost;
    for(int i=0; i<e; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
    }

    Dijk();
    for(int i=1; i<=v; i++) {
        if(last_dist[i] == 2e9) {
            printf("INF\n");
        } else {
            printf("%d\n", last_dist[i]);
        }
    }
}