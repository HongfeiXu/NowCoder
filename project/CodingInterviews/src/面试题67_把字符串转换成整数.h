#pragma once

/*

������ 67�����ַ���ת��������

atoi

*/

#include <iostream>
#include <cctype>

using namespace std;

/*

��֧�� "123" ������������Ӧ���ַ���
��֧�� "-123"
��֧�� "  123"
��֧�� "123abc"
��֧�� "abc"
��֧�� nullptr
��֧��������� "2147483648"

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

// ��ȫ�ֱ�����������Ƿ�Ϸ�
enum Status{kValid = 0, kInvalid};
int g_nStatus = kValid;

/*

���ư汾

*/
int StrToInt_v1(char* s)
{
	g_nStatus = kValid;

	// 1. ��ָ����
	if (s == nullptr)
	{
		g_nStatus = kInvalid;
		return 0;
	}

	// 2. ����ǰ��Ŀո񣨰����Ʊ�������з��ȣ�
	while (isspace(*s))
		++s;
	
	// 3. ��ȡ����
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
	
	// 4. ���ź�����ַ��������֣�����Ƿ�
	if (*s < '0' || *s > '9')
	{
		g_nStatus = kInvalid;
		return 0;
	}

	// 5. �洢��ʱ���֣�����������
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

	// 6. û�з������֣�������Ƿ� ���磺"+abc" ���� "-"��
	if (!hasAtLeastOneDigit)
		g_nStatus = kInvalid;

	// 7. �������֣�ȷ�������Լ�ת���������ͣ�
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