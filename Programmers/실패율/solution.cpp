#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _Node
{
    int index;
    double ratio;
} Node;

vector<Node> mylist;

bool cmp(Node a, Node b)
{
    if(a.ratio > b.ratio) {
        return true;
    } else if(a.ratio == b.ratio) {
        if(a.index < b.index) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;

    sort(stages.begin(), stages.end());
    for(int i=1; i<=N; i++) {
        int head, tail;
        head = lower_bound(stages.begin(), stages.end(), i) - stages.begin();
        tail = upper_bound(stages.begin(), stages.end(), i) - stages.begin();
        if(head == tail) {
            mylist.push_back({i, 0});
        } else if(tail == stages.size()) {
            mylist.push_back({i, 1});
        } else {
            mylist.push_back({i, (double)(tail - head) / (double)(stages.size() - head)});
        }
    }
    sort(mylist.begin(), mylist.end(), cmp);
    for(int i=0; i<mylist.size(); i++) {
        answer.push_back(mylist[i].index);
    }

    return answer;
}