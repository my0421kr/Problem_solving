#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<vector<int>>> cache;
vector<vector<int>> arr;

int f(int row, int col, int flag)
{
    if(row < 0 || row >= n || col < 0 || col >= m) {
        return -1e9;
    } else if(cache[row][col][flag] == -2e9) {
        int result = -2e9;
        if(flag == 0) {
            result = max(result, f(row, col-1, 0));
            result = max(result, f(row, col-1, 1));
        } else if(flag == 1) {
            result = max(result, f(row-1, col, 0));
            result = max(result, f(row-1, col, 1));
            result = max(result, f(row-1, col, 2));
        } else {
            result = max(result, f(row, col+1, 1));
            result = max(result, f(row, col+1, 2));
        }
        cache[row][col][flag] = result + arr[row][col];
    }
    return cache[row][col][flag];
}

int main()
{
    scanf("%d %d", &n, &m);
    arr.assign(n, vector<int>(m));
    cache.assign(n, vector<vector<int>>(m, vector<int>(3, -2e9)));

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    cache[0][0][0] = arr[0][0];
    cache[0][0][1] = arr[0][0];
    cache[0][0][2] = arr[0][0];

    int answer = -2e9;
    for(int i=0; i<3; i++) {
        answer = max(answer, f(n-1, m-1, i));
    }
    printf("%d\n", answer);

}