#pragma once

/*

������6����β��ͷ��ӡ����

��Ŀ������һ�������ͷ�ڵ㣬��β��ͷ��������ӡ��ÿ���ڵ��ֵ�����������¡�

*/

#include <iostream>

using namespace std;

struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

// 1. Ҫ�����޸�����Ľṹ
// ʹ��ջ�����ߵݹ�ķ�ʽ
void PrintLinkedListReversingly_Recursively(ListNode* pHead)
{
	if (pHead == nullptr)
		return;

	PrintLinkedListReversingly_Recursively(pHead->m_pNext);
	cout << pHead->m_nValue << " ";
}

// 2. �����޸�����ṹ
// ʹ������ָ����������һ��ָ���¼��δ����ת�Ľڵ��ͷ�ڵ㣬ǰ����ָ����з�ת����
void PrintLinkedListReversingly(ListNode* & pHead)
{
	if (pHead == nullptr)
		return;
	ListNode* pNewHead = nullptr;
	ListNode* pre = nullptr;
	ListNode* curr = pHead;
	ListNode* next = nullptr;
	while (curr != nullptr)
	{
		next = curr->m_pNext;
		if (next == nullptr)
			pNewHead = curr;
		curr->m_pNext = pre;
		pre = curr;
		curr = next;
	}
	pHead = pNewHead;
	while (pNewHead != nullptr)
	{
		cout << pNewHead->m_nValue << " ";
		pNewHead = pNewHead->m_pNext;
	}
}

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
	else if (pToBeDeleted == pHead)
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
	AddToTail(pHead, 5);
	AddToTail(pHead, 5);
	AddToTail(pHead, 5);

	PrintLinkedList(pHead);
	cout << endl;
	PrintLinkedListReversingly_Recursively(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
}

void test2()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 3);

	PrintLinkedList(pHead);
	cout << endl;
	PrintLinkedListReversingly_Recursively(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
}

void test3()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 3);
	AddToTail(pHead, 4);
	AddToTail(pHead, 5);
	AddToTail(pHead, 5);
	AddToTail(pHead, 5);

	PrintLinkedList(pHead);
	cout << endl;
	PrintLinkedListReversingly(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
}

void test4()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 3);

	PrintLinkedList(pHead);
	cout << endl;
	PrintLinkedListReversingly(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
}

void driver()
{
	test1();
	test2();
	test3();
	test4();
}