#include <string>
#include <vector>

using namespace std;

int len;
int mylist[256];

bool IsOk(int visit, vector<vector<string>> &arr)
{
    int flag;
    for(int i=0; i<arr.size(); i++) {
        for(int j=i+1; j<arr.size(); j++) {
            flag = 0;
            for(int k=0; k<len; k++) {
                if(visit & (1<<k)) {
                    if(arr[i][k].compare(arr[j][k]) == 0) {
                        flag += (1<<k);
                    }
                }
            }
            if(visit == flag) {
                return false;
            }
        }
    }
    return true;
}

void f(int visit, int index, vector<vector<string>> &arr)
{
    if(index == len) {
        if(IsOk(visit, arr)) {
            mylist[visit] = 1;
        }
        return;
    }
    f((1<<index)|visit, index+1, arr);
    f(visit, index+1, arr);
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    len = relation[0].size();

    f(0, 1, relation);
    f(1, 1, relation);

    int num = (1<<len);
    for(int i=0; i<num; i++) {
        if(mylist[i] == 1) {
            for(int j=i+1; j<num; j++) {
                if(mylist[j] == 1 && ((i & j) == i)) {
                    mylist[j] = 0;
                }
            }
        }
    }
    for(int i=0; i<num; i++) {
        if(mylist[i] == 1) {
            answer++;
        }
    }

    return answer;
}