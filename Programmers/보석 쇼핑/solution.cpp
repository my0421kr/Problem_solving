#include <string>
#include <vector>
#include <map>

using namespace std;
map<string, int> pm;
vector<int> mylist, cntlist;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    mylist.resize((int)gems.size());
    int rh, rt;

    int cnt = 0, head = 0, tail;
    for(int i=0; i<gems.size(); i++) {
        if(pm[gems[i]] == 0) {
            pm[gems[i]] = ++cnt;
            mylist[i] = cnt;
            tail = i;
        } else {
            mylist[i] = pm[gems[i]];
        }
    }
    cntlist.assign(cnt+1, 0);
    rh = head;
    rt = tail;
    for(int i=0; i<=tail; i++) {
        cntlist[mylist[i]]++;
    }
    while(1) {
        if(tail - head < rt - rh) {
            rh = head;
            rt = tail;
        }
        if(cntlist[mylist[head]] == 1) {
            tail++;
            if(tail < (int)gems.size()) {
                cntlist[mylist[tail]]++;
            } else {
                break;
            }
        } else {
            cntlist[mylist[head]]--;
            head++;
        }
    }
    answer.push_back(rh+1);
    answer.push_back(rt+1);

    return answer;
}