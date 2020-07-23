#include <iostream>
#include <queue>
#include <vector>
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

int n, m;
vector<Node> last_dist;
int arr[1001][1001];

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({1, 0});
    last_dist[1] = {-1, 0};


    while(!pq.empty()) {
        int num = pq.top().num;
        int cost = pq.top().cost;
        pq.pop();

        for(int i=1; i<=n; i++) {
            if(arr[num][i] != 0) {
                int temp_cost = cost + arr[num][i];
                if(temp_cost < last_dist[i].cost) {
                    last_dist[i] = {num, temp_cost};
                    pq.push({i, temp_cost});
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    last_dist.assign(n+1, {-1, (int)2e9});

    int head, tail, cost;
    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head][tail] = cost;
        arr[tail][head] = cost;
    }

    Dijk();
    printf("%d\n", n-1);
    for(int i=2; i<=n; i++) {
        if(last_dist[i].cost != 2e9) {
            printf("%d %d\n", i, last_dist[i].num);
        }
    }
}