#pragma once

/*

��С��

#####################################
Approach v1[TLE]:

Brute Force

���� n1 + n2 + n3 + n4 ��С������з�ʽ����������

ʱ�临�Ӷȣ� (n1 + n2 + n3 + n4)!
0<=n<=3�������ʱ�临�Ӷ�Ϊ 12!

#####################################
Approach_v2[AC?]:

DP

dp[i][j][k][l] ��ʾi��A��j��B��k��C��l��D���ܻ�õ�������

dp[0][0][0][0] = 0

���ƹ�ϵΪ��
dp[i][j][k][l] = max{
						dp[i-1][j][k][l] + m1 * (M1 % 10),	i >= 1
						dp[i][j-1][k][l] + m2 * (M2 % 10),	j >= 1
						dp[i][j][k-1][l] + m3 * (M3 % 10),	k >= 1
						dp[i][j][k][l-1] + m4 * (M4 % 10),	l >= 1
					}
���� 
M1 Ϊi-1��A��j��B��k��C��l��D����������ĩβ��
M2 Ϊi��A��j-1��B��k��C��l��D����������ĩβ��
...

���Ӧ���� dp[n1][n2][n3][n4]

ʱ�临�Ӷ�
n1 * n2 * n3 * n4
0<=n<=3�������ʱ�临�Ӷ�Ϊ 3*3*3*3

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

#define MEASURE_TIME

void solver_dp()
{
	int n[4];
	int m[4];

	for (int i = 0; i < 4; ++i)
		cin >> n[i];
	for (int j = 0; j < 4; ++j)
		cin >> m[j];

	// measure time
#ifdef MEASURE_TIME
	auto t0 = std::chrono::high_resolution_clock::now();
#endif // MEASURE_TIME


	// dp[i][j][k][l]: ��ʾi��A��j��B��k��C��l��D���ܻ�õ�������
	vector<vector<vector<vector<int>>>> dp(n[0] + 1, vector<vector<vector<int>>>(n[1] + 1, vector<vector<int>>(n[2] + 1, vector<int>(n[3] + 1, 0))));
	// last_digit[i][j][k][l]: i��A��j��B��k��C��l��D�����������ĩβ����
	vector<vector<vector<vector<int>>>> last_digit(n[0] + 1, vector<vector<vector<int>>>(n[1] + 1, vector<vector<int>>(n[2] + 1, vector<int>(n[3] + 1, 0))));

	for (int i = 0; i <= n[0]; ++i)
	{
		for (int j = 0; j <= n[1]; ++j)
		{
			for (int k = 0; k <= n[2]; ++k)
			{
				for (int l = 0; l <= n[3]; ++l)
				{
					last_digit[i][j][k][l] = (i * m[0] + j * m[1] + k * m[2] + l * m[3]) % 10;
				}
			}
		}
	}

	for (int i = 0; i <= n[0]; ++i)
	{
		for (int j = 0; j <= n[1]; ++j)
		{
			for (int k = 0; k <= n[2]; ++k)
			{
				for (int l = 0; l <= n[3]; ++l)
				{
					if (i > 0)
					{
						int candidate = dp[i - 1][j][k][l] + last_digit[i - 1][j][k][l] * m[0];
						dp[i][j][k][l] = max(dp[i][j][k][l], candidate);
					}
					if (j > 0)
					{
						int candidate = dp[i][j - 1][k][l] + last_digit[i][j - 1][k][l] * m[1];
						dp[i][j][k][l] = max(dp[i][j][k][l], candidate);
					}
					if (k > 0)
					{
						int candidate = dp[i][j][k - 1][l] + last_digit[i][j][k - 1][l] * m[2];
						dp[i][j][k][l] = max(dp[i][j][k][l], candidate);
					}
					if (l > 0)
					{
						int candidate = dp[i][j][k][l - 1] + last_digit[i][j][k][l - 1] * m[3];
						dp[i][j][k][l] = max(dp[i][j][k][l], candidate);
					}
				}
			}
		}
	}
	cout << dp[n[0]][n[1]][n[2]][n[3]] << endl;

	// measure time
#ifdef MEASURE_TIME
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
#endif // MEASURE_TIME
}

int getScore(const vector<int>& balls)
{
	int result = 0;
	int curr_sum = balls[0];
	for (int i = 1; i < balls.size(); ++i)
	{
		result += balls[i] * (curr_sum % 10);
		curr_sum += balls[i];
	}
	return result;
}

void solver_bruteforce()
{
	int n[4];
	int m[4];

	for (int i = 0; i < 4; ++i)
		cin >> n[i];
	for (int j = 0; j < 4; ++j)
		cin >> m[j];

	// measure time
#ifdef MEASURE_TIME
	auto t0 = std::chrono::high_resolution_clock::now();
#endif // MEASURE_TIME
	vector<int> balls;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < n[i]; ++j)
			balls.push_back(m[i]);
	}

	sort(balls.begin(), balls.end());

	int max_score = 0;
	do
	{
		int curr_score = getScore(balls);
		max_score = max(max_score, curr_score);

	} while (next_permutation(balls.begin(), balls.end()));

	cout << max_score << endl;

	// measure time
#ifdef MEASURE_TIME
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
#endif // MEASURE_TIME
}


void driver()
{
	solver_dp();
}