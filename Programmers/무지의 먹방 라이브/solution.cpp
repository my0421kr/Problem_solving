#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> mylist;

int solution(vector<int> food_times, long long k) {
    int answer = 0;

    for(int i=0; i<food_times.size(); i++) {
        mylist.push_back(food_times[i]);
    }
    sort(mylist.begin(), mylist.end());

    


    return answer;
}