#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> arr;
vector<vector<int>> cache;

int f(int index, int last)
{
    if(cache[index][last] == -1) {
        int result = 2e9;
        if(index == 1) {
            result = 0;
        } else {
            if(last != index-1) {
                result = f(index-1, last) + abs(arr[index] - arr[index-1]);
            } else {
                result = f(index-1, 0);
                for(int i=1; i<=index-2; i++) {
                    result = min(result, f(index-1, i) + abs(arr[index] - arr[i]));
                }
            }
        }
        cache[index][last] = result;
    }
    return cache[index][last];
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);
    cache.assign(n+1, vector<int>(n+1, -1));

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    int answer = 2e9;
    for(int i=0; i<n; i++) {
        answer = min(answer, f(n, i));
    }
    printf("%d\n", answer);
}