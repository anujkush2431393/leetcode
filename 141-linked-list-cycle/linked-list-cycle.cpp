/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 //if pointer part contains 
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_map<ListNode*, bool> m;  // map to track visited nodes
        ListNode* temp = head;
        while (temp != NULL) {
            if (m[temp] == true) {
                return true;  // cycle detected
            }
            m[temp] = true;
            temp = temp->next;
        }
        return false;  // no cycle
    }
};