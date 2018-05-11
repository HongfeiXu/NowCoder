#pragma once

/*

������25���ϲ��������������

��Ŀ���ϲ����������������������ʹ�ý��������Ȼ������ġ�

�����׻��ֳ������ʵ�������ش�ĺܲ��Ҫ�ǵ�ʱ��˼·ȷʵ���ԡ�
�򵥵ķ������ǰ�����ϲ����̿���ÿ�δӵ�ǰ���µ����� lhs��rhs ���׽ڵ���ȡ��С�Ľڵ����ӵ��Ѿ��ϲ��������ĩβ��
����ĵݹ鷨�Լ�����������ʹ�����ַ�����
�ݹ鷨�У�ÿ�εݹ���û᷵��ʣ��ڵ��ͷ��㡣

*/

#include <list>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

#include "MyList.h"

using namespace std;

// ====================Approach_v1================
// �ݹ鷨��ʹ���Զ������ݽṹListNode
class SolutionNice {
public:
	// �����޸����� list �����ݣ�����Խ�����һ��list�еĽڵ��ƶ����뵽��һ��list�У�ʹ�ö���ռ临�Ӷ�ΪO(1)
	ListNode* merge(ListNode* lhs, ListNode* rhs)
	{
		if (lhs == nullptr)
			return rhs;
		if (rhs == nullptr)
			return lhs;

		// �Ƚϻ��ʣ��ڵ��ͷ���
		ListNode* merge_head = nullptr;
		if (lhs->val < rhs->val)
		{
			merge_head = lhs;
			merge_head->next = merge(lhs->next, rhs);
		}
		else
		{
			merge_head = rhs;
			merge_head->next = merge(lhs, rhs->next);
		}
		// ����ʣ��ڵ��ͷ��㣬��֮ǰ�Ѿ��ϲ��õ�����β�ڵ�����
		return merge_head;
	}
};

// ====================Approach_v2================
// ͨ����¼�ϲ�����������һ���ڵ㣬���ϵ�������β�˼��뵱ǰ lhs��rhs�Ľ�С�Ľڵ㣬ֱ������һ�������Ѿ�������ϡ�
// �ٽ����µ��Ǹ�����ֱ�����ӵ�����β��
class SolutionEasy {
public:
	ListNode* merge(ListNode* lhs, ListNode* rhs)
	{
		if (lhs == nullptr)
			return rhs;
		if (rhs == nullptr)
			return lhs;
		ListNode* head = nullptr;	// ��¼�ϲ�������ĵ�һ�����
		if (lhs->val < rhs->val)
		{
			head = lhs;
			lhs = lhs->next;
		}
		else
		{
			head = rhs;
			rhs = rhs->next;
		}
		ListNode* pre = head;		// ��¼��ǰ�ϲ�����������һ���ڵ�
		while (lhs != nullptr && rhs != nullptr)
		{
			if (lhs->val < rhs->val)
			{
				pre->next = lhs;	// ��ӵ�ǰ lhs �� rhs �н�С�Ľڵ㵽����ĩβ
				pre = lhs;			// Update pre
				lhs = lhs->next;	// Update lhs
			}
			else
			{
				pre->next = rhs;
				pre = rhs;
				rhs = rhs->next;
			}
		}
		if (lhs == nullptr)
			pre->next = rhs;
		else
			pre->next = lhs;
		return head;
	}
};

// ====================���Դ���================

ListNode* test(const std::string test_name, ListNode* p_head1, ListNode* p_head2)
{
	cout << test_name << " begins:\n";
	cout << "The first list = \n";
	printList(p_head1);
	cout << endl;
	cout << "The second list = \n";
	printList(p_head2);
	cout << endl;
	cout << "The merged list = \n";
	// uncomment to test
	//SolutionNice solu;
	SolutionEasy solu;
	ListNode* p_merged_head = solu.merge(p_head1, p_head2);
	printList(p_merged_head);
	cout << "\n\n";
	return p_merged_head;
}

// list1: 1->3->5
// list2: 2->4->6
void test1()
{
	list<int>l1 { 1,3,5 };
	list<int>l2 { 2,4,6 };
	ListNode* p_head1 = makeList(l1.begin(), l1.end());
	ListNode* p_head2 = makeList(l2.begin(), l2.end());
	ListNode* p_merged_head = test("test1", p_head1, p_head2);
	destroyList(p_merged_head);
}

// �����������ظ�����
// list1: 1->3->5
// list2: 1->3->5
void test2()
{
	list<int> l1 { 1,3,5 };
	list<int> l2 { 1,3,5 };
	ListNode* p_head1 = makeList(l1.begin(), l1.end());
	ListNode* p_head2 = makeList(l2.begin(), l2.end());
	ListNode* p_merged_head = test("test2", p_head1, p_head2);
	destroyList(p_merged_head);
}

// ��������ֻ��һ������
// list1: 1
// list2: 2
void test3()
{
	list<int> l1 { 1 };
	list<int> l2 { 2 };
	ListNode* p_head1 = makeList(l1.begin(), l1.end());
	ListNode* p_head2 = makeList(l2.begin(), l2.end());
	ListNode* p_merged_head = test("test3", p_head1, p_head2);
	destroyList(p_merged_head);
}

// ��������Ϊ��
// list1: ������
// list2: ������
void test4()
{
	list<int> l1 {  };
	list<int> l2 {  };
	ListNode* p_head1 = makeList(l1.begin(), l1.end());
	ListNode* p_head2 = makeList(l2.begin(), l2.end());
	ListNode* p_merged_head = test("test4", p_head1, p_head2);
	destroyList(p_merged_head);
}

void driver()
{
	test1();
	test2();
	test3();
	test4();
}
