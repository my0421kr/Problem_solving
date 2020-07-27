#include <iostream>
#include <vector>
using namespace std;

int n, m;
int arr[2001];
vector<vector<int>> cache;

int IsPalindrome(int head, int tail)
{
    if(cache[head][tail] == -1) {
        if(head >= tail) {
            cache[head][tail] = 1;
        } else if(arr[head] == arr[tail]){
            cache[head][tail] = IsPalindrome(head+1, tail-1);
        } else {
            cache[head][tail] = 0;
        }
    }
    return cache[head][tail];
}

int main()
{
    scanf("%d", &n);
    cache.assign(n+1, vector<int>(n+1, -1));

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &m);
    int head, tail;
    for(int i=1; i<=m; i++) {
        scanf("%d %d", &head, &tail);
        printf("%d\n", IsPalindrome(head, tail));
    }
}