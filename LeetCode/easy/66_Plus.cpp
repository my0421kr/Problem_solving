class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        digits[digits.size()-1]++;
        for(int i=digits.size()-1; i>0; i--) {
            if(digits[i] == 10) {
                digits[i] = 0;
                digits[i-1]++;
            }
        }

        vector<int> answer;
        if(digits[0] == 10) {
            digits[0] = 0;
            answer.push_back(1);
        }
        answer.insert(answer.end(), digits.begin(), digits.end());
        return answer;
    }
};