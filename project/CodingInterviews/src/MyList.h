#pragma once

/*

�Զ������� ListNode���������쵥����

*/

#include <list>

using namespace std;

struct ListNode {
	int value;
	ListNode* next;
};

// ʹ�� std::list �����Զ��������
ListNode* makeList(list<int>::const_iterator b, list<int>::const_iterator e);

// ����Զ�������
void printList(ListNode* head);

// �ͷŵ�����ڵ��ڴ�
void destroyList(ListNode* head);




