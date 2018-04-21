#pragma once

/*

[编程题] 最大和
时间限制：1秒

空间限制：32768K

在一个N*N的数组中寻找所有横，竖，左上到右下，右上到左下，四种方向的直线连续D个数字的和里面最大的值
输入描述:
每个测试输入包含1个测试用例，第一行包括两个整数 N 和 D :
3 <= N <= 100
1 <= D <= N
接下来有N行，每行N个数字d:
0 <= d <= 100


输出描述:
输出一个整数，表示找到的和的最大值

输入例子1:
4 2
87 98 79 61
10 27 95 70
20 64 73 29
71 65 15 0

输出例子1:
193

*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void solver()
{
	int N, D;
	cin >> N >> D;
	vector<vector<int>> table(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> table[i][j];
	int maxSum = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			// 行方向
			if (j + D - 1 < N)
			{
				int currSum = 0;
				for (int k = 0; k < D; ++k)
					currSum += table[i][j + k];
				maxSum = max(maxSum, currSum);
			}
			// 列方向
			if (i + D - 1 < N)
			{
				int currSum = 0;
				for (int k = 0; k < D; ++k)
					currSum += table[i + k][j];
				maxSum = max(maxSum, currSum);
			}
			// 左上到右下
			if (i + D - 1 < N && j + D - 1 < N)
			{
				int currSum = 0;
				for (int k = 0; k < D; ++k)
					currSum += table[i + k][j + k];
				maxSum = max(maxSum, currSum);
			}
			// 右上到左下
			if (i + D - 1 < N && j - D + 1 >= 0)
			{
				int currSum = 0;
				for (int k = 0; k < D; ++k)
				{
					currSum += table[i + k][j - k];
				}
				maxSum = max(maxSum, currSum);
			}
		}
	}
	cout << maxSum << endl;
}
