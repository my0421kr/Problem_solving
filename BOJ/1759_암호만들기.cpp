#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int l, c;
vector<char> arr;
vector<char> result;

bool IsVowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ? true : false;
}

void DFS(int index, int vowelCount, int count)
{
    if(index == c) {
        return;
    }
    if(count == l) {
        if(vowelCount >= 1 && count - vowelCount >= 2) {
            for(int i=0; i<l; i++) {
                printf("%c", result[i]);
            }
            printf("\n");
        }
        return;
    }
    for(int i=index+1; i<c; i++) {
        result.push_back(arr[i]);
        if(IsVowel(arr[i])) {
            DFS(i, vowelCount+1, count+1);
        } else {
            DFS(i, vowelCount, count+1);
        }
        result.pop_back();
    }
}

int main()
{
    scanf("%d %d", &l, &c);

    arr.resize(c);
    for(int i=0; i<c; i++) {
        getchar();
        arr[i] = getchar();
    }
    sort(arr.begin(), arr.end());

    for(int i=0; i<c; i++) {
        result.push_back(arr[i]);
        if(IsVowel(arr[i])) {
            DFS(i, 1, 1);
        } else {
            DFS(i, 0, 1);
        }
        result.pop_back();
    }
}