string f(string str, int n)
{
    if(n == 1) {
        return str;
    } else {
        char p = str[0];
        int count = 0;
        string result = "";
        for(int i=0; i<str.size(); i++) {
            if(str[i] == p) {
                count++;
            } else {
                result.push_back((char)count + '0');
                result.push_back(p);
                p = str[i];
                count = 1;
            }
        }
        result.push_back((char)count + '0');
        result.push_back(p);
        return f(result, n-1);
    }
}

class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) {
            return "1";
        } else {
            string str = countAndSay(n-1);
            string result = "";
            char p = str[0];
            int count = 0;
            for(int i=0; i<str.size(); i++) {
                if(str[i] == p) {
                    count++;
                } else {
                    result.push_back((char)count + '0');
                    result.push_back(p);
                    p = str[i];
                    count = 1;
                }
            }
            result.push_back((char)count + '0');
            result.push_back(p);
            return result;
        }
    }
};