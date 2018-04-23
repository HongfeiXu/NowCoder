#pragma once
/*

����ָ���ѭ����������

> Ref: https://blog.csdn.net/daniel_ustc/article/details/23096229


����Ĵ������н��Ϊ��

pb.use_count() = 0
pa.use_count() = 0
pb.use_count() = 2
pa.use_count() = 2
�밴���������. . .

ע���ʱsa,sb��û���ͷţ��������ڴ�й¶���⣡����
��A�ڲ���ָ��B��B�ڲ���ָ��A����������A��B�ض�����A������B������������B��A�ض�����B�����������A�������ѭ���������⣬Υ�����棬�����ڴ�й¶��

���������

1. ��ֻʣ�����һ�����õ�ʱ����Ҫ�ֶ�����ѭ�������ͷŶ���
2. ��A�������ڳ���B�������ڵ�ʱ��B��Ϊʹ��һ����ָͨ��ָ��A��
3. ʹ�������õ�����ָ���������ѭ�����á�

��Ȼ�����ַ��������У�������1�ͷ���2����Ҫ����Ա�ֶ����ƣ��鷳�����׳�������һ��ʹ�õ����ַ����������õ�����ָ��weak_ptr��

�޸ĺ����н��Ϊ

pb.use_count() = 0
pa.use_count() = 0
pb.use_count() = 1
pa.use_count() = 2
kill B
kill A
�밴���������. . .

*/

#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class B;

class A {
public:
	//shared_ptr<B> pb;
	weak_ptr<B> pb;
	void doSomething()
	{
		cout << "pb.use_count() = " << pb.use_count() << endl;
	}
	~A()
	{
		cout << "kill A\n";
	}
};

class B {
public:
	//shared_ptr<A> pa;
	weak_ptr<A> pa;
	void doSomething()
	{
		cout << "pa.use_count() = " << pa.use_count() << endl;
	}
	~B()
	{
		cout << "kill B\n";
	}
};


void driver()
{
	shared_ptr<A> sa(new A());
	sa->doSomething();
	shared_ptr<B> sb(new B());
	sb->doSomething();
	sa->pb = sb;
	sa->doSomething();
	sb->pa = sa;
	sb->doSomething();
}
