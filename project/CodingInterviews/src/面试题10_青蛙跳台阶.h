#pragma once

/*

面试题10：青蛙跳台阶问题

一只青蛙一次可以跳1级台阶，也可以跳2级台阶。求该青蛙跳上一个n级台阶总共由多少种跳法。

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
