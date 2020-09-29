#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size(), cur_index = 0;
        vector<vector<string>> answer(0, vector<string>(0));
        map<string, bool> visit;
        map<string, int> index;
        for(int i=0; i<n; i++) {
            string str = strs[i];
            sort(strs[i].begin(), strs[i].end());
            if(visit[strs[i]]) {
                int target = index[strs[i]];
                answer[target].push_back(str);
            } else {
                visit[strs[i]] = true;
                index[strs[i]] = cur_index;
                answer.push_back(vector<string>(0));
                answer[cur_index].push_back(str);
                cur_index++;
            }
        }
        return answer;
    }
};