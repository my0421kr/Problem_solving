#include <iostream>
using namespace std;

int n, m;
int cache[14][1<<14];
void DFS(int index, int curpath, int row, int nextpath);
int f(int row, int nextpath);

void Init()
{
    int temp = 1<<m;
    for(int i=0; i<n; i++) {
        for(int j=0; j<temp; j++) {
            cache[i][j] = -1;
        }
    }
}

void DFS(int index, int curpath, int row, int nextpath)
{
    if(index >= m) {
        cache[row][nextpath] += f(row-1, curpath);
    } else {
        if( nextpath & (1<<index) ) {
            DFS(index+1, curpath, row, nextpath);
        } else {
            DFS(index+1, curpath|(1<<index), row, nextpath);
            if(index != m-1 && !(nextpath & (1<<index+1)) ) {
                DFS(index+2, curpath, row, nextpath);
            }
        }
    }
}

int f(int row, int nextpath)
{
    if(row == -1) {
        return (nextpath == 0) ? 1 : 0;
    }
    if(cache[row][nextpath] == -1) {
        cache[row][nextpath] = 0;
        DFS(0, 0, row, nextpath);
        cache[row][nextpath] %= 9901;
    }
    return cache[row][nextpath];
}

int main()
{
    scanf("%d %d", &n, &m);

    Init();
    printf("%d\n", f(n-1, 0));
}