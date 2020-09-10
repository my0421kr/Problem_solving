#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<string> url;
vector<int> score;
vector<double> linkscore;
vector<vector<int>> linklist;
map<string, int> pm, pm2;

string Url(string &str)
{
    int head = str.find("<head>");
    int tail = str.find("</head>", head);
    string target = str.substr(head, tail-head);
    string sen;
    head = 0;
    vector<int> mylist;
    while(1) {
        head = target.find("<meta", head+1);
        if(head == string::npos) {
            break;
        } else {
            mylist.push_back(head);
        }
    }
    mylist.push_back(tail);
    for(int i=0; i<mylist.size()-1; i++) {
        sen = target.substr(mylist[i], mylist[i+1] - mylist[i]);
        head = sen.find("https:");
        if(head != string::npos) {
            for(int j=head; j<sen.size(); j++) {
                if(sen[j] == '"') {
                    tail = j;
                    break;
                }
            }
        }
    }
    mylist.clear();
    return sen.substr(head, tail-head);
}

int Score(string &word, string &str)
{
    int count = 0;
    int head = 0;
    while(1) {
        head = str.find(word, head+1);
        if(head != string::npos) {
            if( (str[head+word.size()] < 'a' || 'z' < str[head+word.size()]) && (str[head-1] < 'a' || 'z' < str[head-1]) ) {
                count++;
            }
        } else {
            return count;
        }
    }
}

void Link(int index, string &str)
{
    int head = 0;
    int tail;
    while(1) {
        head = str.find("<a href", head+1);
        if(head != string::npos) {
            head = str.find("https:", head);
            tail = head;
            while(str[tail] != '"') {
                tail++;
            }
            if(pm2[str.substr(head, tail-head)] != 1) {
                linklist[index].push_back(-1);
            } else {
                linklist[index].push_back(pm[str.substr(head, tail-head)]);
            }
        } else {
            return;
        }
    }
}

int solution(string word, vector<string> pages) {
    int answer = 0;
    linklist.resize(pages.size());
    linkscore.assign(pages.size(), 0);

    for(int i=0; i<pages.size(); i++) {
        for(int j=0; j<pages[i].size(); j++) {
            if('A' <= pages[i][j] && pages[i][j] <= 'Z') {
                pages[i][j] -= ('A' - 'a');
            }
        }
    }
    for(int i=0; i<word.size(); i++) {
        if('A' <= word[i] && word[i] <= 'Z') {
            word[i] -= ('A' - 'a');
        }
    }

    for(int i=0; i<pages.size(); i++) {
        url.push_back(Url(pages[i]));
        pm[url[i]] = i;
        pm2[url[i]] = 1;
    }
    for(int i=0; i<pages.size(); i++) {
        score.push_back(Score(word, pages[i]));
    }
    for(int i=0; i<pages.size(); i++) {
        Link(i, pages[i]);
    }

    for(int i=0; i<pages.size(); i++) {
        for(int j=0; j<linklist[i].size(); j++) {
            if(linklist[i][j] != -1) {
                linkscore[linklist[i][j]] += ((double)score[i] / (double)linklist[i].size());
            }
        }
    }
    double max = 0;
    for(int i=0; i<pages.size(); i++) {
        if(-0.000001 <= linkscore[i] + (double)score[i] - max && linkscore[i] + (double)score[i] - max <= 0.000001) {
            continue;
        } else if(linkscore[i] + (double)score[i] > max) {
            max = linkscore[i] + (double)score[i];
            answer = i;
        }
    }

    return answer;
}