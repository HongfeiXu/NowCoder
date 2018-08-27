#pragma once

/*

面试题9：用两个队列实现一个栈

*/

#include <queue>
#include <iostream>
#include <stack>

using namespace std;

template<typename T> class CStack
{
public:
	CStack(void);
	~CStack(void);

	void pushback(const T& node);
	T popback();

private:
	queue<T> queue1;
	queue<T> queue2;
};

template<typename T> CStack<T>::CStack(void)
{

}

template<typename T> CStack<T>::~CStack(void)
{

}

template<typename T> void CStack<T>::pushback(const T& node)
{
	if (!queue1.empty())
		queue1.push(node);
	else
		queue2.push(node);
}

template<typename T> T CStack<T>::popback()
{
	if (!queue1.empty())
	{
		int n = queue1.size();
		for (int i = 0; i < n - 1; ++i)
		{
			queue2.push(queue1.front());
			queue1.pop();
		}
		int ret = queue1.front();
		queue1.pop();
		return ret;
	}
	else
	{
		int n = queue2.size();
		for (int i = 0; i < n - 1; ++i)
		{
			queue1.push(queue2.front());
			queue2.pop();
		}
		int ret = queue2.front();
		queue2.pop();
		return ret;
	}
}

void test()
{
	CStack<int> s;
	s.pushback(1);
	s.pushback(2);
	cout << s.popback() << endl;
	cout << s.popback() << endl;
	s.pushback(3);
	cout << s.popback() << endl;
}

void driver()
{
	test();
}