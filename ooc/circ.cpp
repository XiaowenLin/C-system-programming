#include <cstddef>

class Solution {
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
private:
    bool canReturn(ListNode *head) {
        if (head == NULL) return false;
        if (!canReturn(head)) return canReturn(head->next);
        ListNode *p;
        p = head->next;
        // return p is null or is head
        while (p != NULL && p != head) {
            p = p->next;
        }
        if (p == head) return true;
        else return false;
    }
public:
    bool hasCycle(ListNode *head) {
        bool inCircle = false;
        ListNode *p = head;
        // return p to the joint point or NULL
        while (!inCircle && p != NULL) {
            inCircle = canReturn(p);
            if (!inCircle) p = p->next;
        }
        if (p == NULL) return false;
        else true;
    }
};
