#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
vector<int> arr;
vector<vector<int>> cache;

int f(int head, int tail)
{
    if(cache[head][tail] == -1) {
        int result = 2e9;
        if(head >= tail) {
            result = 0;
        } else if(arr[head] == arr[tail]) {
            result = f(head+1, tail-1) +1;
        } else {
            for(int i=head; i<tail; i++) {
                result = min(result, f(head, i) + f(i+1, tail) + 1);
            }
        }
        cache[head][tail] = result;
    }
    return cache[head][tail];
}

int main()
{
    scanf("%d %d", &n, &k);

    int prev = 0, a;
    arr.push_back(0);
    for(int i=1; i<=n; i++) {
        scanf("%d", &a);
        if(a != prev) {
            prev = a;
            arr.push_back(a);
        }
    }

    n = arr.size()-1;
    cache.assign(n+1, vector<int>(n+1, -1));
    printf("%d\n", f(1, n));
}