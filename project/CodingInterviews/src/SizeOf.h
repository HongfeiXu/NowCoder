#pragma once

/*

��ָOffer p23

sizeof һ�������͡�
���������ж����˹��캯��������������
���������ж�����������������

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
