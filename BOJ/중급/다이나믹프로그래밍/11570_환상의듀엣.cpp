#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> arr, temp;
vector<vector<int>> cache;

int f(int index, int last)
{
    if(index == 1) {
        return 0;
    } else if(last == 0) {
        return temp[index];
    }
    if(cache[index][last] == -1) {
        int result = 2e9;
        if(last == index-1) {
            result = min(result, f(index-1, 0));
            for(int i=1; i<=index-2; i++) {
                result = min(result, abs(arr[i] - arr[index]) + f(index-1, i));
            }
        } else {
            result = f(index-1, last) + abs(arr[index] - arr[index-1]);
        }
        cache[index][last] = result;
    }
    return cache[index][last];
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);
    temp.assign(n+1, 0);
    cache.assign(n+1, vector<int>(n+1, -1));

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }
    for(int i=2; i<=n; i++) {
        temp[i] = abs(arr[i] - arr[i-1]) + temp[i-1];
    }
    

    int answer = 2e9;
    for(int i=0; i<=n-1; i++) {
        answer = min(answer, f(n, i));
    }
    printf("%d\n", answer);
}