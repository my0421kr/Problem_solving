#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int arr[201][201];
int cache[201][201];
int glog[101];
int p;

void Init()
{
    for(int i=0; i<201; i++) {
        for(int j=0; j<201; j++) {
            cache[i][j] = -2;
            arr[i][j] = 0;
        }
    }
    for(int i=0; i<101; i++) {
        glog[i] = 0;
    }
}

int f(int index, int target)
{
    if(index == 1) {
        if(glog[index] == target) {
            return 0;
        } else {
            return -1;
        }
    }
    if(cache[index][target] == -2) {
        int result = 2e9;
        if(target == glog[index]) {
            for(int i=1; i<=p; i++) {
                if(arr[target][i] == 1 || target == i) {
                    int temp = f(index-1, i);
                    if(temp != -1) {
                        result = min(result, temp);
                    }
                }
            }
        } else {
            for(int i=1; i<=p; i++) {
                if(arr[target][i] == 1 || target == i) {
                    int temp = f(index-1, i);
                    if(temp != -1) {
                        result = min(result, temp+1);
                    }
                }
            }
        }
        if(result == 2e9) {
            cache[index][target] = -1;
        } else {
            cache[index][target] = result;
        }
    }
    return cache[index][target];
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    int answer = 0;
    Init();

    for(int i=0; i<m; i++) {
        arr[edge_list[i][0]][edge_list[i][1]] = 1;
        arr[edge_list[i][1]][edge_list[i][0]] = 1;
    }
    p = n;
    for(int i=1; i<=k; i++) {
        glog[i] = gps_log[i-1];
    }

    answer = f(k, glog[k]);
    return answer;
}