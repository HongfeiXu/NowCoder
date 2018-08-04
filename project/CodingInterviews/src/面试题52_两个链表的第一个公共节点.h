#pragma once

/*

������52����������ĵ�һ�������ڵ�

��Ŀ���������������ҳ����ǵĵ�һ�������ڵ㡣

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

// ��û�й����ڵ�ʱ������ nullptr
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	int len1 = LengthOfList(pHead1);
	int len2 = LengthOfList(pHead2);

	// ��֤ pHead1 ָ��ϳ�������
	if (len1 < len2)
	{
		swap(pHead1, pHead2);
		swap(len1, len2);
	}
	int gap = len1 - len2;
	for (int i = 0; i < gap; ++i)
		pHead1 = pHead1->m_pNext;
	// �� pHead1 �� pHead2 ָ�򹫹��ڵ���� pHead2 �Ѿ���������β��(˵����������û�й����ڵ�)
	while (pHead1 != pHead2 && pHead2 != nullptr)
	{
		pHead1 = pHead1->m_pNext;
		pHead2 = pHead2->m_pNext;
	}
	// ���� pHead2 ������ pHead1����Ϊ����û�й����ڵ�
	return pHead2;
}

// @selfboot
// ������ʱ�߹���·����ô���ǻ��ڽ���·��ͻȻ���������������Ľⷨ��
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

// �����������Ϊ�գ����й����ڵ�
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

// �����������Ϊ�գ���û�й����ڵ�
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

// ���������Ϊ��
void test3()
{
	cout << "test3" << endl;
	ListNode* pA = nullptr;
	ListNode* pB = nullptr;
	ListNode* pCommon = FindFirstCommonNode(pA, pB);
	if (pCommon != nullptr)
		cout << pCommon->m_nValue << endl;
}


// һ����������һ���������������
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

// ����һ������Ϊ��
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