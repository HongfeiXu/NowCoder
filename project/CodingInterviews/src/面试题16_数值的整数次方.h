#pragma once

/*

������ 16����ֵ�������η�

��Ŀ��ʵ�ֺ��� double Power(double base, int exponent)���� base �� exponent �η���
����ʹ�ÿ⺯����ͬʱ����Ҫ���Ǵ������⡣

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
�ù�ʽ���٣��ݹ�ʵ������Ĺ�ʽ

a^n = 
a^(n/2) * a^(n/2)       nΪż��
a^(n/2) * a^(n/2) * a   nΪ����

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
	// 0 �ĸ������ݷǷ���0����������
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

// ָ��Ϊ0
void test0()
{
	cout << Power(0, 0) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(-2, 0) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(3, 0) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
}

// ָ��Ϊ������
void test1()
{
	cout << Power(0, 3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(-1.4, 3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
	cout << Power(1.4, 3) << endl;
	cout << "invalid: " << boolalpha << g_InvalidInput << endl;
}

// ָ��Ϊ������
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