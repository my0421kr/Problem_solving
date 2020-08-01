#include <iostream>
#include <vector>
using namespace std;

typedef struct _Shark
{
    int speed, direction, big;
} Shark;
typedef struct _Point
{
    int row, col;
} Point;

int r, c, m, answer = 0;
Point dir[5] = {{0,0}, {-1,0}, {1,0}, {0,1}, {0,-1}};
vector<Shark> arr[101][101];
vector<Shark> temp_arr[101][101];

void Catch(int col)
{
    for(int i=1; i<=r; i++) {
        if(arr[i][col].size() != 0) {
            answer += arr[i][col][0].big;
            arr[i][col].clear();
            break;
        }
    }
}

void CheckValid(Shark &target, Point &dest)
{
    if(dest.row < 1) {
        dest.row = -dest.row + 2;
        target.direction = 2;
    } else if(dest.row > r) {
        dest.row = r*2 - dest.row;
        target.direction = 1;
    } else if(dest.col < 1) {
        dest.col = -dest.col + 2;
        target.direction = 3;
    } else if(dest.col > c) {
        dest.col = c*2 - dest.col;
        target.direction = 4;
    }
}

void Move()
{
    Shark target;
    Point dest;
    for(int i=1; i<=r; i++) {
        for(int j=1; j<=c; j++) {
            if(arr[i][j].size() != 0) {
                target = arr[i][j][0];
                arr[i][j].clear();

                dest = {i + (dir[target.direction].row * target.speed), j + (dir[target.direction].col * target.speed)};
                CheckValid(target, dest);
                CheckValid(target, dest);
                temp_arr[dest.row][dest.col].push_back(target);
            }
        }
    }
}

void DeleteDup()
{
    for(int i=1; i<=r; i++) {
        for(int j=1; j<=c; j++) {

            int num_shark = (int)temp_arr[i][j].size();

            if(num_shark != 0) {
                Shark max_shark = {0,0,0};
                for(int k=0; k<num_shark; k++) {
                    if(temp_arr[i][j][k].big > max_shark.big) {
                        max_shark = temp_arr[i][j][k];
                    }
                }
                temp_arr[i][j].clear();
                arr[i][j].push_back(max_shark);
            }

        }
    }
}

int main()
{
    scanf("%d %d %d", &r, &c, &m);

    int row, col, speed, direction, big;
    for(int i=0; i<m; i++) {
        scanf("%d %d %d %d %d", &row, &col, &speed, &direction, &big);
        if(direction == 1 || direction == 2) {
            arr[row][col].push_back({speed%(2*(r-1)), direction, big});
        } else {
            arr[row][col].push_back({speed%(2*(c-1)), direction, big});
        }
    }

    int cur_col = 0;
    while(cur_col < c) {
        cur_col++;
        Catch(cur_col);
        Move();
        DeleteDup();
    }
    printf("%d\n", answer);
}