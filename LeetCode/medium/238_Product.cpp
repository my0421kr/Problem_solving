#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size(), temp = 1;
        vector<int> answer(n, 1);

        for(int i=1; i<n; i++) {
            answer[i] = answer[i-1] * nums[i-1];
        }
        for(int i=n-2; i>=0; i--) {
            temp *= nums[i+1];
            answer[i] *= temp;
        }
        return answer;
    }
};