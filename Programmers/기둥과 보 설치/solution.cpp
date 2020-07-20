#include <string>
#include <vector>

using namespace std;

int pillar[101][101];
int paper[101][101];
int len;
int numOfCom;

bool ConditionPillar1(int row, int col)
{
    if(col == 0) {
        return true;
    } else if(row == 0) {
        if(paper[row][col] == 1) {
            return true;
        } else {
            return false;
        }
    } else if(row == len) {
        if(paper[row-1][col] == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        if(paper[row][col] == 1 || paper[row-1][col] == 1) {
            return true;
        } else {
            return false;
        }
    }
}

bool ConditionPillar2(int row, int col)
{
    if(col == 0) {
        return false;
    } else if(pillar[row][col-1] == 1) {
        return true;
    } else {
        return false;
    }
}

bool ConditionPaper1(int row, int col)
{
    if(pillar[row][col-1] == 1 || pillar[row+1][col-1] == 1) {
        return true;
    } else {
        return false;
    }
}

bool ConditionPaper2(int row, int col)
{
    if(row == 0 || row == len-1) {
        return false;
    } else if(paper[row-1][col] == 1 && paper[row+1][col] == 1) {
        return true;
    } else {
        return false;
    }
}

void CreatePillar(int row, int col)
{
    if(row < 0 || row > len || col < 0 || col >= len) {
        return;
    } else if(ConditionPillar1(row, col) || ConditionPillar2(row, col)) {
        pillar[row][col] = 1;
    }
}

void CreatePaper(int row, int col)
{
    if(row < 0 || row >= len || col <= 0 || col > len) {
        return;
    } else if(ConditionPaper1(row, col) || ConditionPaper2(row, col)) {
        paper[row][col] = 1;
    }
}

void RemovePillar(int row, int col)
{
    pillar[row][col] = 0;
    for(int i=0; i<=len; i++) {
        for(int j=0; j<=len; j++) {
            if(pillar[i][j] == 1) {
                if(!ConditionPillar1(i, j) && !ConditionPillar2(i, j)) {
                    pillar[row][col] = 1;
                    return;
                }
            }
            if(paper[i][j] == 1) {
                if(!ConditionPaper1(i, j) && !ConditionPaper2(i, j)) {
                    pillar[row][col] = 1;
                    return;
                }
            }
        }
    }

}

void RemovePaper(int row, int col)
{
    paper[row][col] = 0;
    for(int i=0; i<=len; i++) {
        for(int j=0; j<=len; j++) {
            if(pillar[i][j] == 1) {
                if(!ConditionPillar1(i, j) && !ConditionPillar2(i, j)) {
                    paper[row][col] = 1;
                    return;
                }
            }
            if(paper[i][j] == 1) {
                if(!ConditionPaper1(i, j) && !ConditionPaper2(i, j)) {
                    paper[row][col] = 1;
                    return;
                }
            }
        }
    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;

    len = n;
    numOfCom = (int)build_frame.size();

    for(int i=0; i<numOfCom; i++) {
        if(build_frame[i][2] == 0) {
            if(build_frame[i][3] == 0) {
                RemovePillar(build_frame[i][0], build_frame[i][1]);
            } else {
                CreatePillar(build_frame[i][0], build_frame[i][1]);
            }
        } else {
            if(build_frame[i][3] == 0) {
                RemovePaper(build_frame[i][0], build_frame[i][1]);
            } else {
                CreatePaper(build_frame[i][0], build_frame[i][1]);
            }
        }
    }
    vector<int> temp;
    for(int i=0; i<=len; i++) {
        for(int j=0; j<=len; j++) {
            if(pillar[i][j] == 1) {
                temp = {i, j, 0};
                answer.push_back(temp);
            }
            if(paper[i][j] == 1) {
                temp = {i, j, 1};
                answer.push_back(temp);
            }
        }
    }

    return answer;
}