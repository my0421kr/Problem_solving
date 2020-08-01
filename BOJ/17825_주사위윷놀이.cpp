#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int cost;
    vector<int> next;
} Node;
typedef struct _Horse
{
    int pos, score;
} Horse;

int answer = 0;
int dice[10];
Horse state[4] = {{0,0}, {0,0}, {0,0}, {0,0}};
vector<Node> arr;

bool IsAlreadyHorse(int pos)
{
    for(int i=0; i<4; i++) {
        if(state[i].pos == pos && state[i].pos != 21) {
            return true;
        }
    }
    return false;
}

bool IsBlue(int pos)
{
    return (pos == 5 || pos == 10 || pos == 15) ? true : false;
}

bool IsEnd(int which)
{
    return (state[which].pos == 21) ? true : false;
}

void Make_Board()
{
    arr.resize(33);
    for(int i=0; i<21; i++) {
        arr[i].cost = i*2;
        arr[i].next.push_back(i+1);
    }

    arr[5].next.push_back(22);
    arr[10].next.push_back(28);
    arr[15].next.push_back(25);
    arr[22] = {13, {23}}; arr[23] = {16, {24}}, arr[24] = {19, {30}};
    arr[25] = {28, {26}}; arr[26] = {27, {27}}, arr[27] = {26, {30}};
    arr[28] = {22, {29}}; arr[29] = {24, {30}}, arr[30] = {25, {31}}; arr[31] = {30, {32}}; arr[32] = {35, {20}};
}

int WholeScore()
{
    int result = 0;
    for(int i=0; i<4; i++) {
        result += state[i].score;
    }
    return result;
}

int Destination(int which, int count)
{
    int cur = state[which].pos;
    if(IsBlue(cur)) {
        cur = arr[cur].next[1];
    } else {
        cur = arr[cur].next[0];
    }

    count--;
    while(count != 0 && cur != 21) {
        count--;
        cur = arr[cur].next[0];
    }

    return cur;
}

void DFS(int which, int count)
{
    if(count == 10) {
        answer = max(answer, WholeScore());
        return;
    }

    if(IsEnd(which)) {
        return;
    }

    int src = state[which].pos;
    int dest = Destination(which, dice[count]);
    if(IsAlreadyHorse(dest)) {
        return;
    }

    state[which] = {dest, state[which].score + arr[dest].cost};
    for(int i=0; i<4; i++) {
        DFS(i, count+1);
    }
    state[which] = {src, state[which].score - arr[dest].cost};
}

int main()
{
    Make_Board();

    for(int i=0; i<10; i++) {
        scanf("%d", &dice[i]);
    }

    for(int i=0; i<4; i++) {
        DFS(i, 0);
    }
    printf("%d\n", answer);
}