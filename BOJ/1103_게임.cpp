#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
int visit[50][50];
int cache[50][50];
int dir[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
char arr[50][50];

int DFS(int row, int col)
{
    if(row < 0 || row >= n || col < 0 || col >= m) {
        return 0;
    } else if(arr[row][col] == 'H') {
        return 0;
    }
    if(visit[row][col] == 1) {
        return -1;
    }
    if(cache[row][col] != -1) {
        return cache[row][col];
    }
    visit[row][col] = 1;
    int result = 0;
    for(int i=0; i<4; i++) {
        int temp = DFS(row + dir[0][i] * (arr[row][col] - '0'), col + dir[1][i] * (arr[row][col] - '0'));
        if(temp == -1) {
            return -1;
        }
        result = max(result, temp+1);
    }
    cache[row][col] = result;
    visit[row][col] = 0;
    return result;
}

void InitCache()
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cache[i][j] = -1;
        }
    }
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
    InitCache();
    printf("%d\n", DFS(0, 0));
}