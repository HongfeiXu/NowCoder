#pragma once

/*

[�����] ����
ʱ�����ƣ�1��

�ռ����ƣ�32768K

��һ��N*N��������Ѱ�����кᣬ�������ϵ����£����ϵ����£����ַ����ֱ������D�����ֵĺ���������ֵ
��������:
ÿ�������������1��������������һ�а����������� N �� D :
3 <= N <= 100
1 <= D <= N
��������N�У�ÿ��N������d:
0 <= d <= 100


�������:
���һ����������ʾ�ҵ��ĺ͵����ֵ

��������1:
4 2
87 98 79 61
10 27 95 70
20 64 73 29
71 65 15 0

�������1:
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
			// �з���
			if (j + D - 1 < N)
			{
				int currSum = 0;
				for (int k = 0; k < D; ++k)
					currSum += table[i][j + k];
				maxSum = max(maxSum, currSum);
			}
			// �з���
			if (i + D - 1 < N)
			{
				int currSum = 0;
				for (int k = 0; k < D; ++k)
					currSum += table[i + k][j];
				maxSum = max(maxSum, currSum);
			}
			// ���ϵ�����
			if (i + D - 1 < N && j + D - 1 < N)
			{
				int currSum = 0;
				for (int k = 0; k < D; ++k)
					currSum += table[i + k][j + k];
				maxSum = max(maxSum, currSum);
			}
			// ���ϵ�����
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
