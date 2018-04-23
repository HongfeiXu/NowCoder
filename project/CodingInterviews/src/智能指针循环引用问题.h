#pragma once
/*

智能指针的循环引用问题

> Ref: https://blog.csdn.net/daniel_ustc/article/details/23096229


上面的代码运行结果为：

pb.use_count() = 0
pa.use_count() = 0
pb.use_count() = 2
pa.use_count() = 2
请按任意键继续. . .

注意此时sa,sb都没有释放，产生了内存泄露问题！！！
即A内部有指向B，B内部有指向A，这样对于A，B必定是在A析构后B才析构，对于B，A必定是在B析构后才析构A，这就是循环引用问题，违反常规，导致内存泄露。

解决方法：

1. 当只剩下最后一个引用的时候需要手动打破循环引用释放对象。
2. 当A的生存期超过B的生存期的时候，B改为使用一个普通指针指向A。
3. 使用弱引用的智能指针打破这种循环引用。

虽然这三种方法都可行，但方法1和方法2都需要程序员手动控制，麻烦且容易出错。我们一般使用第三种方法：弱引用的智能指针weak_ptr。

修改后，运行结果为

pb.use_count() = 0
pa.use_count() = 0
pb.use_count() = 1
pa.use_count() = 2
kill B
kill A
请按任意键继续. . .

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
