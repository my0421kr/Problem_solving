#include <iostream>
using namespace std;

int n;
int arr[17][17], cache[17][17][3];

int f(int row, int col, int flag)
{
    if(row < 1 || col < 1) {
        return 0;
    } else if(row == 1 && col == 1 && flag == 0) {
        return 1;
    }
    if(cache[row][col][flag] == -1) {
        int result = 0;
        if(flag == 0 && arr[row][col] == 0 && arr[row][col+1] == 0) {
            result = f(row, col-1, 0) + f(row-1, col-1, 1);
        } else if(flag == 1 && arr[row][col] == 0 && arr[row][col+1] == 0 && arr[row+1][col] == 0 && arr[row+1][col+1] == 0) {
            result = f(row, col-1, 0) + f(row-1, col-1, 1) + f(row-1, col, 2);
        } else if(flag == 2 && arr[row][col] == 0 && arr[row+1][col] == 0){
            result = f(row-1, col-1, 1) + f(row-1, col, 2);
        }
        cache[row][col][flag] = result;
    }
    return cache[row][col][flag];
}

int main()
{
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            scanf("%d", &arr[i][j]);
            cache[i][j][0] = -1;
            cache[i][j][1] = -1;
            cache[i][j][2] = -1;
        }
    }

    int answer = 0;
    answer += f(n, n-1, 0);
    answer += f(n-1, n-1, 1);
    answer += f(n-1, n, 2);
    printf("%d\n", answer);
}