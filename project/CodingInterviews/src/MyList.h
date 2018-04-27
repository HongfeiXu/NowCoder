#pragma once

/*

自定义类型 ListNode，用来构造单链表

*/

#include <list>

using namespace std;

struct ListNode {
	int value;
	ListNode* next;
};

// 使用 std::list 构建自定义的链表
ListNode* makeList(list<int>::const_iterator b, list<int>::const_iterator e);

// 输出自定义链表
void printList(ListNode* head);

// 释放单链表节点内存
void destroyList(ListNode* head);




