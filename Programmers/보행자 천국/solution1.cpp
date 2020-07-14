// botton-up
#include <vector>

using namespace std;

int MOD = 20170805;
int cache[2][501][501];

void Init(int m, int n)
{
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            cache[0][i][j] = 0;
            cache[1][i][j] = 0;
        }
    }
}


// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;

    Init(m, n);
    cache[0][0][0] = 1;
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(city_map[i][j] == 0) {
                cache[0][i][j+1] += cache[0][i][j] + cache[1][i][j];
                cache[0][i][j+1] %= MOD;
                cache[1][i+1][j] += cache[0][i][j] + cache[1][i][j];
                cache[1][i+1][j] %= MOD;
            } else if(city_map[i][j] == 2){
                cache[0][i][j+1] += cache[0][i][j];
                cache[0][i][j+1] %= MOD;
                cache[1][i+1][j] += cache[1][i][j];
                cache[1][i+1][j] %= MOD;
            }
        }
    }
    answer = cache[0][m-1][n-1] + cache[1][m-1][n-1];
    answer %= MOD;

    return answer;
}