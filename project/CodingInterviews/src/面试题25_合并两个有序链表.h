#pragma once

/*

面试题25：合并两个排序的链表

题目：合并两个（递增）有序的链表，使得结果链表仍然是有序的。

网易雷火现场面试问到，结果回答的很差。主要是当时的思路确实不对。
简单的方法，是把这个合并过程看做每次从当前余下的链表 lhs，rhs 的首节点中取较小的节点链接到已经合并的链表的末尾。
下面的递归法以及迭代法就是使用这种方法。
递归法中，每次递归调用会返回剩余节点的头结点。

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
		// 返回剩余节点的头结点，与之前已经合并好的链表尾节点连接
		return merge_head;
	}
};

// ====================Approach_v2================
// 通过记录合并后链表的最后一个节点，不断的向链表尾端加入当前 lhs、rhs的较小的节点，直到其中一个链表已经遍历完毕。
// 再将余下的那个链表直接链接到链表尾部
class SolutionEasy {
public:
	ListNode* merge(ListNode* lhs, ListNode* rhs)
	{
		if (lhs == nullptr)
			return rhs;
		if (rhs == nullptr)
			return lhs;
		ListNode* head = nullptr;	// 记录合并后链表的第一个结点
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
		ListNode* pre = head;		// 记录当前合并后链表的最后一个节点
		while (lhs != nullptr && rhs != nullptr)
		{
			if (lhs->val < rhs->val)
			{
				pre->next = lhs;	// 添加当前 lhs 和 rhs 中较小的节点到链表末尾
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
	test1();
	test2();
	test3();
	test4();
}
