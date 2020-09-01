#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _Node
{
    string name;
    int index;
} Node;

vector<Node> mylist;

bool cmp(Node a, Node b)
{
    return a.index < b.index;
}

bool IsThere(int head, int tail, string &target, int index)
{
    for(int i=head; i<=tail; i++) {
        if(target.compare(mylist[i].name) == 0) {
            mylist[i].index = index;
            sort(mylist.begin()+head, mylist.end(), cmp);
            return true;
        }
    }
    return false;
}

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;

    for(int i=0; i<cities.size(); i++) {
        for(int j=0; j<cities[i].size(); j++) {
            if('A' <= cities[i][j] && cities[i][j] <= 'Z') {
                cities[i][j] -= 'A' - 'a';
            }
        }
    }

    int head = 0, tail = -1;
    for(int i=0; i<cities.size(); i++) {
        if(IsThere(head, tail, cities[i], i)) {
            answer++;
        } else {
            answer+=5;
            mylist.push_back({cities[i], i});
            if(tail - head + 1 == cacheSize) {
                head++;
                tail++;
            } else {
                tail++;
            }
        }
    }

    return answer;
}