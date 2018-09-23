#pragma once

/*

面试题 16：数值的整数次方

题目：实现函数 double Power(double base, int exponent)，求 base 的 exponent 次方。
不得使用库函数，同时不需要考虑大数问题。

*/

#include <iostream>
#include <cmath>

using namespace std;

bool g_InvalidInput = false;

bool EqualDouble(double a, double b)
{
	return abs(a - b) < 1e-7;
}

double PowerWithUnsignedExponent(double base, unsigned exponent)
{
	double result = 1.0;
	for (unsigned i = 0; i < exponent; ++i)
		result *= base;
	return result;
}

/*
用公式加速，递归实现下面的公式

a^n = 
a^(n/2) * a^(n/2)       n为偶数
a^(n/2) * a^(n/2) * a   n为奇数

*/
double PowerWithUnsignedExponent_v2(double base, unsigned exponent)
{
	if (exponent == 0)
		return 1;
	if (exponent == 1)
		return base;

	double result = PowerWithUnsignedExponent_v2(base, exponent >> 1);
	result *= result;
	if (exponent & 0x1 == 1)
		result *= base;
	return result;
}

double Power(double base, int exponent)
{
	g_InvalidInput = false;
	// 0 的负数次幂非法，0次幂无意义
	if (EqualDouble(base, 0.0) && exponent <= 0)
	{
		g_InvalidInput = true;
		return 0.0;
	}

	double result = PowerWithUnsignedExponent_v2(base, static_cast<unsigned int>(abs(exponent)));
	if (exponent < 0)
		result = 1 / result;

	return result;
}

// 指数为0
void test0()
{
	cout << Power(0, 0) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(-2, 0) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(3, 0) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
}

// 指数为正整数
void test1()
{
	cout << Power(0, 3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(-1.4, 3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(1.4, 3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
}

// 指数为负整数
void test2()
{
	cout << Power(0, -3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(-1.5, -3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(1.5, -3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
}

void driver()
{
	test0();
	test1();
	test2();
}