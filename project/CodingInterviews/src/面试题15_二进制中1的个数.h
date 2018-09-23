#pragma once

/*

������15���������е�1�ĸ���

��Ŀ����
����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ��

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
		// ���n!=0����һ�����ڶ�����λΪ1�����
		while (n)
		{
			++cnt;
			// ��n�Ķ����Ʊ�ʾ�е����ұ�1���0
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
