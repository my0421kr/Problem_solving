#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[101][101];
int cache[101][101];

void Init()
{
    for(int i=0; i<=100; i++) {
        for(int j=0; j<=100; j++) {
            cache[i][j] = -1;
        }
    } 
}

int f(int head, int tail)
{
    if(cache[head][tail] == -1) {
        if(head >= tail) {
            return 0;
        } else {
            int result = 0;
            if(arr[head][tail] == 1) {
                result = max(result, f(head+1, tail-1)) + 1;
            }
            for(int i=head; i<tail; i++) {
                result = max(result, f(head, i) + f(i+1, tail));
            }
            cache[head][tail] = result;
        }
    }
    return cache[head][tail];
}

int main()
{
    scanf("%d", &n);

    int a, b;
    for(int i=0; i<n; i++) {
        scanf("%d %d", &a, &b);
        arr[a][b] = 1;
        arr[b][a] = 1;
    }
    Init();
    printf("%d\n", f(1, 100));
}