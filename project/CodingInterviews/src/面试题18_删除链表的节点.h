#pragma once

/*

������18��ɾ������Ľڵ�

��Ŀһ����O(1)ʱ����ɾ������ڵ㡣
�������������ͷָ���һ���ڵ�ָ�룬����һ�������� O(1) ʱ����ɾ���ýڵ㡣
����ڵ��뺯���Ķ������£�

*/

#include <iostream>

using namespace std;

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

void DeleteNode(ListNode* &pListHead, ListNode* pToBeDeleted)
{
	if (pListHead == nullptr || pToBeDeleted == nullptr)
		return;

	// ��� pToBeDeleted �����һ���ڵ�
	if (pToBeDeleted->m_pNext == nullptr)
	{
		ListNode* pre = pListHead;
		if (pre == pToBeDeleted)
		{
			delete pToBeDeleted;
			pListHead = nullptr;
			return;
		}
		else
		{
			while (pre->m_pNext != nullptr && pre->m_pNext != pToBeDeleted)
				pre = pre->m_pNext;
			pre->m_pNext = nullptr;
			delete pToBeDeleted;
			pToBeDeleted = nullptr;
		}
	}
	// ��� pToBeDeleted �������һ���ڵ㣬��ֵ��һ���ڵ��ֵ�� pToBeDeleted �У�Ȼ��ɾ����һ���ڵ㣨������һ��覴ã��ڵ� pToBeDeleted ���ܲ��������У�
	else
	{
		ListNode* next = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = next->m_nValue;
		pToBeDeleted->m_pNext = next->m_pNext;
		delete next;
		next = nullptr;
	}
}

// ���ܲ��ԣ�ɾ��ͷ���
void test1()
{
	ListNode* pHead = nullptr;
	ListNode* pA = new ListNode();
	pA->m_nValue = 2;
	ListNode* pB = new ListNode();
	pB->m_nValue = 3;
	ListNode* pC = new ListNode();
	pC->m_nValue = 4;
	pA->m_pNext = pB;
	pB->m_pNext = pC;
	pHead = pA;
	PrintLinkedList(pHead);
	cout << endl;
	DeleteNode(pHead, pA);
	PrintLinkedList(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
}

// ���ܲ��ԣ�ɾ���м�ڵ�
void test2()
{
	ListNode* pHead = nullptr;
	ListNode* pA = new ListNode();
	pA->m_nValue = 2;
	ListNode* pB = new ListNode();
	pB->m_nValue = 3;
	ListNode* pC = new ListNode();
	pC->m_nValue = 4;
	pA->m_pNext = pB;
	pB->m_pNext = pC;
	pHead = pA;
	PrintLinkedList(pHead);
	cout << endl;
	DeleteNode(pHead, pB);
	PrintLinkedList(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
}

// ���ܲ��ԣ�ɾ��β�ڵ�
void test3()
{
	ListNode* pHead = nullptr;
	ListNode* pA = new ListNode();
	pA->m_nValue = 2;
	ListNode* pB = new ListNode();
	pB->m_nValue = 3;
	ListNode* pC = new ListNode();
	pC->m_nValue = 4;
	pA->m_pNext = pB;
	pB->m_pNext = pC;
	pHead = pA;
	PrintLinkedList(pHead);
	cout << endl;
	DeleteNode(pHead, pC);
	PrintLinkedList(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
}

// ����������ԣ�ָ������ͷ����Ϊ nullptr ָ��
void test4()
{
	ListNode* pHead = nullptr;
	ListNode* pA = new ListNode();
	pA->m_nValue = 2;
	PrintLinkedList(pHead);
	cout << endl;
	DeleteNode(pHead, pA);
	PrintLinkedList(pHead);
	cout << endl;
	DeleteLinkedList(pHead);
	delete pA;
}

// ����������ԣ�ָ��Ҫɾ���ڵ��Ϊ nullptr ָ��
void test5()
{
	ListNode* pHead = nullptr;
	ListNode* pA = new ListNode();
	pA->m_nValue = 2;
	pHead = pA;
	PrintLinkedList(pHead);
	cout << endl;
	DeleteNode(pHead, nullptr);
	PrintLinkedList(pHead);
	cout << endl;
}


void driver()
{
	test1();
	test2();
	test3();
	test4();
	test5();
}