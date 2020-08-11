#include <iostream>
#include <vector>
#define MAX 1000000007
using namespace std;

int n, k;
vector<vector<vector<long long>>> cache;
vector<vector<int>> arr;
vector<vector<int>> tree;

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

long long f(int root, int until, int count)
{
    if(count == 1 || count == 0) {
        return 1;
    } else if(until == -1) {
        return 0;
    }
    if(cache[root][until][count] == -1) {
        long long result = 0;
        for(int i=1; i<=count; i++) {
            result += f(root, until-1, i) * f(tree[root][until], (int)tree[tree[root][until]].size()-1, count-i);
            result %= MAX;
        }
        cache[root][until][count] = result;
    }
    return cache[root][until][count];
}

int main()
{
    scanf("%d %d", &n, &k);
    arr.resize(n+1);
    tree.resize(n+1);
    cache.assign(n+1, vector<vector<long long>>(n+1, vector<long long>(n+1, -1)));

    int a, b;
    for(int i=0; i<n-1; i++) {
        scanf("%d %d", &a, &b);
        arr[a].push_back(b);
        arr[b].push_back(a);
    }

    DFS(0, 1);

    long long answer = 0;
    for(int i=1; i<=n; i++) {
        answer += f(i, (int)tree[i].size()-1, k);
        answer %= MAX;
    }
    printf("%lld\n", answer);
}