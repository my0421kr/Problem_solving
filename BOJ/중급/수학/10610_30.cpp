#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string str;

int main()
{
    cin >> str;

    sort(str.begin(), str.end());
    reverse(str.begin(), str.end());

    if(str.back() != '0') {
        printf("-1\n");
    } else {
        int temp = 0;
        for(int i=0; i<str.size(); i++) {
            temp += str[i] - '0';
        }
        if(temp%3 == 0) {
            cout << str;
        } else {
            printf("-1\n");
        }
    }
}