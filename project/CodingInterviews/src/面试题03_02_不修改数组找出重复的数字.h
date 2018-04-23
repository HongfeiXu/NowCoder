#pragma once

/*

������03_02�����޸������ҳ��ظ�������

��Ŀ����һ������Ϊn+1����������������ֶ���1��n�ķ�Χ�ڣ�������������
����һ���������ظ��ġ����ҳ�����������һ���ظ������֣��������޸������
���顣���磬������볤��Ϊ8������{2, 3, 5, 4, 3, 2, 6, 7}����ô��Ӧ��
������ظ�������2����3��

===========================================
Apporach:

��׼�޸����飬������ʹ�� unordered_set ��¼�Ѿ����ڵ����֣���������Ѿ��� unordered_set �д��ڵ����֣���Ϊ�ظ��ġ�
ͬ���ģ����ǿ���ֱ��ʹ��������ʵ�ּ򵥵Ĺ�ϣ����Ϊ����key�ķ�Χ��1��n֮�䡣

Time: O(n)
Space: O(n)

===========================================
Approach_v2:

���Ա��� Space: O(n)��ʹ�ö��ַ� + ��������

Time: O(nlgn)
Space: O(1)

*/

#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;


// ====================Approach_v1================

/*
������
numbers: ����
duplication: �ظ�������

����ֵ��
true: �����ظ�����
false: �������ظ����ֻ���������������Ч

*/
bool duplicate(const vector<int>& numbers, int& duplication)
{
	int len = numbers.size();
	int n = len - 1;
	for (int i = 0; i < len; ++i)
	{
		if (numbers[i] < 1 || numbers[i] > n)
			return false;
	}

	unordered_set<int> us;
	for (int i = 0; i < len; ++i)
	{
		if (us.find(numbers[i]) == us.end())
		{
			us.insert(numbers[i]);
		}
		else
		{
			duplication = numbers[i];
			return true;
		}
	}
	return false;
}

// ������ķ���һ����ֻ��ʹ��������ʵ�ּ򵥵Ĺ�ϣ��
bool duplicate_v2(const vector<int>& numbers, int& duplication)
{
	int len = numbers.size();
	int n = len - 1;
	for (int i = 0; i < len; ++i)
	{
		if (numbers[i] < 1 || numbers[i] > n)
			return false;
	}
	// ������ʵ�ּ򵥵�hash��
	vector<int> us(len, -1);
	for (int i = 0; i < len; ++i)
	{
		if (us[numbers[i]] == numbers[i])
		{
			duplication = numbers[i];
			return true;
		}
		else
		{
			us[numbers[i]] = numbers[i];
		}
	}
	
	return false;
}

// ====================Approach_v2================

/*
������
numbers: ����
left: ��ʼ��С
right: ��ֹ��С

����ֵ��
numbers �д�С�� [left, right] �����ֵĸ���
*/
int count_range(const vector<int>& numbers, int left, int right)
{
	int ret = 0;
	for (auto item : numbers)
	{
		if (item >= left && item <= right)
			++ret;
	}
	return ret;
}

bool duplicate_v3(const vector<int>& numbers, int& duplication)
{
	int len = numbers.size();
	if (len == 0)
		return false;
	int n = len - 1;
	for (int i = 0; i < len; ++i)
	{
		if (numbers[i] < 1 || numbers[i] > n)
			return false;
	}

	// ���ַ� + ����
	int left = 1;
	int right = n;
	while (left < right)
	{
		int mid = (left + right) / 2;
		int left_cnt = count_range(numbers, left, mid);
		if (left_cnt > mid - left + 1)
		{
			right = mid;
			continue;
		}
		int right_cnt = count_range(numbers, mid + 1, right);
		if (right_cnt > right - mid)
		{
			left = mid + 1;
			continue;
		}
	}
	duplication = numbers[left];
	return true;
}

// ====================���Դ���================

void test(const std::string& testName, std::vector<int>& numbers, std::vector<int>& expected, bool expectedRet)
{
	std::cout << testName << " begins: ";
	int duplication = 0;
	bool ret = duplicate(numbers, duplication);

	if (expectedRet == ret)
	{
		// �������ظ����֣���Ҫ�жϵõ����ظ������Ƿ�����ظ�
		if (expectedRet)
		{
			if (std::find(expected.begin(), expected.end(), duplication) != expected.end())
			{
				std::cout << "Passed.\n";
			}
			else
			{
				std::cout << "FAILED.\n";
			}
		}
		// ���������ظ����֣���ֱ��ͨ������
		else
		{
			std::cout << "Passed.\n";
		}
	}
	// ���������ؽ�����ڴ��Ľ����ͬ����ͨ��
	else
	{
		std::cout << "FAILED.\n";
	}
}

// �ظ�����������������С������
void test1()
{
	std::vector<int> numbers { 2,1,3,1,4 };
	std::vector<int> duplications { 1 };
	test("Test1", numbers, duplications, true);
}

// �ظ�����������������������
void test2()
{
	std::vector<int> numbers { 2,4,3,1,4 };
	std::vector<int> duplications { 4 };
	test("Test2", numbers, duplications, true);
}

// ���ڶ���ظ�����
void test3()
{
	std::vector<int> numbers { 2,4,2,1,4 };
	std::vector<int> duplications { 2, 4 };
	test("Test3", numbers, duplications, true);
}

// û���ظ�����
void test4()
{
	std::vector<int> numbers { 2,1,3,0,4 };
	std::vector<int> duplications { -1 };		// not use in the test function
	test("Test4", numbers, duplications, false);
}

// û���ظ�������
void test5()
{
	std::vector<int> numbers { 2,1,3,5,4 };
	std::vector<int> duplications { -1 };		// not use in the test function
	test("Test5", numbers, duplications, false);
}

// ��Ч������
void test6()
{
	std::vector<int> numbers { };
	std::vector<int> duplications { -1 };		// not use in the test function
	test("Test6", numbers, duplications, false);
}

void test7()
{
	std::vector<int> numbers { 1,3,9,2,3 };
	std::vector<int> duplications { -1 };		// not use in the test function
	test("Test7", numbers, duplications, false);
}

void driver()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
}