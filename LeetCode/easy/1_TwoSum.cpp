#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> answer;
        map<int, int> pm;

        int temp;
        for(int i=0; i<nums.size(); i++) {
            temp = pm[target - nums[i]];
            if(temp != 0) {
                answer.push_back(temp-1);
                answer.push_back(i);
                break;
            } else {
                pm[nums[i]] = i+1;
            }
        }

        return answer;
    }
};