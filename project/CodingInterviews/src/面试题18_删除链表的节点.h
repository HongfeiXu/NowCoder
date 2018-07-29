#pragma once

/*

面试题18：删除链表的节点

题目一：在O(1)时间内删除链表节点。
给定单向链表的头指针和一个节点指针，定义一个函数在 O(1) 时间内删除该节点。
链表节点与函数的定义如下：

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

	// 如果 pToBeDeleted 是最后一个节点
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
	// 如果 pToBeDeleted 不是最后一个节点，赋值后一个节点的值到 pToBeDeleted 中，然后删除后一个节点（这里有一个瑕疵，节点 pToBeDeleted 可能不在链表中）
	else
	{
		ListNode* next = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = next->m_nValue;
		pToBeDeleted->m_pNext = next->m_pNext;
		delete next;
		next = nullptr;
	}
}

// 功能测试：删除头结点
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

// 功能测试：删除中间节点
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

// 功能测试：删除尾节点
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

// 特殊输入测试：指向链表头结点的为 nullptr 指针
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

// 特殊输入测试：指向要删除节点的为 nullptr 指针
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