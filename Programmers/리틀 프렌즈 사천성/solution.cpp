// Not solved
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

typedef struct _Point
{
    int row, col;
} Point;
typedef struct _Node
{
    vector<int> child1, child2;
} Node;
typedef struct _cmp
{
    bool operator()(int a, int b) {
        return a > b;
    }
} cmp;

vector<vector<Point>> arr_pos;
vector<Node> arr;
int parent1[26], parent2[26], exist[26];

void MakeConnect(int index, vector<string> &board)
{
    Point a = arr_pos[index][0];
    Point b = arr_pos[index][1];
    int start_row = min(a.row, b.row);
    int start_col = min(a.col, b.col);
    int end_row = max(a.row, b.row);
    int end_col = max(a.col, b.col);

    int flag1 = 0, flag2 = 0;
    if( (start_row == a.row && start_col == a.col) || (start_row == b.row && start_col == b.col) ) {
        flag1 = 1;
    } else {
        flag2 = 1;
    }

    vector<int> temp1, temp2;
    temp1.assign(26, 0);
    temp2.assign(26, 0);
    for(int i=start_row; i<=end_row; i++) {
        for(int j=start_col; j<=end_col; j++) {

            if(board[i][j]-'A' == index) {
                continue;
            }

            if(flag1 == 1) {

                if(i == start_row || j == end_col) {
                    if('A' <= board[i][j] && board[i][j] <= 'Z') {
                        temp1[board[i][j]-'A'] = 1;
                    } else if(board[i][j] == '*') {
                        parent1[index]++;
                    }
                }
                if(i == end_row || j == start_col) {
                    if('A' <= board[i][j] && board[i][j] <= 'Z') {
                        temp2[board[i][j]-'A'] = 1;
                    } else if(board[i][j] == '*') {
                        parent2[index]++;
                    }
                }

            } else {

                if(i == start_row || j == start_col) {
                    if('A' <= board[i][j] && board[i][j] <= 'Z') {
                        temp1[board[i][j]-'A'] = 1;
                    } else if(board[i][j] == '*') {
                        parent1[index]++;
                    }
                }
                if(i == end_row || j == end_col) {
                    if('A' <= board[i][j] && board[i][j] <= 'Z') {
                        temp2[board[i][j]-'A'] = 1;
                    } else if(board[i][j] == '*') {
                        parent2[index]++;
                    }
                }

            }

        }
    }
    for(int i=0; i<26; i++) {
        if(temp1[i] == 1) {
            arr[i].child1.push_back(index);
            parent1[index]++;
        }
        if(temp2[i] == 1) {
            arr[i].child2.push_back(index);
            parent2[index]++;
        }
    }
    temp1.clear();
    temp2.clear();
}

void MakeGraph(vector<string> &board)
{
    for(int i=0; i<26; i++) {
        if(arr_pos[i].size() != 0) {
            MakeConnect(i, board);
        }
    }
    // for(int i=0; i<26; i++) {
    //     if(exist[i] == 1) {
    //         printf("%c ", (char)i + 'A');
    //         printf("%d %d\n", parent1[i], parent2[i]);
    //     }
    // }
}

string TopoloSort()
{
    string result = "";
    priority_queue<int, vector<int>, cmp> pq;
    for(int i=0; i<26; i++) {
        if((parent1[i] == 0 || parent2[i] == 0) && (exist[i] == 1) ) {
            pq.push(i);
        }
    }

    while(!pq.empty()) {
        int num = pq.top();
        pq.pop();
        if(exist[num] == 0) {
            continue;
        }
        exist[num] = 0;
        result.push_back((char)num + 'A');

        int len1 = (int)arr[num].child1.size();
        int len2 = (int)arr[num].child2.size();

        for(int i=0; i<len1; i++) {
            parent1[arr[num].child1[i]]--;
        }
        for(int i=0; i<len2; i++) {
            parent2[arr[num].child2[i]]--;
        }

        for(int i=0; i<len1; i++) {
            if(parent1[arr[num].child1[i]] == 0) {
                pq.push(arr[num].child1[i]);
            }
        }
        for(int i=0; i<len2; i++) {
            if(parent2[arr[num].child2[i]] == 0) {
                pq.push(arr[num].child2[i]);
            }
        }
    }
    return result;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board) {
    string answer = "";
    arr_pos.resize(26);
    arr.resize(26);

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if('A' <= board[i][j] && board[i][j] <= 'Z') {
                exist[board[i][j]-'A'] = 1;
                arr_pos[board[i][j]-'A'].push_back({i, j});
            }
        }
    }

    MakeGraph(board);
    answer = TopoloSort();
    for(int i=0; i<26; i++) {
        if(exist[i] == 1) {
            return "IMPOSSIBLE";
        }
    }
    return answer;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int m, n;
    scanf("%d %d", &m, &n);
    vector<string> input;
    input.resize(m);
    for(int i=0; i<m; i++) {
        cin >> input[i];
    }

    cout << solution(m, n, input) << endl;
}