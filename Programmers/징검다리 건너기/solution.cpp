#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int BinarySearch(vector<int> &arr, int head, int tail, int k)
{
    if(head > tail) {
        return tail;
    }
    int mid = (head+tail)/2, count = 0, max_cnt = 0;
    for(int i=0; i<arr.size(); i++) {
        if(arr[i] < mid) {
            count++;
            max_cnt = max(max_cnt, count);
        } else {
            count = 0;
        }
    }
    return (max_cnt >= k) ? BinarySearch(arr, head, mid-1, k) : BinarySearch(arr, mid+1, tail, k);
}

int solution(vector<int> stones, int k) {
    int answer = 0, head = 1, tail = *max_element(stones.begin(), stones.end());
    answer = BinarySearch(stones, head, tail, k);
    return answer;
}