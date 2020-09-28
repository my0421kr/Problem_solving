class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int answer = -__INT32_MAX__-1;
        int i = 0, j = 0, cur = nums[0];
        while(1) {
            answer = max(answer, cur);
            if(cur < 0) {
                i = j+1;
                j = i;
                if(i == nums.size()) {
                    break;
                }
                cur = nums[i];
            } else {
                j++;
                if(j == nums.size()) {
                    break;
                }
                cur += nums[j];
            }
        }
        return answer;
    }
};