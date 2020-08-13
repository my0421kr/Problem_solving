#include <iostream>
#include <vector>
#include <algorithm>
#define MOD 20070713
using namespace std;

typedef struct _Node
{
    int head, tail;
} Node;

int n;
vector<Node> arr;
vector<long long> cache;

bool cmp(Node a, Node b)
{
    return a.tail < b.tail;
}
bool cmp2(Node a, Node b)
{
    return a.tail < b.head;
}

long long f(int index)
{
    if(index == 0) {
        return 1;
    } else if(cache[index] == -1) {
        int start = lower_bound(arr.begin()+1, arr.end()-(n-index), arr[index], cmp2) - arr.begin();
        cache[index] = f(start-1) + f(index-1);
        cache[index] %= MOD;
    }
    return cache[index];
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);
    cache.assign(n+1, -1);

    for(int i=1; i<=n; i++) {
        scanf("%d %d", &arr[i].head, &arr[i].tail);
    }
    sort(arr.begin()+1, arr.end(), cmp);
    printf("%lld\n", f(n));
}