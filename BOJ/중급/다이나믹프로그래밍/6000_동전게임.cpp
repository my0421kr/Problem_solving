#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> cache;
vector<int> arr, psum;

int f(int prev, int index)
{
    if(index > n || prev == 0) {
        return 0;
    }
    if(cache[prev][index] == -1) {
        int result = 0;
        result = max(result, f(prev-1, index));
        result = max(result, psum[n] - psum[index-1] - f(2*prev-1, index+2*prev-1));
        result = max(result, psum[n] - psum[index-1] - f(2*prev, index+2*prev));
        cache[prev][index] = result;
    }
    return cache[prev][index]; 
}

int main()
{
    scanf("%d", &n);
    cache.assign(n+1, vector<int>(n+1, -1));
    arr.resize(n+1);
    psum.resize(n+1);
    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }
    for(int i=1; i<=n; i++) {
        psum[i] = psum[i-1] + arr[i];
    }

    int result1 = psum[n] - f(1, 2);
    int result2 = psum[n] - f(2, 3);
    printf("%d\n", max(result1, result2));
}