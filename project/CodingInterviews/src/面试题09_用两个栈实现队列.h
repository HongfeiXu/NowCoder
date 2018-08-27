#pragma once

/*

������9��������ջʵ�ֶ���

��Ŀ��������ջʵ��һ�����С����е��������£���ʵ�������������� appendTail �� deleteHead���ֱ�����ڶ���β������ڵ���ڶ���ͷ��ɾ���ڵ�Ĺ��ܡ�

*/

#include <stack>
#include <iostream>

using namespace std;

template<typename T> class CQueue
{
public:
	CQueue(void);
	~CQueue(void);

	void appendTail(const T& node);
	T deleteHead();

private:
	stack<T> stack1;
	stack<T> stack2;
};

template<typename T> CQueue<T>::CQueue(void)
{

}

template<typename T> CQueue<T>::~CQueue(void)
{

}

template<typename T> void CQueue<T>::appendTail(const T& node)
{
	stack1.push(node);
}

template<typename T> T CQueue<T>::deleteHead()
{
	if (stack2.empty())
	{
		while (!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}
	}
	T ret = stack2.top();
	stack2.pop();
	return ret;
}

void test()
{
	CQueue<int> myqueue;
	myqueue.appendTail(1);
	myqueue.appendTail(3);
	cout << myqueue.deleteHead() << endl;
	myqueue.appendTail(4);
	myqueue.appendTail(5);
	cout << myqueue.deleteHead() << endl;
	cout << myqueue.deleteHead() << endl;
}

void driver()
{
	test();
}