vector<vector<bool>> arr;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size(), i, j, k;
        arr.assign(n, vector<bool>(n, true));
        for(k=1; k<n; k++) {
            i = 0;
            j = k;
            while(j < n) {
                arr[i++][j++] = (s[i] == s[j]) ? arr[i+1][j-1] : false;
            }
        }
        int result = 0, head = 0;
        for(int i=0; i<n; i++) {
            for(int j=i; j<n; j++) {
                if(arr[i][j] && j-i+1 > result) {
                    result = j-i+1;
                    head = i;
                }
            }
        }
        return s.substr(head, result);
    }
};