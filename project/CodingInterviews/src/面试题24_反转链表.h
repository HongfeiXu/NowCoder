#pragma once

#include <iostream>

using namespace std;

struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

ListNode* ReverseList(ListNode* pHead)
{
	if (pHead == nullptr)
		return nullptr;
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

	// 更新链表的头
	return pNewHead;
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

// 功能测试
void test1()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 2);
	AddToTail(pHead, 3);
	AddToTail(pHead, 4);
	PrintLinkedList(pHead);
	cout << endl;
	pHead = ReverseList(pHead);
	PrintLinkedList(pHead);
	cout << endl;
}

// 特殊输入测试：输入的链表头指针是 nullptr
void test2()
{
	ListNode* pHead = nullptr;
	PrintLinkedList(pHead);
	cout << endl;
	pHead = ReverseList(pHead);
	PrintLinkedList(pHead);
	cout << endl;
}

// 特殊输入测试：输入的链表只有一个节点
void test3()
{
	ListNode* pHead = nullptr;
	AddToTail(pHead, 2);
	PrintLinkedList(pHead);
	cout << endl;
	pHead = ReverseList(pHead);
	PrintLinkedList(pHead);
	cout << endl;
}


void driver()
{
	test1();
	test2();
	test3();
}