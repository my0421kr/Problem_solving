#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> answer(n, vector<int>(n));
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                answer[j][n-i-1] = matrix[i][j];
            }
        }
        matrix = answer;
    }
};