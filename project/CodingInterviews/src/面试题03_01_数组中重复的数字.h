#pragma once

/*

������03_01���������ظ�������

��Ŀ����һ������Ϊn����������������ֶ���0��n-1�ķ�Χ�ڡ�������ĳЩ�������ظ��ģ�����֪���м��������ظ��ˣ�
Ҳ��֪��ÿ�������ظ��˼��Ρ����ҳ�����������һ���ظ������֡����磬������볤��Ϊ7������{2, 3, 1, 0, 2, 5, 3}��
��ô��Ӧ��������ظ�������2����3��

Approach:
���鳤��Ϊn������������0��n-1��Χ�ڡ��ú�������һ�㣬������һ��Time:O(n)������Space:O(1)���㷨

���ϵİ� numbers[i] ������ numbers[i] λ�ã�����λ�õ�ֵ�Ѿ��� numbers[i]�������ظ�Ԫ�ء�

Time: O(n)
Space: O(1)

*/

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

/*
������
numbers		: һ����������
duplication	:������������е�һ���ظ�������

����ֵ��
true	: ������Ч���������д����ظ�������
false	: ������Ч������������û���ظ�������
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