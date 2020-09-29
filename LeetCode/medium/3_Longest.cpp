class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> index(256, -1);
        int answer = 0;
        int i = 0, j = -1;
        while(j < (int)s.size() - 1) {
            j++;
            if(index[s[j]] == -1) {
                index[s[j]] = j;
            } else {
                while(i <= index[s[j]]) {
                    index[s[i]] = -1;
                    i++;
                }
                index[s[j]] = j;
            }
            printf("%d %d\n", i, j);
            answer = max(answer, j-i+1);
        }
        return answer;
    }
};