class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) {
            return 0;
        }
        vector<int> arr(prices.size(), 0);
        arr[arr.size()-1] = prices[prices.size()-1];
        for(int i=prices.size()-2; i>=0; i--) {
            arr[i] = max(arr[i+1], prices[i]);
        }

        int answer = 0;
        for(int i=0; i<prices.size(); i++) {
            answer = max(answer, arr[i] - prices[i]);
        }
        return answer;
    }
};