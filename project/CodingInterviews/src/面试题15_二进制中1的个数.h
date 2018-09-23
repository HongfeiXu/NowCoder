#pragma once

/*

面试题15：二进制中的1的个数

题目描述
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。

*/

#include <iostream>
#include <bitset>
#include <string>

using namespace std;

class Solution {
public:
	// time O(sizeof(int) * 8)
	int  NumberOf1(int n)
	{
		int cnt = 0;
		int numOfBits = sizeof(int) * 8;
		for (int i = 0; i < numOfBits; ++i)
		{
			if (n & (1 << i))
				++cnt;
		}
		return cnt;
	}
};

class Solution2 {
public:
	int NumberOf1(int n)
	{
		int cnt = 0;
		// 如果n!=0，则一定存在二进制位为1的情况
		while (n)
		{
			++cnt;
			// 把n的二进制表示中的最右边1变成0
			n = (n - 1) & n;
		}
		return cnt;
	}
};

class Solution3 {
public:
	int NumberOf1(int n)
	{
		bitset<sizeof(int) * 8> b(n);
		return b.count();
	}
};

void test()
{
	Solution3 solu;
	cout << solu.NumberOf1(-10) << endl;
}

void driver()
{
	test();
}
