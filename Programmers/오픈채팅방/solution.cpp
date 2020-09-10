#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

typedef struct _Node
{
    string id;
    char flag;
} Node;

map<string, string> pm;
vector<Node> mylist;
int head, tail;

void f(string &str)
{
    for(int i=0; i<str.size(); i++) {
        if(str[i] == ' ') {
            head = i+1;
            break;
        }
    }
    for(int i=str.size()-1; i>=0; i--) {
        if(str[i] == ' ') {
            tail = i-1;
            break;
        }
    }
}

vector<string> solution(vector<string> record) {
    vector<string> answer;

    for(int i=0; i<record.size(); i++) {
        f(record[i]);
        string tid = record[i].substr(head, tail-head+1);
        string name;
        if(record[i][0] != 'L') {
            name = record[i].substr(tail+2);
            pm[tid] = name;
        }
        if(record[i][0] != 'C') {
            mylist.push_back({tid, record[i][0]});
        }
    }

    for(int i=0; i<mylist.size(); i++) {
        string temp;
        temp = pm[mylist[i].id];
        if(mylist[i].flag == 'E') {
            temp += "님이 들어왔습니다.";
        } else {
            temp += "님이 나갔습니다.";
        }
        answer.push_back(temp);
    }


    return answer;
}