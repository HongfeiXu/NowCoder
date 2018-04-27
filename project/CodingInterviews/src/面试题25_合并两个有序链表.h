#pragma once

/*

������25���ϲ��������������

��Ŀ���ϲ����������������������ʹ�ý��������Ȼ������ġ�

�����׻��ֳ������ʵ�������ش�ĺܲ
�ص��ǵ����ֵݹ鷽���͵����ֵ�������

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
// ������������ռ�O(n)
class SolutionIterative {
public:
	list<int> merge(const list<int>& lhs, const list<int>& rhs)
	{
		list<int> result;
		auto lhs_it = lhs.begin();
		auto rhs_it = rhs.begin();

		while (lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if (*lhs_it < *rhs_it)
			{
				result.push_back(*lhs_it);
				++lhs_it;
			}
			else
			{
				result.push_back(*rhs_it);
				++rhs_it;
			}
		}
		copy(lhs_it, lhs.end(), back_inserter(result));
		copy(rhs_it, rhs.end(), back_inserter(result));
		return result;
	}
};

// ====================Approach_v2================
// �ݹ鷨��ʹ�õ�����������ռ�O(n)
class SolutionRecursive {
public:
	using IterType = list<int>::const_iterator;

	list<int> merge(const list<int>& lhs, const list<int>& rhs)
	{
		list<int> result;
		combineAux(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result);
		return result;
	}
	void combineAux(IterType lhs_b, IterType lhs_e, IterType rhs_b, IterType rhs_e, list<int>& result)
	{
		if (lhs_b == lhs_e)
		{
			copy(rhs_b, rhs_e, back_inserter(result));
			return;
		}
		if (rhs_b == rhs_e)
		{
			copy(lhs_b, lhs_e, back_inserter(result));
			return;
		}
		if (*lhs_b < *rhs_b)
		{
			result.push_back(*lhs_b);
			++lhs_b;
		}
		else
		{
			result.push_back(*rhs_b);
			++rhs_b;
		}
		combineAux(lhs_b, lhs_e, rhs_b, rhs_e, result);
		return;
	}
};

// ====================Approach_v3================
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
		if (lhs->value < rhs->value)
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

// ====================Approach_v4================
// ��������ʹ���Զ������ݽṹListNode������ռ临�Ӷ�O(1)
class SolutionBest {
public:
	ListNode* merge(ListNode* lhs, ListNode* rhs)
	{
		if (lhs == nullptr)
			return rhs;
		if (rhs == nullptr)
			return lhs;
		if (lhs->value > rhs->value)
			swap(lhs, rhs);
		ListNode* pre = nullptr;
		ListNode* curr = lhs;
		ListNode* r_node = rhs;
		while (r_node != nullptr)
		{
			// Ѱ�� r_node Ҫ���뵽 lhs �е�λ�ã���lhs����Ѱ��һ����r_node��Ľڵ�curr��
			while (curr != nullptr && r_node->value >= curr->value)
			{
				pre = curr;
				curr = curr->next;
			}

			// ����ǰ�ڵ�r_node��������lhs�����µĽڵ㣬��ֱ�ӽ�rhs�ӵ�lhs��β��
			if (curr == nullptr)
			{
				pre->next = r_node;
				break;
			}

			// ����ǰ�ڵ�r_node����pre���棬����preָ��
			pre->next = r_node;
			r_node = r_node->next;
			pre->next->next = curr;
			pre = pre->next;
		}
		return lhs;
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
	SolutionBest solu;
	ListNode* p_merged_head = solu.merge(p_head1, p_head2);
	printList(p_merged_head);
	cout << "\n\n";
	return p_merged_head;
}

// list1: 1->3->5
// list2: 2->4->6
void test1()
{
	list<int> l1 { 1,3,5 };
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
	cout << "=============================" << endl;
	cout << "Using std::list" << endl;
	list<int> lhs = { 1,3,7,9 };
	list<int> rhs = { 2,3,3,5,12 };
	list<int> result;

	SolutionIterative solu1;
	result = solu1.merge(lhs, rhs);
	for (auto item : result)
		cout << item << " ";
	cout << endl;

	SolutionRecursive solu2;
	result = solu2.merge(lhs, rhs);
	for (auto item : result)
		cout << item << " ";
	cout << endl;

	cout << "=============================" << endl;
	cout << "Using user defined list" << endl;
	test1();
	test2();
	test3();
	test4();
}
