//
// Created by 22411 on 2025/10/31.
//
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode *head = new ListNode((l1->val + l2->val) % 10);
        ListNode *cur = head;
        int carry = (l1->val + l2->val) / 10;
        int num1, num2, sum;
        l1 = l1->next;
        l2 = l2->next;
        while(l1 || l2 || carry)
        {
            if (l1)
            {
                num1 = l1->val;
                l1 = l1->next;
            }
            else num1 = 0;
            if (l2)
            {
                num2 = l2->val;
                l2 = l2->next;
            }
            else num2 = 0;
            sum = num1 + num2 + carry;
            carry = sum / 10;
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
        }
        return head;
    }
};