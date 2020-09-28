/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *p1 = head;
        if(p1 == NULL) {
            return false;
        }
        ListNode *p2 = head->next;
        if(p2 == NULL) {
            return false;
        }
        while(p1 != p2) {
            p1 = p1->next;
            if(p1 == NULL) {
                return false;
            } else if(p2->next == NULL) {
                return false;
            }
            p2 = p2->next->next;
            if(p2 == NULL) {
                return false;
            }
        }
        return true;
    }
};