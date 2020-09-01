#include <string>
#include <vector>

using namespace std;

vector<vector<int>> target;

bool rSearch(int m, int n, vector<string> &arr)
{
    bool result = false;
    for(int i=0; i<m-1; i++) {
        for(int j=0; j<n-1; j++) {
            if(arr[i][j] == '.') {
                continue;
            } else if(arr[i][j] == arr[i][j+1] && arr[i][j] == arr[i+1][j] && arr[i][j] == arr[i+1][j+1]) {
                result = true;
                target[i][j] = 1;
                target[i][j+1] = 1;
                target[i+1][j] = 1;
                target[i+1][j+1] = 1;
            }
        }
    }
    return result;
}

void rPop(int m, int n, vector<string> &arr)
{
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(target[i][j] == 1) {
                arr[i][j] = '.';
            }
        }
    }
}

void rPush(int m, int n, vector<string> &arr)
{
    vector<string> temp;
    vector<char> pv;
    temp.assign(m, string(n, '.'));
    for(int j=0; j<n; j++) {
        for(int i=m-1; i>=0; i--) {
            if(arr[i][j] != '.') {
                pv.push_back(arr[i][j]);
            }
        }
        for(int i=0; i<pv.size(); i++) {
            temp[m-1-i][j] = pv[i];
        }
        pv.clear();
    }
    arr = temp;
}

int solution(int m, int n, vector<string> board) {
    int answer = 0;

    while(1) {
        for(int i=0; i<target.size(); i++) {
            target[i].clear();
        }
        target.clear();
        target.assign(m, vector<int>(n, 0));

        if(!rSearch(m, n, board)) {
            break;
        }
        rPop(m, n, board);
        rPush(m, n, board);
    }
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(board[i][j] == '.') {
                answer++;
            }
        }
    }

    return answer;
}