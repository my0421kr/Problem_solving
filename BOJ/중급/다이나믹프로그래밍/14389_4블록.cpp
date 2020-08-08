#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int cache[25][1<<10];
char arr[10][25];
void DFS(int index, int curpath, int col, int nextpath, int count);
int f(int col, int nextpath);

void Init()
{
    int temp = 1<<n;
    for(int i=0; i<m; i++) {
        for(int j=0; j<temp; j++) {
            cache[i][j] = -1;
        }
    }
}

void DFS(int index, int curpath, int col, int nextpath, int count)
{
    if(index >= n) {
        cache[col][nextpath] = max(cache[col][nextpath], f(col-1, curpath) + count);
    } else {
        if(index < n-1) {
            if(col >= 1 && arr[index][col] == '.' && arr[index+1][col] == '.' && arr[index][col-1] == '.' && arr[index+1][col-1] == '.') {
                if( !(nextpath & (1<<index)) && !(nextpath & (1<<(index+1))) ) {
                    DFS(index+2, curpath | (1<<index) | (1<<(index+1)), col, nextpath, count+16);
                }
            }
        }
        if(!(nextpath & (1<<index))) {
            DFS(index+1, curpath, col, nextpath, count+1);
        } else {
            DFS(index+1, curpath, col, nextpath, count);
        }
    }
}

int f(int col, int nextpath)
{
    if(col == -1) {
        return 0;
    }
    if(cache[col][nextpath] == -1) {
        cache[col][nextpath] = 0;
        DFS(0, 0, col, nextpath, 0);
    }
    return cache[col][nextpath];
}

int main()
{
    scanf("%d %d", &n, &m);

    for(int i=0; i<n; i++) {
        getchar();
        for(int j=0; j<m; j++) {
            arr[i][j] = getchar();
        }
    }

    Init();
    printf("%d\n", f(m-1, 0));
}