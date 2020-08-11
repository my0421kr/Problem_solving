#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int index, cost, thr;
} Node;
typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;

int t, n, m, k;
int last_dist[101][10001];
vector<vector<Node>> arr;

void Init()
{
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=m; j++) {
            last_dist[i][j] = 2e9;
        }
    }
}

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({1, 0, 0});
    last_dist[1][0] = 0;

    while(!pq.empty()) {
        int index = pq.top().index;
        int cost = pq.top().cost;
        int thr = pq.top().thr;
        int len = arr[index].size();
        pq.pop();

        if(cost > last_dist[index][thr]) {
            continue;
        }

        for(int i=0; i<len; i++) {
            int nextindex = arr[index][i].index;
            int nextcost = arr[index][i].cost + cost;
            int nextthr = arr[index][i].thr + thr;

            if(nextthr > m) {
                continue;
            }

            if(nextcost < last_dist[nextindex][nextthr]) {
                for(int j=nextthr; j<=m; j++) {
                    if(nextcost < last_dist[nextindex][j]) {
                        last_dist[nextindex][j] = nextcost;
                    }
                }
                pq.push({nextindex, nextcost, nextthr});
            }
        }
    }
}

int main()
{
    scanf("%d", &t);

    for(int i=0; i<t; i++) {
        scanf("%d %d %d", &n, &m, &k);
        Init();
        for(int j=0; j<(int)arr.size(); j++) {
            arr[j].clear();
        }
        arr.clear();
        arr.resize(n+1);
        

        int head, tail, cost, thr;
        for(int j=0; j<k; j++) {
            scanf("%d %d %d %d", &head, &tail, &cost, &thr);
            arr[head].push_back({tail, thr, cost});
        }

        Dijk();

        int answer = 2e9;
        for(int j=1; j<=m; j++) {
            answer = min(answer, last_dist[n][j]);
        }
        if(answer == 2e9) {
            printf("Poor KCM\n");
        } else {
            printf("%d\n", answer);
        }
    }
}