#pragma once

/*

面试题52：两个链表的第一个公共节点

题目：输入两个链表，找出它们的第一个公共节点。

*/

#include <iostream>
#include <algorithm>

using namespace std;

struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

int LengthOfList(ListNode* pHead)
{
	int ret = 0;
	while (pHead != nullptr)
	{
		++ret;
		pHead = pHead->m_pNext;
	}
	return ret;
}

// 在没有公共节点时，返回 nullptr
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	int len1 = LengthOfList(pHead1);
	int len2 = LengthOfList(pHead2);

	// 保证 pHead1 指向较长的链表
	if (len1 < len2)
	{
		swap(pHead1, pHead2);
		swap(len1, len2);
	}
	int gap = len1 - len2;
	for (int i = 0; i < gap; ++i)
		pHead1 = pHead1->m_pNext;
	// 当 pHead1 与 pHead2 指向公共节点或者 pHead2 已经到达链表尾端(说明两个链表没有公共节点)
	while (pHead1 != pHead2 && pHead2 != nullptr)
	{
		pHead1 = pHead1->m_pNext;
		pHead2 = pHead2->m_pNext;
	}
	// 返回 pHead2 而不是 pHead1，因为可能没有公共节点
	return pHead2;
}

// @selfboot
// 走你来时走过的路，那么我们会在交叉路口突然的相遇。好浪漫的解法！
ListNode* FindFirstCommonNode_v2(ListNode* pHead1, ListNode* pHead2)
{
	ListNode* p1 = pHead1;
	ListNode* p2 = pHead2;
	while (p1 != p2)
	{
		p1 = p1 == nullptr ? pHead2 : p1->m_pNext;
		p2 = p2 == nullptr ? pHead1 : p2->m_pNext;
	}
	return p1;
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

// 两个链表均不为空，且有公共节点
void test1()
{
	cout << "test1" << endl;
	ListNode* pA = new ListNode();
	ListNode* pB = new ListNode();
	ListNode* pC = new ListNode();
	ListNode* pD = new ListNode();
	ListNode* pE = new ListNode();
	ListNode* pF = new ListNode();
	pA->m_nValue = 1;
	pB->m_nValue = 2;
	pC->m_nValue = 3;
	pD->m_nValue = 4;
	pE->m_nValue = 5;
	pF->m_nValue = 6;
	// A->B->E->F
	pA->m_pNext = pB;
	pB->m_pNext = pE;
	// C->D->E->F
	pC->m_pNext = pD;
	pD->m_pNext = pE;

	pE->m_pNext = pF;
	pF->m_pNext = nullptr;
	ListNode* pCommon = FindFirstCommonNode(pA, pC);
	if (pCommon != nullptr)
		cout << pCommon->m_nValue << endl;
}

// 两个链表均不为空，但没有公共节点
void test2()
{
	cout << "test2" << endl;
	ListNode* pA = new ListNode();
	ListNode* pB = new ListNode();
	ListNode* pC = new ListNode();
	ListNode* pD = new ListNode();
	pA->m_nValue = 1;
	pB->m_nValue = 2;
	pC->m_nValue = 3;
	pD->m_nValue = 4;

	// A->B
	pA->m_pNext = pB;
	pB->m_pNext = nullptr;
	// C->D
	pC->m_pNext = pD;
	pD->m_pNext = nullptr;

	ListNode* pCommon = FindFirstCommonNode_v2(pA, pC);
	if (pCommon != nullptr)
		cout << pCommon->m_nValue << endl;
}

// 两个链表均为空
void test3()
{
	cout << "test3" << endl;
	ListNode* pA = nullptr;
	ListNode* pB = nullptr;
	ListNode* pCommon = FindFirstCommonNode(pA, pB);
	if (pCommon != nullptr)
		cout << pCommon->m_nValue << endl;
}


// 一个链表是另一个链表的子链表。。
void test4()
{
	cout << "test4" << endl;
	ListNode* pA = new ListNode();
	ListNode* pB = new ListNode();
	ListNode* pE = new ListNode();
	ListNode* pF = new ListNode();
	pA->m_nValue = 1;
	pB->m_nValue = 2;
	pE->m_nValue = 5;
	pF->m_nValue = 6;
	// A->B->E->F
	pA->m_pNext = pB;
	pB->m_pNext = pE;
	pE->m_pNext = pF;
	pF->m_pNext = nullptr;
	// B->E->F

	ListNode* pCommon = FindFirstCommonNode(pA, pB);
	if (pCommon != nullptr)
		cout << pCommon->m_nValue << endl;
}

// 其中一个链表为空
void test5()
{
	cout << "test5" << endl;
	ListNode* pA = new ListNode();
	ListNode* pB = new ListNode();
	ListNode* pE = new ListNode();
	ListNode* pF = new ListNode();
	pA->m_nValue = 1;
	pB->m_nValue = 2;
	pE->m_nValue = 5;
	pF->m_nValue = 6;
	// A->B->E->F
	pA->m_pNext = pB;
	pB->m_pNext = pE;
	pE->m_pNext = pF;
	pF->m_pNext = nullptr;

	ListNode* pCommon = FindFirstCommonNode(pA, nullptr);
	if (pCommon != nullptr)
		cout << pCommon->m_nValue << endl;
}

void driver()
{
	test1();
	test2();
	test3();
	test4();
	test5();
}