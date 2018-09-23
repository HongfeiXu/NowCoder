#pragma once

/*

面试题 67：把字符串转换成整数

atoi

*/

#include <iostream>
#include <cctype>

using namespace std;

/*

仅支持 "123" 这种正整数对应的字符串
不支持 "-123"
不支持 "  123"
不支持 "123abc"
不支持 "abc"
不支持 nullptr
不支持数字溢出 "2147483648"

*/
int StrToInt_v0(char* s)
{
	int result = 0;
	while (*s != 0)
	{
		result = result * 10 + (*s - '0');
		++s;
	}
	return result;
}

// 用全局变量标记输入是否合法
enum Status{kValid = 0, kInvalid};
int g_nStatus = kValid;

/*

完善版本

*/
int StrToInt_v1(char* s)
{
	g_nStatus = kValid;

	// 1. 空指针检测
	if (s == nullptr)
	{
		g_nStatus = kInvalid;
		return 0;
	}

	// 2. 跳过前面的空格（包括制表符，换行符等）
	while (isspace(*s))
		++s;
	
	// 3. 获取符号
	bool isPositiveNum = true;
	if (*s == '+')
	{
		++s;
	}
	else if (*s == '-')
	{
		isPositiveNum = false;
		++s;
	}
	
	// 4. 符号后面的字符不是数字，输入非法
	if (*s < '0' || *s > '9')
	{
		g_nStatus = kInvalid;
		return 0;
	}

	// 5. 存储临时数字，进行溢出检测
	long long result = 0;
	bool hasAtLeastOneDigit = false;
	while (*s >= '0' && *s <= '9')
	{
		hasAtLeastOneDigit = true;
		result = result * 10 + (*s - '0');
		if (isPositiveNum && result > 0x7FFFFFFF
			|| !isPositiveNum && result < (signed int)0x80000000)
		{
			result = 0;
			g_nStatus = kInvalid;
			return 0;
		}
		++s;
	}

	// 6. 没有发现数字，则输入非法 （如："+abc" 或者 "-"）
	if (!hasAtLeastOneDigit)
		g_nStatus = kInvalid;

	// 7. 返回数字（确定正负以及转换数据类型）
	return isPositiveNum ? static_cast<int>(result) : -1 * static_cast<int>(result);
}

void test0()
{
	cout << StrToInt_v1(" -123junk") << endl;
	cout << "valid input: " << boolalpha << (g_nStatus == kValid) << endl;

	cout << atoi(" -123junk") << endl;
}

void test1()
{
	cout << StrToInt_v1("0") << endl;
	cout << "valid input: " << boolalpha << (g_nStatus == kValid) << endl;

	cout << atoi("0") << endl;
}

// no conversion can be performed
void test2()
{
	cout << StrToInt_v1("junk") << endl;
	cout << "valid input: " << boolalpha << (g_nStatus == kValid) << endl;

	cout << atoi("junk") << endl;
}

// UB: out of range of int
void test3()
{
	cout << StrToInt_v1("2147483648") << endl;
	cout << "valid input: " << boolalpha << (g_nStatus == kValid) << endl;

	cout << atoi("2147483648") << endl;
}

void test4()
{
	cout << StrToInt_v1("0101") << endl;
	cout << "valid input: " << boolalpha << (g_nStatus == kValid) << endl;

	cout << atoi("0101") << endl;
}

void driver()
{
	test0();
	test1();
	test2();
	test3();
	test4();
}