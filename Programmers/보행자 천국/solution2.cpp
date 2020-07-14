// top-down
#include <vector>

using namespace std;

int MOD = 20170805;
int cache[2][500][500];
int len_row, len_col;
vector<vector<int>> arr;

void Init_Cache()
{
    for(int i=0; i<len_row; i++) {
        for(int j=0; j<len_col; j++) {
            cache[0][i][j] = -1;
            cache[1][i][j] = -1;
        }
    }
    cache[0][0][0] = 1;
    cache[1][0][0] = 0;
}

bool IsValidIndex(int row, int col)
{
    return ( (0 <= row && row < len_row) && (0 <= col && col < len_col) ) ? true : false;
}

int function(int flag, int row, int col)
{
    int prev_row, prev_col;

    if(cache[flag][row][col] == -1) {

        if(arr[row][col] == 1) {
            cache[flag][row][col] = 0;
            return 0;
        }

        if(flag == 0) {
            prev_row = row;
            prev_col = col-1;
        } else {
            prev_row = row-1;
            prev_col = col;
        }

        if(IsValidIndex(prev_row, prev_col)) {
            if(arr[prev_row][prev_col] == 0) {
                cache[flag][row][col] = function(0, prev_row, prev_col) + function(1, prev_row, prev_col);
            } else {
                cache[flag][row][col] = function(flag, prev_row, prev_col);
            }
        } else {
            cache[flag][row][col] = 0;
        }

        cache[flag][row][col] %= MOD;

    }

    return cache[flag][row][col];
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    arr = city_map;
    len_row = m;
    len_col = n;
    Init_Cache();

    answer = function(0, m-1, n-1) + function(1, m-1, n-1);
    answer %= MOD;
    return answer;
}