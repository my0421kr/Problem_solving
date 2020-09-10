#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _Node
{
    int row, col;
} Node;

vector<Node> arr;

int Dist(int a, int b)
{
    return abs(arr[a].row - arr[b].row) + abs(arr[a].col - arr[b].col);
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    arr.resize(13);

    for(int i=1; i<=12; i++) {
        arr[i] = {(i-1)/3, (i - 1)%3};
    }
    arr[0] = {3, 1};

    int l = 10, r = 12;
    for(int i=0; i<numbers.size(); i++) {
        if(numbers[i] == 0 || (numbers[i] % 3 == 2)) {
            if(Dist(l, numbers[i]) < Dist(r, numbers[i])) {
                l = numbers[i];
                answer.push_back('L');
            } else if(Dist(l, numbers[i]) > Dist(r, numbers[i])) {
                r = numbers[i];
                answer.push_back('R');
            } else {
                if(hand[0] == 'l') {
                    l = numbers[i];
                    answer.push_back('L');
                } else {
                    r = numbers[i];
                    answer.push_back('R');
                }
            }
        } else if(numbers[i] % 3 == 1) {
            l = numbers[i];
            answer.push_back('L');
        } else {
            r = numbers[i];
            answer.push_back('R');
        }
    }

    return answer;
}