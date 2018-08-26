#pragma once

/*

小易在学校中学习了关于字符串的理论，于是他基于此完成了一个字典的项目。
小易的这个字典很奇特，字典内的每个单词都包含n个'a'和m个'z'，并且所有单词按照字典序排列。
小易现在希望你能帮他找出第k个单词是什么。

输入描述：
输入包括一行三个整数n，m，k（1 <= n, m <= 100, 1 <= k <= 10^9），以空格分隔。

输出描述：
输出第k个字典中的字符串，如果无解，输出-1。

示例1：
输入：
2 2 6
输出：
zzaa
说明：
字典中的字符串依次为 aazz azaz azza zaaz zaza zzaa

TODO

法一：Pass 30%，时间复杂度太高

法二：https://github.com/LyricYang/Internet-Recruiting-Algorithm-Problems/blob/master/NETEASE/Problem%20Description%202018.md#%E7%AC%AC%E5%8D%81%E4%B8%80%E9%A2%98

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution 
{
public:
	// 获得字符串a的全排列中第k个字符串
	string permute(string a, int k)
	{
		if (a.empty())
			return a;

		sort(a.begin(), a.end());
		if (k == 1)
			return a;
		for (int i = 2; i <= k; ++i)
		{
			next_permutation(a.begin(), a.end());
		}
		return a;
	}

	int factorial(int n)
	{
		if (n == 0 || n == 1)
			return 1;
		else
			return factorial(n - 1) * n;
	}

	// numOfA个'a'和numOfZ个'z'一共有多少种排列
	int permuteCnt(int numOfA, int numOfZ)
	{
		return factorial(numOfA + numOfZ) / (factorial(numOfA) * factorial(numOfZ));
	}

	void solve()
	{
		int n, m, k;
		cin >> n >> m >> k;
		string s(n, 'a');
		s.append(m, 'z');

		int totalNumberOfPermute = permuteCnt(n, m);
		cout << "permuteCnt:" << totalNumberOfPermute << endl;
		if (totalNumberOfPermute < k)
		{
			cout << -1 << endl;
			return;
		}

		cout << permute(s, k) << endl;
	}
};

