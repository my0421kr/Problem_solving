#include <iostream>
#include <string>
#include <vector>

using namespace std;

int IsSet(int head, int tail);

int n;
string str;
vector<vector<int>> cset, celelist, clist, cele, catom;

int IsAtom(int head, int tail)
{
    if(catom[head][tail] == -1) {
        int result;
        if(head == tail) {
            if(str[head] == '{' || str[head] == '}' || str[head] == ',') {
                result = 1;
            } else {
                result = 0;
            }
        } else {
            result = 0;
        }
        catom[head][tail] = result;
    }
    return catom[head][tail];
}

int IsEle(int head, int tail)
{
    if(cele[head][tail] == -1) {
        int result;
        if(IsAtom(head, tail) || IsSet(head, tail)) {
            result = 1;
        } else {
            result = 0;
        }
        cele[head][tail] = result;
    }
    return cele[head][tail];
}

int IsList(int head, int tail)
{
    if(clist[head][tail] == -1) {
        int result;
        if(IsEle(head, tail)) {
            result = 1;
        } else {
            for(int i=head; i<=tail; i++) {
                if(str[i] == ',') {
                    if(IsEle(head, i-1) && IsList(i+1, tail)) {
                        return clist[head][tail] = 1;
                    }
                }
            }
            return clist[head][tail] = 0;
        }
    }
    return clist[head][tail];
}

int IsEleList(int head, int tail)
{
    if(celelist[head][tail] == -1) {
        int result;
        if(head > tail) {
            result = 1;
        } else if(IsList(head, tail)) {
            result = 1;
        } else {
            result = 0;
        }
        celelist[head][tail] = result;
    }
    return celelist[head][tail];
}

int IsSet(int head, int tail)
{
    if(cset[head][tail] == -1) {
        int result;
        if(tail - head >= 1) {
            if(str[head] == '{' && str[tail] == '}' && IsEleList(head+1, tail-1)) {
                result = 1;
            } else {
                result = 0;
            }
        } else {
            result = 0;
        }
        cset[head][tail] = result;
    }
    return cset[head][tail];
}

void Init()
{
    cset.assign(str.size(), vector<int>(str.size(), -1));
    celelist.assign(str.size(), vector<int>(str.size(), -1));
    clist.assign(str.size(), vector<int>(str.size(), -1));
    cele.assign(str.size(), vector<int>(str.size(), -1));
    catom.assign(str.size(), vector<int>(str.size(), -1));
}

int main()
{
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        cin >> str;
        Init();
        if(IsSet(0, str.size()-1)) {
            printf("Word #%d: Set\n", i);
        } else {
            printf("Word #%d: No Set\n", i);
        }
    }
}