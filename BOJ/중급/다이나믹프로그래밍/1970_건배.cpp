#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[1000];
int cache[1000][1000];

void Init()
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cache[i][j] = -1;
        }
    }
}

int f(int head, int tail)
{
    if(cache[head][tail] == -1) {
        if(head >= tail) {
            cache[head][tail] = 0;
        } else {
            int result = 0;
            if(arr[head] == arr[tail]) {
                result = f(head+1, tail-1) + 1;
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

    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    Init();
    printf("%d\n", f(0, n-1));
}