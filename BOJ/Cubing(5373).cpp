#include <iostream>
#include <vector>

using namespace std;

typedef struct _Node
{
    char color[6];
} Node;

typedef struct _Command
{
    char face, clock;
} Command;

int t, n;
Node arr[3][3][3];

void Print()
{
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            printf("%c", arr[i][j][2].color[2]);
        }
        printf("\n");
    }
}

void RotateFace(vector<vector<Node>> &arr, char clock)
{
    vector<vector<Node>> result(3, vector<Node>(3, {0,0,0,0,0,0}));
    if(clock == '+') {
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                result[i][j] = arr[2-j][i];
            }
        }
    } else {
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                result[i][j] = arr[j][2-i];
            }
        }
    }
    arr = result;
}

void RotateSide(Node &dice, char face, char clock)
{
    char temp;
    if( (face == 'L' && clock == '+') || (face == 'R' && clock == '-') ) {
        temp = dice.color[0];
        dice.color[0] = dice.color[1];
        dice.color[1] = dice.color[2];
        dice.color[2] = dice.color[3];
        dice.color[3] = temp;
    } else if( (face == 'L' && clock == '-') || (face == 'R' && clock == '+') ) {
        temp = dice.color[0];
        dice.color[0] = dice.color[3];
        dice.color[3] = dice.color[2];
        dice.color[2] = dice.color[1];
        dice.color[1] = temp;
    } else if( (face == 'F' && clock == '+') || (face == 'B' && clock == '-') ) {
        temp = dice.color[0];
        dice.color[0] = dice.color[5];
        dice.color[5] = dice.color[2];
        dice.color[2] = dice.color[4];
        dice.color[4] = temp;
    } else if( (face == 'F' && clock == '-') || (face == 'B' && clock == '+') ) {
        temp = dice.color[0];
        dice.color[0] = dice.color[4];
        dice.color[4] = dice.color[2];
        dice.color[2] = dice.color[5];
        dice.color[5] = temp;
    } else if( (face == 'U' && clock == '+') || (face == 'D' && clock == '-') ) {
        temp = dice.color[1];
        dice.color[1] = dice.color[5];
        dice.color[5] = dice.color[3];
        dice.color[3] = dice.color[4];
        dice.color[4] = temp;
    } else if( (face == 'U' && clock == '-') || (face == 'D' && clock == '+') ) {
        temp = dice.color[1];
        dice.color[1] = dice.color[4];
        dice.color[4] = dice.color[3];
        dice.color[3] = dice.color[5];
        dice.color[5] = temp;
    }

}

void Rotate(Command com)
{
    vector<vector<Node>> cur(3, vector<Node>(3, {0,0,0,0,0,0}));
    int i, j, k;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(com.face == 'D'){
                cur[i][j] = arr[2-i][j][0];
            } else if(com.face == 'F') {
                cur[i][j] = arr[2][j][2-i];
            } else if(com.face == 'U') {
                cur[i][j] = arr[i][j][2];
            } else if(com.face == 'B') {
                cur[i][j] = arr[0][j][i];
            } else if(com.face == 'L') {
                cur[i][j] = arr[j][0][2-i];
            } else if(com.face == 'R') {
                cur[i][j] = arr[2-j][2][2-i];
            }
        }
    }
    RotateFace(cur, com.clock);
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            RotateSide(cur[i][j], com.face, com.clock);
        }
    }
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(com.face == 'D'){
                arr[2-i][j][0] = cur[i][j];
            } else if(com.face == 'F') {
                arr[2][j][2-i] = cur[i][j];
            } else if(com.face == 'U') {
                arr[i][j][2] = cur[i][j];
            } else if(com.face == 'B') {
                arr[0][j][i] = cur[i][j];
            } else if(com.face == 'L') {
                arr[j][0][2-i] = cur[i][j];
            } else if(com.face == 'R') {
                arr[2-j][2][2-i] = cur[i][j];
            }
        }
    }
}

void Init_Cube()
{
    int i, j, k;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            for(k=0; k<3; k++) {
                if(i == 0) {
                    arr[i][j][k].color[3] = 'o';
                } else if(i == 2) {
                    arr[i][j][k].color[1] = 'r';
                }
                if(j == 0) {
                    arr[i][j][k].color[4] = 'g';
                } else if(j == 2) {
                    arr[i][j][k].color[5] = 'b';
                }
                if(k == 0) {
                    arr[i][j][k].color[0] = 'y';
                } else if(k == 2) {
                    arr[i][j][k].color[2] = 'w';
                }
            }
        }
    }
}

int main()
{
    scanf("%d", &t);

    Command com;
    for(int i=0; i<t; i++) {
        Init_Cube();
        scanf("%d", &n);

        for(int j=0; j<n; j++) {
            getchar();
            com.face = getchar();
            com.clock = getchar();
            Rotate(com);
        }
        Print();
    }
    
}