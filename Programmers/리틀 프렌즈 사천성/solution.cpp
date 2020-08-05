#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _Node
{
    int row, col;
} Node;

vector<vector<Node>> pos;
vector<vector<char>> arr;
vector<Node> sub1, sub2;
string result;
int wholeCount;
Node dir[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void Collect(int m, int n)
{
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if('A' <= arr[i][j] && arr[i][j] <= 'Z') {
                wholeCount++;
                pos[arr[i][j] - 'A'].push_back({i, j});
            }
        }
    }
    wholeCount /= 2;
}

int Find(int m, int n)
{
    for(int i=0; i<26; i++) {
        if(!pos[i].empty()) {
            Node temp1 = pos[i][0];
            Node temp2 = pos[i][1];
            char c = arr[temp1.row][temp1.col];
            int row, col;
            sub1.clear();
            sub2.clear();

            for(int j=0; j<4; j++) {
                row = temp1.row;
                col = temp1.col;
                while( (0 <= row && row < m && 0 <= col && col < n) && (arr[row][col] == '.' || arr[row][col] == c) ) {
                    sub1.push_back({row, col});
                    row += dir[j].row;
                    col += dir[j].col;
                }
            }
            for(int j=0; j<4; j++) {
                row = temp2.row;
                col = temp2.col;
                while( (0 <= row && row < m && 0 <= col && col < n) && (arr[row][col] == '.' || arr[row][col] == c) ) {
                    sub2.push_back({row, col});
                    row += dir[j].row;
                    col += dir[j].col;
                }
            }

            int len1 = sub1.size();
            int len2 = sub2.size();
            for(int j=0; j<len1; j++) {
                for(int k=0; k<len2; k++) {
                    if(sub1[j].row == sub2[k].row && sub1[j].col == sub2[k].col) {
                        result.push_back((char)i+'A');
                        arr[pos[i][0].row][pos[i][0].col] = '.';
                        arr[pos[i][1].row][pos[i][1].col] = '.';
                        pos[i].clear();
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board) {
    string answer = "";
    result = "";
    wholeCount = 0;
    pos.resize(26);
    arr.assign(m, vector<char>(n));
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            arr[i][j] = board[i][j];
        }
    }

    Collect(m, n);

    int flag = 1;
    while(flag == 1) {
        flag = Find(m, n);
    }

    if((int)result.size() == wholeCount) {
        return result;
    } else {
        return "IMPOSSIBLE";
    }
}