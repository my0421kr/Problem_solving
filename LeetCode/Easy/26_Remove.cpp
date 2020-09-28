#include <vector>
#include <algorithm>
using namespace std;

void Swap(int head, int i, vector<int> &nums)
{
    int temp = nums[head];
    nums[head] = nums[i];
    nums[i] = temp;
}

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int p = nums[0], answer = 1;
        int head = 1;

        for(int i=1; i<nums.size(); i++) {
            if(nums[i] != p) {
                p = nums[i];
                Swap(head, i, nums);
                head++;
                answer++;
            }
        }

        return answer;
    }
};