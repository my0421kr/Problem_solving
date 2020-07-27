#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int t, n;
vector<int> arr;
vector<vector<int>> cache, sum_cache;

int Sum(int head, int tail)
{
    if(sum_cache[head][tail] == -1) {
        if(head == tail) {
            sum_cache[head][tail] = arr[head];
        } else {
            sum_cache[head][tail] = Sum(head, tail-1) + arr[tail];
        }
    }
    return sum_cache[head][tail];
}

int Function(int head, int tail)
{
    if(cache[head][tail] == -1) {
        if(head == tail) {
            cache[head][tail] = 0;
        } else {
            int result = 2e9;
            for(int i=head; i<tail; i++) {
                result = min(result, Function(head, i) + Function(i+1, tail) + Sum(head, tail));
            }
            cache[head][tail] = result;
        }
    }
    return cache[head][tail];
}

int main()
{
    scanf("%d", &t);

    for(int i=0; i<t; i++) {
        scanf("%d", &n);
        arr.resize(n);
        cache.assign(n, vector<int>(n, -1));
        sum_cache.assign(n, vector<int>(n, -1));
        for(int j=0; j<n; j++) {
            scanf("%d", &arr[j]);
        }
        printf("%d\n", Function(0, n-1));
    }
}