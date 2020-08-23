#include <iostream>
#include <vector>
using namespace std;

int n, p;
int arr[16][16], cache[17][1<<16];

int f(int cnt, int visited)
{
    if(cache[cnt][visited] == -1) {
        int result = 2e9;
        if(cnt == p) {
            result = 0;
        } else {
            for(int i=0; i<n; i++) {
                if(visited & (1 << i)) {
                    continue;
                }
                for(int j=0; j<n; j++) {
                    if(visited & (1<<j)) {
                        result = min(result, f(cnt+1, visited|(1<<i)) + arr[j][i]);
                    }
                }
            }
        }
        cache[cnt][visited] = result;
    }
    return cache[cnt][visited];
}

int main()
{
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    for(int i=0; i<=n; i++) {
        for(int j=0; j<(1<<n); j++) {
            cache[i][j] = -1;
        }
    }

    getchar();
    char c;
    int count = 0;
    int visited = 0;
    for(int i=0; i<n; i++) {
        c = getchar();
        if(c == 'Y') {
            count++;
            visited += (1<<i);
        }
    }
    scanf("%d", &p);
    if(count >= p) {
        printf("0\n");
    } else {
        if(count == 0) {
            printf("-1\n");
        } else {
            printf("%d\n", f(count, visited));
        }
    }
}