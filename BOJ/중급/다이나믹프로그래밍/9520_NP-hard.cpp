#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> arr, cache;

int f(int head, int tail, int index)
{
    if(index == n+1) {
        return 0;
    }
    if(cache[head][tail] == -1) {
        int result1 = f(head, index, index+1) + arr[tail][index];
        int result2 = f(index, tail, index+1) + arr[index][head];
        cache[head][tail] = min(result1, result2);
    }
    return cache[head][tail];
}

int main()
{
    scanf("%d", &n);
    arr.assign(n+1, vector<int>(n+1));
    cache.assign(n+1, vector<int>(n+1, -1));

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int answer = f(1, 1, 1);
    printf("%d\n", answer);
}