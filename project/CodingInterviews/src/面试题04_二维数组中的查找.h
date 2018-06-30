#pragma once

/*

面试题04：二维数组中的查找

题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按
照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个
整数，判断数组中是否含有该整数。

*/

#include <vector>
#include <iostream>

using namespace std;

bool Find(vector<vector<int>>& matrix, int number)
{
	int m = matrix.size();
	if (m == 0)
	{
		return false;
	}
	int n = matrix[0].size();

	int i = m - 1;
	int j = 0;
	while (i >= 0 && j < n)
	{
		if (matrix[i][j] == number)
		{
			return true;
		}

		if (matrix[i][j] < number)
		{
			++j;
		}
		else
		{
			--i;
		}
	}

	return false;
}

// ====================测试代码================

void test()
{
	vector<vector<int>> matrix = {
		{1,2,8,9},
		{2,4,9,12},
		{4,7,10,13},
		{6,8,11,15}
	};

	cout << boolalpha << Find(matrix, 7) << endl;
	cout << boolalpha << Find(matrix, -1) << endl;
	cout << boolalpha << Find(matrix, 17) << endl;

	vector<int> &temp = matrix[0];
	matrix.clear();
	cout << boolalpha << Find(matrix, 1) << endl;
}
