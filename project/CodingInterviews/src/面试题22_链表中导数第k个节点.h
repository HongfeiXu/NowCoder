#pragma once

/*

������22�������е�����k���ڵ�
��Ŀ������һ����������������е�����k���ڵ㡣Ϊ�˷��ϴ��˵�˵�ϰ�ߣ������1��ʼ�������������β�ڵ��ǵ�����1���ڵ㡣

*/

#include <iostream>

using namespace std;

struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	if (pListHead == nullptr)
		return nullptr;

	ListNode* pLeft = pListHead;
	ListNode* pRight = pListHead;
	for (unsigned i = 0; i < k; ++i)
	{
		pRight = pRight->m_pNext;
		// �������� k ���ڵ�
		if (pRight == nullptr && i != k-1)
			return nullptr;
	}
	while (pRight != nullptr)
	{
		pLeft = pLeft->m_pNext;
		pRight = pRight->m_pNext;
	}
	return pLeft;
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

// ���ܲ���
void test1()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 2);
	AddToTail(pHead, 3);
	AddToTail(pHead, 4);

	ListNode* p = FindKthToTail(pHead, 3);
	if (p != nullptr)
		cout << p->m_nValue << endl;
	else
		cout << "not found" << endl;

	p = FindKthToTail(pHead, 2);
	if (p != nullptr)
		cout << p->m_nValue << endl;
	else
		cout << "not found" << endl;

	p = FindKthToTail(pHead, 1);
	if (p != nullptr)
		cout << p->m_nValue << endl;
	else
		cout << "not found" << endl;

	DeleteLinkedList(pHead);
}

// ����������ԣ�����ͷ���Ϊ nullptr ָ��
void test2()
{
	ListNode* pHead = nullptr;
	
	ListNode* p = FindKthToTail(pHead, 1);
	if (p != nullptr)
		cout << p->m_nValue << endl;
	else
		cout << "not found" << endl;
	
	DeleteLinkedList(pHead);
}


// ����������ԣ�����Ľڵ��������� k
void test3()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 2);
	AddToTail(pHead, 3);
	AddToTail(pHead, 4);

	ListNode* p = FindKthToTail(pHead, 20);
	if (p != nullptr)
		cout << p->m_nValue << endl;
	else
		cout << "not found" << endl;
	DeleteLinkedList(pHead);
}

// ����������ԣ�k ���� 0
void test4()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 2);
	AddToTail(pHead, 3);
	AddToTail(pHead, 4);

	ListNode* p = FindKthToTail(pHead, 0);
	if (p != nullptr)
		cout << p->m_nValue << endl;
	else
		cout << "not found" << endl;
	DeleteLinkedList(pHead);
}


void driver()
{
	test1();
	test2();
	test3();
	test4();
}