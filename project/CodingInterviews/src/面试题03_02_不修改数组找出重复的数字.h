#pragma once

/*

面试题03_02：不修改数组找出重复的数字

题目：在一个长度为n+1的数组里的所有数字都在1到n的范围内，所以数组中至
少有一个数字是重复的。请找出数组中任意一个重复的数字，但不能修改输入的
数组。例如，如果输入长度为8的数组{2, 3, 5, 4, 3, 2, 6, 7}，那么对应的
输出是重复的数字2或者3。

===========================================
Apporach:

不准修改数组，则我们使用 unordered_set 记录已经存在的数字，如果遇到已经在 unordered_set 中存在的数字，则为重复的。
同样的，我们可以直接使用数组来实现简单的哈希表，因为这里key的范围在1到n之间。

Time: O(n)
Space: O(n)

===========================================
Approach_v2:

尝试避免 Space: O(n)，使用二分法 + 计数法。

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
参数：
numbers: 数组
duplication: 重复的数字

返回值：
true: 存在重复数字
false: 不存在重复数字或者数组中数字无效

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

// 与上面的方法一样，只是使用数组来实现简单的哈希表
bool duplicate_v2(const vector<int>& numbers, int& duplication)
{
	int len = numbers.size();
	int n = len - 1;
	for (int i = 0; i < len; ++i)
	{
		if (numbers[i] < 1 || numbers[i] > n)
			return false;
	}
	// 用数组实现简单的hash表
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
参数：
numbers: 数组
left: 起始大小
right: 终止大小

返回值：
numbers 中大小在 [left, right] 中数字的个数
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

	// 二分法 + 计数
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

// ====================测试代码================

void test(const std::string& testName, std::vector<int>& numbers, std::vector<int>& expected, bool expectedRet)
{
	std::cout << testName << " begins: ";
	int duplication = 0;
	bool ret = duplicate(numbers, duplication);

	if (expectedRet == ret)
	{
		// 若存在重复数字，需要判断得到的重复数字是否真的重复
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
		// 若不存在重复数字，则直接通过测试
		else
		{
			std::cout << "Passed.\n";
		}
	}
	// 若函数返回结果与期待的结果不同，不通过
	else
	{
		std::cout << "FAILED.\n";
	}
}

// 重复的数字是数组中最小的数字
void test1()
{
	std::vector<int> numbers { 2,1,3,1,4 };
	std::vector<int> duplications { 1 };
	test("Test1", numbers, duplications, true);
}

// 重复的数字是数组中最大的数字
void test2()
{
	std::vector<int> numbers { 2,4,3,1,4 };
	std::vector<int> duplications { 4 };
	test("Test2", numbers, duplications, true);
}

// 存在多个重复数字
void test3()
{
	std::vector<int> numbers { 2,4,2,1,4 };
	std::vector<int> duplications { 2, 4 };
	test("Test3", numbers, duplications, true);
}

// 没有重复数字
void test4()
{
	std::vector<int> numbers { 2,1,3,0,4 };
	std::vector<int> duplications { -1 };		// not use in the test function
	test("Test4", numbers, duplications, false);
}

// 没有重复的数字
void test5()
{
	std::vector<int> numbers { 2,1,3,5,4 };
	std::vector<int> duplications { -1 };		// not use in the test function
	test("Test5", numbers, duplications, false);
}

// 无效的输入
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