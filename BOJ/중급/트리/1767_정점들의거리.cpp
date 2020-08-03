#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    int index, cost;
} Node;

int n, m;
vector<vector<Node>> arr;
vector<vector<int>> parent;
vector<int> visit, height, dist;

void MakeParent(int root, int index, int h, int cost)
{
    if(visit[index] == 1) {
        return;
    }
    visit[index] = 1;
    height[index] = h;
    dist[index] = cost;
    parent[index][0] = root;
    int len = (int)arr[index].size();

    for(int i=0; i<len; i++) {
        MakeParent(index, arr[index][i].index, h+1, cost+arr[index][i].cost);
    }
}

int Parent(int a, int k)
{
    if(k == 0) {
        return parent[a][k];
    } else if(parent[a][k] == -1){
        parent[a][k] = Parent(Parent(a, k-1), k-1);
    }
    return parent[a][k];
}

int UpParent(int a, int h)
{
    for(int i=0; i<20; i++) {
        if((1 << i) & h) {
            a = Parent(a, i);
        }
    }
    return a;
}

int LCA(int a, int b)
{
    if(height[a] > height[b]) {
        a = UpParent(a, height[a] - height[b]);
    } else if(height[a] < height[b]) {
        b = UpParent(b, height[b] - height[a]);
    }

    if(a == b) {
        return a;
    } else {
        int i, result1, result2;
        for(i=0; i<20; i++) {
            result1 = Parent(a, i);
            result2 = Parent(b, i);
            if(result1 == result2) {
                break;
            }
        }
        if(i == 0) {
            return result1;
        } else {
            return LCA(Parent(a, i-1), Parent(b, i-1));
        }
    }
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);
    height.resize(n+1);
    dist.resize(n+1);
    visit.assign(n+1, 0);
    parent.assign(n+1, vector<int>(30, -1));

    int head, tail, cost;
    for(int i=1; i<=n-1; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
        arr[tail].push_back({head, cost});
    }

    for(int i=0; i<30; i++) {
        parent[0][i] = 0;
    }
    MakeParent(0, 1, 0, 0);

    scanf("%d", &m);
    for(int i=1; i<=m; i++) {
        scanf("%d %d", &head, &tail);
        int result = LCA(head, tail);
        printf("%d\n", dist[head] + dist[tail] - 2*dist[result]);
    }

}