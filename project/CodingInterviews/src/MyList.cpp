/*

自定义类型 ListNode，用来构造单链表

*/

#include "MyList.h"

#include <iostream>

using namespace std;

ListNode* makeList(list<int>::const_iterator b, list<int>::const_iterator e)
{
	if (b == e)
		return nullptr;
	ListNode* curr = new ListNode;
	curr->value = *b;
	curr->next = makeList(++b, e);
	return curr;
}

void destroyList(ListNode* head)
{
	ListNode* p_node = head;
	while (p_node != nullptr)
	{
		head = head->next;
		delete p_node;
		p_node = head;
	}
}

void printList(ListNode* head)
{
	while (head != nullptr)
	{
		cout << head->value << " ";
		head = head->next;
	}
}

