#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int r, c;
} Node;

int n;
Node arr[500];
vector<vector<int>> cache;

int Function(int head, int tail)
{
    if(cache[head][tail] == -1) {
        if(head == tail) {
            cache[head][tail] = 0;
        } else {
            int result = 2147483647;
            for(int i=head; i<tail; i++) {
                result = min(result, Function(head, i) + Function(i+1, tail) + arr[head].r * arr[i].c * arr[tail].c);
            }
            cache[head][tail] = result;
        }
    }
    return cache[head][tail];
}

int main()
{
    scanf("%d", &n);
    cache.assign(n, vector<int>(n, -1));

    for(int i=0; i<n; i++) {
        scanf("%d %d", &arr[i].r, &arr[i].c);
    }

    printf("%d\n", Function(0, n-1));
}