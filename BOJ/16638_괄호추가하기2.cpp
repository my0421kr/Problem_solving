#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, result = -2e9;
char arr[40];
vector<int> op;

int cal(int num1, int num2, char c)
{
    if(c == '+') return num1 + num2;
    else if(c == '-') return num1 - num2;
    else return num1 * num2;
}

int wholeCal(vector<int> &str)
{
    vector<int> temp;
    int len = (int)str.size();
    for(int i=0; i<len-1; i++) {
        if(i % 2 == 1 && str[i] == '*') {
            int temp2 = temp[(int)temp.size()-1];
            temp.pop_back();
            temp.push_back(temp2 * str[i+1]);
            i++;
        } else {
            temp.push_back(str[i]);
        }
    }
    int ret = temp[0];
    len = (int)temp.size();
    for(int i=1; i<len; i+=2) {
        ret = cal(ret, temp[i+1], temp[i]);
    }
    return ret;
}

void DFS(int index, vector<int> &str)
{
    if(index > n+2) {
        result = max(result, wholeCal(str));
        return;
    }

    str.push_back(arr[index-1]-'0');
    str.push_back(arr[index]);
    DFS(index+2, str);
    str.pop_back();
    str.pop_back();

    str.push_back(cal(arr[index-1]-'0', arr[index+1]-'0', arr[index]));
    str.push_back(arr[index+2]);
    DFS(index+4, str);
    str.pop_back();
    str.pop_back();
}

int main()
{
    scanf("%d", &n);
    scanf("%s", arr);
    arr[n] = '+';
    arr[n+1] = '0';

    DFS(1, op);
    printf("%d\n", result);
}