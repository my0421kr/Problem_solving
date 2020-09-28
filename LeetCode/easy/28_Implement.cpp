
bool IsValid(int head, string &str1, string &str2)
{
    for(int i=0; i<str2.size(); i++) {
        if(str1[i+head] != str2[i]) {
            return false;
        }
    }
    return true;
}

class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size() == 0) {
            return 0;
        }
        for(int i=0; i<=((int)haystack.size() - (int)needle.size()); i++) {
            if(IsValid(i, haystack, needle)) {
                return i;
            }
        }
        return -1;
    }
};