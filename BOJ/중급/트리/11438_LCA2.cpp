#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> parent, arr;
vector<int> height, visit;

void MakeParent(int root, int h)
{
    if(visit[root] == 1) {
        return;
    }
    visit[root] = 1;
    height[root] = h;
    int len = (int)arr[root].size();
    for(int i=0; i<len; i++) {
        MakeParent(arr[root][i], h+1);
        parent[arr[root][i]][0] = root;
    }
}

int Parent(int a, int k)
{
    if(k == 0) {
        return parent[a][k];
    } else if(parent[a][k] == -1) {
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
        int i, parent1, parent2;
        for(i=0; i<20; i++) {
            parent1 = Parent(a, i);
            parent2 = Parent(b, i);
            if(parent1 == parent2) {
                break;
            }
        }
        
        if(i == 0) {
            return parent1;
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
    visit.assign(n+1, 0);
    parent.assign(n+1, vector<int>(30, -1));

    int a, b;
    for(int i=0; i<n-1; i++) {
        scanf("%d %d", &a, &b);
        arr[a].push_back(b);
        arr[b].push_back(a);
    }

    parent[1][0] = 0;
    MakeParent(1, 0);

    scanf("%d", &m);
    for(int i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", LCA(a, b));
    }
}