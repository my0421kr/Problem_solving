#include <iostream>
using namespace std;

int n, arr[16][16], cache[16][1<<16];

bool IsPath(int index, int path)
{
    return (path & (1<<index)) ? true : false;
}

int f(int index, int path)
{
    if(path == (1<<n)-1) {
        if(arr[index][0] == 0) {
            return 1e9;
        } else {
            return arr[index][0];
        }
    }
    if(cache[index][path] == -1) {
        int result = 2e9;
        for(int i=0; i<n; i++) {
            if(arr[index][i] != 0 && !IsPath(i, path)) {
                result = min(result, f(i, path|(1<<i)) + arr[index][i]);
            }
        }
        cache[index][path] = result;
    }
    return cache[index][path];
}

void Init()
{
    int flag = 1<<n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<flag; j++) {
            cache[i][j] = -1;
        }
    }
}

int main()
{
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    Init();
    printf("%d\n", f(0, 1));
}