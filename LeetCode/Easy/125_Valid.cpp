class Solution {
public:
    bool isPalindrome(string s) {
        string str = "";
        for(int i=0; i<s.size(); i++) {
            if(('a' <= s[i] && s[i] <= 'z') || ('0' <= s[i] && s[i] <= '9')) {
                str.push_back(s[i]);
            } else if('A' <= s[i] && s[i] <= 'Z') {
                str.push_back(s[i] - 'A' + 'a');
            }
        }
        bool answer = true;
        int i = 0, j = str.size()-1;
        while(i <= j) {
            if(str[i] != str[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};