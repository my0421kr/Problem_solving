#include <iostream>
#include <vector>
using namespace std;

int t, n, m, curpath = 0;
int cache[10][1024];
char arr[10][10];

int f(int row, int nextpath);
void MakePath(int index, int row, int nextpath);

void Init()
{
    int temp = 1<<m;
    for(int i=0; i<n; i++) {
        for(int j=0; j<temp; j++) {
            cache[i][j] = -1;
        }
    }
}

void MakePath(int index, int row, int curpath, int nextpath, int count)
{
    if(index >= m) {
        cache[row][nextpath] = max(cache[row][nextpath], f(row-1, curpath) + count);
        return;
    }
    for(int i=index; i<m; i++) {
        if(arr[row][i] == '.') {
            if(i == 0) {
                if(!(nextpath&(1<<i+1))) {
                    MakePath(i+2, row, curpath | (1<<i), nextpath, count+1);
                    continue;
                }
            } else if(i == m-1) {
                if(!(nextpath&(1<<i-1))) {
                    MakePath(i+2, row, curpath | (1<<i), nextpath, count+1);
                    continue;
                }
            } else {
                if(!(nextpath&(1<<i+1)) && !(nextpath&(1<<i-1))) {
                    MakePath(i+2, row, curpath | (1<<i), nextpath, count+1);
                    continue;
                }
            }
        }
        MakePath(i+1, row, curpath, nextpath, count);
    }
}

int f(int row, int nextpath)
{
    if(row == -1) {
        return 0;
    }
    if(cache[row][nextpath] == -1) {
        cache[row][nextpath] = 0;
        MakePath(0, row, 0, nextpath, 0);
    }
    return cache[row][nextpath];
}

int main()
{
    scanf("%d", &t);

    for(int i=0; i<t; i++) {
        scanf("%d %d", &n, &m);
        Init();

        for(int j=0; j<n; j++) {
            getchar();
            for(int k=0; k<m; k++) {
                arr[j][k] = getchar();
            }
        }

        printf("%d\n", f(n-1, 0));
    }
}