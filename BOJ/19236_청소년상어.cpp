#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct _Node
{
    int num, dir;
} Node;
typedef struct _Point
{
    int row, col;
} Point;

vector<vector<Node>> first;
Point dir_set[8] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}};

bool IsValid(int row, int col)
{
    return (0 <= row && row < 4 && 0 <= col && col < 4) ? true : false;
}

bool IsShark(int row, int col, Point shark)
{
    return (row == shark.row && col == shark.col) ? true : false;
}

void Move(Point shark, vector<vector<Node>> &arr)
{
    vector<Point> mylist;
    mylist.assign(17, {-1, -1});
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(arr[i][j].num != 0) {
                mylist[arr[i][j].num] = {i, j};
            }
        }
    }

    for(int i=1; i<=16; i++) {
        if(mylist[i].row != -1) {
            int row = mylist[i].row;
            int col = mylist[i].col;
            while(1) {
                int dir = arr[row][col].dir;
                int nr = row+dir_set[dir].row;
                int nc = col+dir_set[dir].col;
                if(IsValid(nr, nc) && !IsShark(nr, nc, shark)) {
                    Node temp = arr[nr][nc];
                    arr[nr][nc] = arr[row][col];
                    arr[row][col] = temp;
                    mylist[i] = {nr, nc};
                    mylist[arr[row][col].num] = {row, col};
                    break;
                } else {
                    arr[row][col].dir += 1;
                    arr[row][col].dir %= 8;
                }
            }
        }
    }
    mylist.clear();
}

void rArr(vector<vector<Node>> &arr)
{
    for(int i=0; i<4; i++) {
        arr[i].clear();
    }
    arr.clear();
}

int DFS(Point shark, vector<vector<Node>> &arrOfParent)
{
    int result = 0;
    vector<vector<Node>> arrCur;
    arrCur.assign(4, vector<Node>(4));
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            arrCur[i][j] = arrOfParent[i][j];
        }
    }

    arrCur[shark.row][shark.col].num = 0;
    Move(shark, arrCur);

    int row = shark.row;
    int col = shark.col;
    int dir = arrCur[row][col].dir;
    
    while(1) {
        row += dir_set[dir].row;
        col += dir_set[dir].col;
        if(!IsValid(row, col)) {
            rArr(arrCur);
            return result;
        } else if(arrCur[row][col].num != 0) {
            result = max(result, DFS({row, col}, arrCur) + arrCur[row][col].num);
        }
    }
}

int main()
{
    first.assign(4, vector<Node>(4));

    int num, dir;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            scanf("%d %d", &num, &dir);
            first[i][j] = {num, dir-1};
        }
    }

    printf("%d\n", DFS({0,0}, first) + first[0][0].num);
}