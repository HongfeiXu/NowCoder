#pragma once

/*

������04����ά�����еĲ���

��Ŀ����һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж���
�մ��ϵ��µ�����˳�����������һ������������������һ����ά�����һ��
�������ж��������Ƿ��и�������

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

// ====================���Դ���================

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
