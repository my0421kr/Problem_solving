#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> cost;
vector<vector<int>> arr, tree, cache;

void DFS(int root, int index)
{
    int len = arr[index].size();
    for(int i=0; i<len; i++) {
        if(arr[index][i] != root) {
            tree[index].push_back(arr[index][i]);
            DFS(index, arr[index][i]);
        }
    }
}

int f(int include, int index)
{
    if(cache[include][index] == -1) {
        int result;
        int len = tree[index].size();
        if(include == 0) {
            result = 0;
            for(int i=0; i<len; i++) {
                result += max(f(1, tree[index][i]), f(0, tree[index][i]));
            }
        } else {
            result = cost[index];
            for(int i=0; i<len; i++) {
                result += f(0, tree[index][i]);
            }
        }
        cache[include][index] = result;
    }
    return cache[include][index];
}

int main()
{
    scanf("%d", &n);
    cost.resize(n+1);
    arr.resize(n+1);
    tree.resize(n+1);
    cache.assign(2, vector<int>(n+1, -1));

    for(int i=1; i<=n; i++) {
        scanf("%d", &cost[i]);
    }
    int a, b;
    for(int i=1; i<=n-1; i++) {
        scanf("%d %d", &a, &b);
        arr[a].push_back(b);
        arr[b].push_back(a);
    }

    DFS(0, 1);

    int answer = max(f(0, 1), f(1, 1));
    printf("%d\n", answer);
}