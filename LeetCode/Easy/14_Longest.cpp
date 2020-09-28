#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string MergeSearch(int head, int tail, vector<string> &strs)
{
    if(head == tail) {
        return strs[head];
    } else {
        int mid = (head+tail)/2, i;
        string str1 = MergeSearch(head, mid, strs);
        string str2 = MergeSearch(mid+1, tail, strs);
        for(i=0; i<min(str1.size(), str2.size()); i++) {
            if(str1[i] != str2[i]) {
                break;
            }
        }
        return str1.substr(0, i);
    }
}

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0) {
            return "";
        }
        string answer = MergeSearch(0, strs.size()-1, strs);
        return answer;
    }
};