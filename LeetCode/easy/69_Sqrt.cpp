
long long f(long long head, long long tail, long long x)
{
    long long mid = (head+tail)/2;
    if(mid*mid <= x && x < (mid+1)*(mid+1)) {
        return mid;
    } else if(x < mid*mid){
        return f(head, mid, x);
    } else {
        return f(mid+1, tail, x);
    }
}

class Solution {
public:
    int mySqrt(int x) {
        return f(0, x, x);
    }
};