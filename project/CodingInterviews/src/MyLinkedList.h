// P56 Á´±í

#pragma once

#include <iostream>

using namespace std;

namespace my_linked_list 
{
	struct ListNode {
		int m_nValue;
		ListNode* m_pNext;
	};

	void AddToTail(ListNode* & pHead, int value)
	{
		ListNode* pNew = new ListNode();
		pNew->m_nValue = value;
		pNew->m_pNext = nullptr;

		if (pHead == nullptr)
		{
			pHead = pNew;
		}
		else
		{
			ListNode* pNode = pHead;
			while (pNode->m_pNext != nullptr)
			{
				pNode = pNode->m_pNext;
			}
			pNode->m_pNext = pNew;
		}
	}

	void RemoveNode(ListNode* & pHead, int value)
	{
		if (pHead == nullptr)
			return;

		ListNode* pToBeDeleted = pHead;
		ListNode* pre = pHead;
		while (pToBeDeleted != nullptr && pToBeDeleted->m_nValue != value)
		{
			pre = pToBeDeleted;
			pToBeDeleted = pToBeDeleted->m_pNext;
		}
		if (pToBeDeleted == nullptr)
		{
			return;
		}
		else if(pToBeDeleted == pHead)
		{
			pHead = pHead->m_pNext;
			delete pToBeDeleted;
		}
		else
		{
			pre->m_pNext = pToBeDeleted->m_pNext;
			delete pToBeDeleted;
		}
	}

	void DeleteLinkedList(ListNode* & pHead)
	{
		ListNode* pCurr = nullptr;
		while (pHead != nullptr)
		{
			pCurr = pHead;
			pHead = pHead->m_pNext;
			delete pCurr;
		}
	}

	void PrintLinkedList(ListNode* pHead)
	{
		while (pHead != nullptr)
		{
			cout << pHead->m_nValue << " ";
			pHead = pHead->m_pNext;
		}
	}

	void test1()
	{
		ListNode* pHead = nullptr;
		AddToTail(pHead, 3);
		AddToTail(pHead, 4);
		PrintLinkedList(pHead);
		DeleteLinkedList(pHead);
	}

	void test2()
	{
		ListNode* pHead = nullptr;
		AddToTail(pHead, 3);
		AddToTail(pHead, 4);
		AddToTail(pHead, 5);
		AddToTail(pHead, 4);
		PrintLinkedList(pHead);
		RemoveNode(pHead, 4);
		PrintLinkedList(pHead);
		DeleteLinkedList(pHead);
	}

	void driver()
	{
		test1();
		test2();
	}
}


