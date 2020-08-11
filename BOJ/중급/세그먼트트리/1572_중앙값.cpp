#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    int head, tail, cnt;
} Node;

int n, k, seglen = 65536*2;
vector<int> arr;
vector<Node> tree;

void InitSeg(int index, int head, int tail)
{
    tree[index] = {head, tail, 0};
    if(head != tail) {
        int mid = (head+tail)/2;
        InitSeg(index*2, head, mid);
        InitSeg(index*2+1, mid+1, tail);
    }
}

void Update(int index, int target, int flag)
{
    Node cur = tree[index];
    if(flag == 0) {
        tree[index].cnt++;
    } else {
        tree[index].cnt--;
    }
    if(cur.head != cur.tail) {
        int mid = (cur.head + cur.tail)/2;
        if(target <= mid) {
            Update(index*2, target, flag);
        } else {
            Update(index*2+1, target, flag);
        }
    }
}

long long Mid(int index, int cnt)
{
    Node cur = tree[index];
    if(cur.head == cur.tail) {
        return (long long)cur.head;
    } else {
        int leftcnt = tree[index*2].cnt;
        int rightcnt = tree[index*2+1].cnt;
        if(cnt <= leftcnt) {
            return Mid(index*2, cnt);
        } else {
            return Mid(index*2+1, cnt-leftcnt);
        }
    }
}

int main()
{
    scanf("%d %d", &n, &k);
    tree.resize(seglen*2);
    InitSeg(1, 0, seglen);
    arr.resize(n+1);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    long long answer = 0;
    for(int i=1; i<=n; i++) {
        Update(1, arr[i], 0);
        if(i >= k) {
            answer += Mid(1, (k+1)/2);
            Update(1, arr[i-k+1], 1);
        }
    }
    printf("%lld\n", answer);
}