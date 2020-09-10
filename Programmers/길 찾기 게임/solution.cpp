#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _Node
{
    int num, x, y;
} Node;
typedef struct _Point
{
    int head, tail;
} Point;

vector<Node> arr;
vector<Point> mylist;
vector<vector<int>> tree;
vector<int> arr2, result1, result2;

bool cmp(Node a, Node b) 
{
    if(a.y > b.y) {
        return true;
    } else if(a.y == b.y) {
        return (a.x < b.x);
    }
    return false;
}

void f(int index, int level, int l, int r)
{
    int head = mylist[level].head;
    int tail = mylist[level].tail;
    if(level == mylist.size()) {
        return;
    }
    int right = lower_bound(arr2.begin()+head, arr2.begin()+tail, arr2[index]) - arr2.begin();
    int left = right-1;
    if(left >= head && l < arr2[left]) {
        tree[arr[index].num][0] = arr[left].num;
        f(left, level+1, l, arr2[index]);
    }
    if(right != tail && arr2[right] < r) {
        tree[arr[index].num][1] = arr[right].num;
        f(right, level+1, arr2[index], r);
    }
}

void Pre(int num)
{
    result1.push_back(num);
    for(int i=0; i<2; i++) {
        if(tree[num][i] != 0) {
            Pre(tree[num][i]);
        }
    }
}

void Post(int num)
{
    for(int i=0; i<2; i++) {
        if(tree[num][i] != 0) {
            Post(tree[num][i]);
        }
    }
    result2.push_back(num);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    tree.assign(nodeinfo.size()+1, vector<int>(2, 0));

    for(int i=0; i<nodeinfo.size(); i++) {
        arr.push_back({i+1, nodeinfo[i][0], nodeinfo[i][1]});
    }
    sort(arr.begin(), arr.end(), cmp);
    for(int i=0; i<arr.size(); i++) {
        arr2.push_back(arr[i].x);
    }

    int head = 0, tail = 1;
    while(head != arr.size()) {
        while(tail != arr.size() && arr[head].y == arr[tail].y) {
            tail++;
        }
        mylist.push_back({head, tail});
        head = tail;
    }

    f(0, 1, -1, 100001);

    Pre(arr[0].num);
    Post(arr[0].num);
    answer.push_back(result1);
    answer.push_back(result2);

    return answer;
}