#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int index;
    long long cost;
} Node;
typedef struct _Info
{
    long long cost1, cost2;
} Info;

int n, m;
vector<vector<Node>> arr;
vector<vector<int>> parent;
vector<vector<long long>> min_cost, max_cost;
vector<int> visit, height;

void DFS(int root, int index, long long cost, int h)
{
    if(visit[index] == 1) {
        return;
    } else {
        visit[index] = 1;
        parent[index][0] = root;
        min_cost[index][0] = cost;
        max_cost[index][0] = cost;
        height[index] = h;
        int len = (int)arr[index].size();
        for(int i=0; i<len; i++) {
            DFS(index, arr[index][i].index, arr[index][i].cost, h+1);
        }
    }
}

void MakeParent()
{
    for(int j=1; j<20; j++) {
        for(int i=1; i<=n; i++) {
            parent[i][j] = parent[parent[i][j-1]][j-1];
            max_cost[i][j] = max(max_cost[i][j-1], max_cost[parent[i][j-1]][j-1]);
            min_cost[i][j] = min(min_cost[i][j-1], min_cost[parent[i][j-1]][j-1]);
        }
    }
}

int LCA(int a, int b)
{
    int temp, h = height[a] - height[b];
    if(h < 0) {
        h = -h;
        temp = a;
        a = b;
        b = temp;
    }
    for(int i=19; i>=0; i--) {
        if((1 << i) & h) {
            a = parent[a][i];
        }
    }
    if(a == b) {
        return a;
    }
    for(int i=19; i>=0; i--) {
        if(parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    }
    return parent[a][0];
}

Info Dist(int a, int b)
{
    Info result = {(long long)2e18, 0};
    int h = height[a] - height[b];
    for(int i=19; i>=0; i--) {
        if((1 << i) & h) {
            result = {min(result.cost1, min_cost[a][i]), max(result.cost2, max_cost[a][i])};
            a = parent[a][i];
        }
    }
    return result;
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);

    int a, b, c;
    for(int i=0; i<n-1; i++) {
        scanf("%d %d %d", &a, &b, &c);
        arr[a].push_back({b, c});
        arr[b].push_back({a, c});
    }

    parent.assign(n+1, vector<int>(20, 0));
    min_cost.assign(n+1, vector<long long>(20, 0));
    max_cost.assign(n+1, vector<long long>(20, 0));
    height.assign(n+1, 0);
    visit.assign(n+1, 0);

    DFS(1, 1, 0, 0);
    MakeParent();

    scanf("%d", &m);
    for(int i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        int lca = LCA(a, b);
        Info dis1 = Dist(a, lca);
        Info dis2 = Dist(b, lca);
        printf("%lld %lld\n", min(dis1.cost1, dis2.cost1), max(dis1.cost2, dis2.cost2));
    }
}