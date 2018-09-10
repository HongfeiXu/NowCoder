#pragma once

/*

������10��������̨������

һֻ����һ�ο�����1��̨�ף�Ҳ������2��̨�ס������������һ��n��̨���ܹ��ɶ�����������

*/

int climbStairs(int n)
{
	int dp[2] = { 1, 2 };
	if (n < 3)
	{
		return dp[n - 1];
	}
	int temp = 0;
	for (int i = 3; i <= n; ++i)
	{
		temp = dp[1];
		dp[1] += dp[0];
		dp[0] = temp;
	}
	return dp[1];
}
