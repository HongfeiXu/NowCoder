#pragma once

/*

面试题03_01：数组中重复的数字

题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，
那么对应的输出是重复的数字2或者3。

Approach:
数组长度为n，所有数字在0到n-1范围内。好好利用这一点，可以有一个Time:O(n)，额外Space:O(1)的算法

不断的把 numbers[i] 交换到 numbers[i] 位置，若该位置的值已经是 numbers[i]，则发现重复元素。

Time: O(n)
Space: O(1)

*/

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

/*
参数：
numbers		: 一个整数数组
duplication	:（输出）数组中的一个重复的数字

返回值：
true	: 输入有效，且数组中存在重复的数字
false	: 输入无效，或者数组中没有重复的数字
*/
bool duplicate(std::vector<int> numbers, int& duplication)
{
	int len = numbers.size();

	for (int i = 0; i < len; ++i)
	{
		if (numbers[i] < 0 || numbers[i] > len - 1)
			return false;
	}

	for (int i = 0; i < len; ++i)
	{
		while (numbers[i] != i)
		{
			if (numbers[i] == numbers[numbers[i]])
			{
				duplication = numbers[i];
				return true;
			}
			std::swap(numbers[i], numbers[numbers[i]]);
		}
	}
	return false;
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
	std::vector<int> numbers {};
	std::vector<int> duplications { -1 };		// not use in the test function
	test("Test6", numbers, duplications, false);
}

void test7()
{
	std::vector<int> numbers { 1,3,9,2,3};
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