#pragma once

/*

剑指Offer p23

sizeof 一个空类型。
若空类型中定义了构造函数和析构函数。
若空类型中定义了虚析构函数。

*/

#include <iostream>

using namespace std;

class A {
};

class B {
	B() = default;
	~B() = default;
};

class C {
	virtual ~C() = default;
};


void driver()
{
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
}
