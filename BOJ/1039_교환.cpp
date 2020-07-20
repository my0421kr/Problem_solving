#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct _Node
{
    string str;
    int cost;
} Node;

int n, k, last_result = 0, len = 0;
int visit[11][1000001];
string arr;

void BFS()
{
    queue<Node> pq;
    pq.push({arr, 0});

    while(!pq.empty()) {
        string num = pq.front().str;
        int numInt = stoi(num);
        int cost = pq.front().cost;
        pq.pop();

        if(visit[cost][numInt] == 1) {
            continue;
        }
        if(cost == k) {
            last_result = max(last_result, numInt);
            continue;
        }

        visit[cost][numInt] = 1;
        for(int i=0; i<len; i++) {
            for(int j=i+1; j<len; j++) {
                if(i == 0 && num[j] == '0') {
                    continue;
                } else {
                    swap(num[i], num[j]);
                    pq.push({num, cost+1});
                    swap(num[i], num[j]);
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &k);
    
    arr = to_string(n);
    len = (int)arr.size();

    BFS();
    if(last_result == 0) {
        printf("-1\n");
    } else {
        printf("%d\n", last_result);
    }
}