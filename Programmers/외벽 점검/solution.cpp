#include <string>
#include <vector>

using namespace std;

int len_weak;
int len_dist;
vector<int> arr;
int visit[8];
int result = 100;

void DFS(int head, int count, vector<int> &dist)
{
    int i, j;
    if(head == len_weak) {
        result = min(result, count);
        return;
    } else {
        for(i=0; i<len_dist; i++) {
            if(visit[i] != 1) {
                for(j=head; j<=len_weak; j++) {
                    if(arr[j] - arr[head] > dist[i]) {
                        visit[i] = 1;
                        DFS(j, count+1, dist);
                        visit[i] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void Init_Visit()
{
    for(int i=0; i<len_dist; i++) {
        visit[i] = 0;
    }
}

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = 0;
    int i, j, k, count, first_index, temp;

    len_weak = (int)weak.size();
    len_dist = (int)dist.size();

    
    for(k=0; k<len_weak; k++) {
        Init_Visit();
        arr.clear();
        first_index = k;
        temp = weak[first_index];
        for(i=k, count=0; count<len_weak; i=(i+1)%len_weak, count++) {
            arr.push_back((weak[i] - temp + n)%n);
            temp = weak[i];
        }
        arr.push_back(1000000);
        for(i=1; i<len_weak; i++) {
            arr[i] += arr[i-1];
        }

        for(i=0; i<len_dist; i++) {
            for(j=0; j<=len_weak; j++) {
                if(arr[j] - arr[0] > dist[i]) {
                    printf("%d\n", j);
                    visit[i] = 1;
                    DFS(j, 1, dist);
                    visit[i] = 0;
                    break;
                }
            }
        }
    }

    if(result == 100) {
        answer = -1;
    } else {
        answer = result;
    }

    return answer;
}