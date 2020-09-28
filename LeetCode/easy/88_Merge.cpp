class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n == 0) {
            return;
        }
        if(m == 0) {
            nums1 = nums2;
            return;
        }
        for(int i=m-1; i>=0; i--) {
            nums1[i+n] = nums1[i];
        }
        int i = n, j = 0, k = 0;
        while(i != nums1.size() && j != nums2.size()) {
            if(nums1[i] < nums2[j]) {
                nums1[k++] = nums1[i++];
            } else {
                nums1[k++] = nums2[j++];
            }
        }
        while(i != nums1.size()) {
            nums1[k++] = nums1[i++];
        }
        while(j != nums2.size()) {
            nums1[k++] = nums2[j++];
        }
    }
};