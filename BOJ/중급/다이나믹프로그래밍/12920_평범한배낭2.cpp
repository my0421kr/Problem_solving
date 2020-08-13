#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int v, c, k;
} Node;

int n, m;
vector<vector<int>> cache;
vector<Node> arr;

int f(int index, int weight)
{
    if(weight < 0) {
        return -1;
    } else if(index == 0) {
        return 0;
    }
    if(cache[index][weight] == -2) {
        int result = -1;
        int temp = f(index-1, weight-arr[index].v*arr[index].k);
        if(temp != -1) {
            result = temp + arr[index].c*arr[index].k;
        }
        temp = f(index-1, weight);
        if(temp != -1) {
            result = max(result, temp);
        }
        cache[index][weight] = result;
    }
    return cache[index][weight];
}

int main()
{
    scanf("%d %d", &n, &m);
    arr.resize(1);

    int v, c, k;
    for(int i=1; i<=n; i++) {
        scanf("%d %d %d", &v, &c, &k);
        int temp = 1;
        arr.push_back({v, c, 1});
        while(temp < k/2) {
            arr.push_back({v, c, temp});
            temp = (temp << 1);
        }
        if(k != temp) {
            arr.push_back({v, c, k-temp});
        }
    }

    n = arr.size()-1;
    cache.assign(n+1, vector<int>(m+1, -2));
    printf("%d\n", f(n, m));
}