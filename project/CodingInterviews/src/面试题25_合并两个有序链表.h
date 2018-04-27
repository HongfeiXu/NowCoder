#pragma once

/*

面试题25：合并两个排序的链表

题目：合并两个（递增）有序的链表，使得结果链表仍然是有序的。

网易雷火现场面试问到，结果回答的很差。
重点是第三种递归方法和第四种迭代方法

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
// 迭代法，额外空间O(n)
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
// 递归法，使用迭代器，额外空间O(n)
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
// 递归法，使用自定义数据结构ListNode
class SolutionNice {
public:
	// 允许修改输入 list 的内容，则可以将其中一个list中的节点移动插入到另一个list中，使得额外空间复杂度为O(1)
	ListNode* merge(ListNode* lhs, ListNode* rhs)
	{
		if (lhs == nullptr)
			return rhs;
		if (rhs == nullptr)
			return lhs;

		// 比较获得剩余节点的头结点
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
		// 返回剩余节点的头结点，与之前已经合并好的链表尾节点连接
		return merge_head;
	}
};

// ====================Approach_v4================
// 迭代法，使用自定义数据结构ListNode，额外空间复杂度O(1)
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
			// 寻找 r_node 要插入到 lhs 中的位置（在lhs中找寻第一个比r_node大的节点curr）
			while (curr != nullptr && r_node->value >= curr->value)
			{
				pre = curr;
				curr = curr->next;
			}

			// 若当前节点r_node大于所有lhs中余下的节点，则直接将rhs接到lhs的尾部
			if (curr == nullptr)
			{
				pre->next = r_node;
				break;
			}

			// 将当前节点r_node插入pre后面，更新pre指针
			pre->next = r_node;
			r_node = r_node->next;
			pre->next->next = curr;
			pre = pre->next;
		}
		return lhs;
	}
};



// ====================测试代码================

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

// 两个链表有重复数字
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

// 两个链表都只有一个数字
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

// 两个链表都为空
// list1: 空链表
// list2: 空链表
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
