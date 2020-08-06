#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    int row, col;
} Node;

int n, m, answer = 2e9;
vector<Node> chickCan, chick, house;

int Length(Node a, Node b)
{
    return abs(a.row - b.row) + abs(a.col - b.col);
}

int LengthSum()
{
    int len = house.size();
    int result = 0;
    for(int i=0; i<len; i++) {
        int temp = 2e9;
        for(int j=0; j<m; j++) {
            temp = min(temp, Length(house[i], chick[j]));
        }
        result += temp;
    }
    return result;
}

void DFS(int index, int count)
{
    if(count == m) {
        answer = min(answer, LengthSum());
        return;
    } else {
        int len = chickCan.size();
        for(int i=index+1; i<len; i++) {
            chick.push_back(chickCan[i]);
            DFS(i, count+1);
            chick.pop_back();
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);

    int temp;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            scanf("%d", &temp);
            if(temp == 1) {
                house.push_back({i, j});
            } else if(temp == 2) {
                chickCan.push_back({i, j});
            }
        }
    }

    int len = chickCan.size();
    for(int i=0; i<len; i++) {
        chick.push_back(chickCan[i]);
        DFS(i, 1);
        chick.pop_back();
    }
    printf("%d\n", answer);
}