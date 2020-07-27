#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int num, cost;
} Node;

int n, m, first, last, result = 0;
vector<vector<Node>> arr, parent;
vector<int> cnt, last_dist, visit;

void Function()
{
    queue<Node> pq;
    pq.push({first, 0});
    last_dist[first] = 0;

    while(!pq.empty()) {
        int num = pq.front().num;
        int cost = pq.front().cost;
        int len = (int)arr[num].size();
        pq.pop();

        for(int i=0; i<len; i++) {
            last_dist[arr[num][i].num] = max(last_dist[arr[num][i].num], cost + arr[num][i].cost);
            cnt[arr[num][i].num]--;
            if(cnt[arr[num][i].num] == 0) {
                pq.push({arr[num][i].num, last_dist[arr[num][i].num]});
            }
        }
    }
}

void Back()
{
    queue<int> pq;
    pq.push(last);

    while(!pq.empty()) {
        int num = pq.front();
        int len = (int)parent[num].size();
        pq.pop();

        if(visit[num] == 1) {
            continue;
        }
        visit[num] = 1;

        for(int i=0; i<len; i++) {
            if(last_dist[num] - parent[num][i].cost == last_dist[parent[num][i].num]) {
                pq.push(parent[num][i].num);
                result++;
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    arr.resize(n+1);
    parent.resize(n+1);
    cnt.assign(n+1, 0);
    last_dist.assign(n+1, 0);
    visit.assign(n+1, 0);

    int head, tail, cost;
    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
        parent[tail].push_back({head, cost});
        cnt[tail]++;
    }
    scanf("%d %d", &first, &last);

    Function();
    Back();
    printf("%d\n", last_dist[last]);
    printf("%d\n", result);
}
