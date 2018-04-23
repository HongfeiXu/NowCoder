#pragma once

/*

P23
在 C++ 中，有哪4个与类型转换相关的关键字？
这些关键字各有什么特点，应该在什么场合下使用？

1. const_cast
添加或移除底层const，底层const表示指针所指的对象是一个常量（相对的顶层const表示指针本身是一个常量）详见 C++ Primier 第五版 P145，p57

2. static_cast
进行基本类型转换。任何具有明确定义的类型转换，只要不包含底层const，都可以使用static_cast。
另外，static_cast对编译器无法自动执行的类型转换也非常有用。详细见下面的例子。

3. dynamic_cast
进行有检查的多态转换，用于将基类的指针或引用安全地转换成派生类的指针或引用。

4. reinterpret_cast
以转译底层位模式在类型间转换。

*/

#include <iostream>
using namespace std;

// 1. const_cast
void cc_test()
{
	char c = 'A';
	const char* const_pc = &c;
	char* pc = const_cast<char*>(const_pc);			// 去掉 const 性质
	*pc = 'a';
	cout << c << endl;

	char d = 'A';
	char* pd = &d;
	const char* const_pd = const_cast<char*>(pd);	// 添加 const 性质
	cout << *const_pd << endl;
	*pd = 'B';
	cout << *const_pd << endl;
}

// 2. static_cast
void sc_test()
{
	int i = 3;
	int j = 2;
	double r = static_cast<double>(i) / static_cast<double>(j);
	cout << i / j << " " << r << endl;
	
	void *pr = &r;								// 任何非常量对象的地址都能存入 void*
	double *pd = static_cast<double*>(pr);		// 将 void* 转换回初始的指针类型
	cout << *pd << endl;
	//cout << *pr << endl;	// pr 必须是指向完整类型的指针
}

// TODO...

// 3. dynamic_cast

// 4. reinterpret_cast


