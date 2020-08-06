#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    int row, col;
} Node;

int n, l;
int cache[21][21][21][21][21];
int arr[21][21];
vector<Node> dir;

void Init()
{
    int i, j, k, p, q;
    for(i=1; i<=n; i++) {
        for(j=1; j<=n; j++) {
            for(k=1; k<=n; k++) {
                for(p=1; p<=n; p++) {
                    for(q=1; q<=l; q++) {
                        cache[i][j][k][p][q] = -1;
                        if(q == 1) {
                            if(i == k && j == p) {
                                cache[i][j][k][p][q] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(i == 1 && j == 1) {
                continue;
            } else {
                dir.push_back({i-1, j-1});
            }
        }
    }
}

bool IsValid(int r, int c)
{
    return ( (1 <= r && r <= n) && (1 <= c && c <= n) ) ? true : false;
}

int f(int row1, int col1, int row2, int col2, int count)
{
    if(!IsValid(row1, col1) || !IsValid(row2, col2)) {
        return 0;
    }
    if(cache[row1][col1][row2][col2][count] == -1) {
        if(arr[row1][col1] != arr[row2][col2]) {
            cache[row1][col1][row2][col2][count] = 0;
        } else {
            int result = 0;
            if(count == 2) {
                int i;
                for(i=0; i<8; i++) {
                    if( (row1+dir[i].row == row2) && (col1+dir[i].col == col2) ) {
                        result = 1;
                        break;
                    }
                }
                if(i == 8) {
                    result = 0;
                }
            } else {
                for(int i=0; i<8; i++) {
                    for(int j=0; j<8; j++) {
                        result += f(row1+dir[i].row, col1+dir[i].col, row2+dir[j].row, col2+dir[j].col, count-2);
                    }
                }
            }
            cache[row1][col1][row2][col2][count] = result;
            cache[row2][col2][row1][col1][count] = result;
        }
        
    }
    return cache[row1][col1][row2][col2][count];
}

int main()
{
    scanf("%d %d", &n, &l);

    Init();
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int answer = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            for(int k=1; k<=n; k++) {
                for(int p=1; p<=n; p++) {
                    answer += f(i, j, k, p, l);
                }
            }
        }
    }
    printf("%d\n", answer);
}