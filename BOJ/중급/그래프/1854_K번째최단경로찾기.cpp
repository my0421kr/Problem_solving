#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct _Node
{
    int index, cost;
} Node;
typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;
typedef struct _cmp2
{
    bool operator()(int a, int b) {
        return a < b;
    }
} cmp2;

int n, m, k;
vector<vector<Node>> arr;
vector<priority_queue<int, vector<int>, cmp2>> last_dist;

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({1, 0});
    last_dist[1].push(0);

    while(!pq.empty()) {
        int index = pq.top().index;
        int cost = pq.top().cost;
        int len = arr[index].size();
        pq.pop();

        for(int i=0; i<len; i++) {
            int nextindex = arr[index][i].index;
            int nextcost = arr[index][i].cost + cost;
            if(last_dist[nextindex].size() == k) {
                if(nextcost < last_dist[nextindex].top()) {
                    last_dist[nextindex].pop();
                    last_dist[nextindex].push(nextcost);
                    pq.push({nextindex, nextcost});
                }
            } else {
                last_dist[nextindex].push(nextcost);
                pq.push({nextindex, nextcost});
            }
        }
    }
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);
    arr.resize(n+1);
    last_dist.resize(n+1);

    int a, b, c;
    for(int i=1; i<=m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        arr[a].push_back({b, c});
    }

    Dijk();
    for(int i=1; i<=n; i++) {
        if(last_dist[i].size() != k) {
            printf("%d\n", -1);
        } else {
            printf("%d\n", last_dist[i].top());
        }
    }
}