#pragma once

// p13
// 求链表中的倒数第 k 个节点

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) { }
};

// 特殊情况
// 1. pListHead == nullptr, 
// 2. k == 0
// 3. 链表长度小于 k，
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	if (pListHead == nullptr)	// case 1
		return nullptr;
	if (k == 0)					// case 2
		return nullptr;
	ListNode* pAhead = pListHead;
	ListNode* pBehind = nullptr;
	for (unsigned int i = 0; i < k - 1; ++i)
	{
		if (pAhead != nullptr)
			pAhead = pAhead->next;
		else
			break;
	}
	if (pAhead == nullptr)		// case 3
		return nullptr;
	pBehind = pListHead;
	while (pAhead->next != nullptr)
	{
		pAhead = pAhead->next;
		pBehind = pBehind->next;
	}
	return pBehind;
};