#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef struct _Point
{
    int row, col;
} Point;
typedef struct _Node
{
    Point head, tail;
    int cost, state;
} Node;

int visited[101][101][2];
int len_board;
Point dir[4] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

bool IsValid(Point pos)
{
    return (0 <= pos.row && pos.row < len_board && 0 <= pos.col && pos.col < len_board) ? true : false;
}

bool IsEnd(Point pos)
{
    return (pos.row == len_board-1 && pos.col == len_board-1) ? true : false;
}

int BFS(vector<vector<int>> &board)
{
    queue<Node> pq;
    pq.push({{0, 0}, {0, 1}, 0, 0});

    while(!pq.empty()) {
        Point head = pq.front().head;
        Point tail = pq.front().tail;
        int cost = pq.front().cost;
        int state = pq.front().state;
        pq.pop();

        if(!IsValid(head) || !IsValid(tail)) {
            continue;
        }

        if(board[head.row][head.col] == 1 || board[tail.row][tail.col] == 1) {
            continue;
        }

        if(IsEnd(head) || IsEnd(tail)) {
            return cost;
        }

        if(visited[head.row][head.col][state] == 1) {
            continue;
        }

        visited[head.row][head.col][state] = 1;

        for(int i=0; i<4; i++) {
            pq.push({{head.row+dir[i].row, head.col+dir[i].col}, {tail.row+dir[i].row, tail.col+dir[i].col}, cost+1, state});
        }

        if(state == 0) {
            if(IsValid({head.row+1, head.col+1}) && (board[head.row+1][head.col+1] == 0) ) {
                pq.push({head, {head.row+1, head.col}, cost+1, 1});
            }
            if(IsValid({head.row-1, head.col+1}) && (board[head.row-1][head.col+1] == 0) ) {
                pq.push({{head.row-1, head.col}, head, cost+1, 1});
            }
            if(IsValid({head.row+1, head.col}) && (board[head.row+1][head.col] == 0) ) {
                pq.push({tail, {head.row+1, head.col+1}, cost+1, 1});
            }
            if(IsValid({head.row-1, head.col}) && (board[head.row-1][head.col] == 0) ) {
                pq.push({{head.row-1, head.col+1}, tail, cost+1, 1});
            }
        } else {
            if(IsValid({head.row+1, head.col+1}) && (board[head.row+1][head.col+1] == 0) ) {
                pq.push({head, {head.row, head.col+1}, cost+1, 0});
            }
            if(IsValid({head.row+1, head.col-1}) && (board[head.row+1][head.col-1] == 0) ) {
                pq.push({{head.row, head.col-1}, head, cost+1, 0});
            }
            if(IsValid({head.row, head.col+1}) && (board[head.row][head.col+1] == 0) ) {
                pq.push({tail, {head.row+1, head.col+1}, cost+1, 0});
            }
            if(IsValid({head.row, head.col-1}) && (board[head.row][head.col-1] == 0) ) {
                pq.push({{head.row+1, head.col-1}, tail, cost+1, 0});
            }
        }
    }
    return 0;
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    len_board = (int)board.size();

    answer = BFS(board);

    return answer;
}