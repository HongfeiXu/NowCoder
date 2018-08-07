#pragma once

/*

输入描述:
输入的第一行为一个正整数T，表示测试数据组数。 接下来有T组数据。每组数据的第一行包括两个整数m和n，表示字符迷阵的行数和列数。
接下来有m行，每一行为一个长度为n的字符串，按顺序表示每一行之中的字符。再接下来还有一行包括一个字符串，表示要寻找的单词。  
数据范围： 对于所有数据，都满足1<=T<=9，且输入的所有位于字符迷阵和单词中的字符都为大写字母。要寻找的单词最短为2个字符，
最长为9个字符。字符迷阵和行列数，最小为1，最多为99。 对于其中50%的数据文件，字符迷阵的行列数更限制为最多为20。


输出描述:
对于每一组数据，输出一行，包含一个整数，为在给定的字符迷阵中找到给定的单词的合法方案数。

输入例子1:
3
10 10
AAAAAADROW
WORDBBBBBB
OCCCWCCCCC
RFFFFOFFFF
DHHHHHRHHH
ZWZVVVVDID
ZOZVXXDKIR
ZRZVXRXKIO
ZDZVOXXKIW
ZZZWXXXKIK
WORD
3 3
AAA
AAA
AAA
AA
5 8
WORDSWOR
ORDSWORD
RDSWORDS
DSWORDSW
SWORDSWO
SWORD

输出例子1:
4
16
5

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;


int CountString(const vector<vector<char>>& table, const string& target, int m, int n)
{
	if (m == 0 || n == 0)
		return 0;
	int len = target.size();

	int cnt = 0;
	
	// 横向
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n - len + 1; ++j)
		{
			string temp;
			for (int k = 0; k < len; ++k)
			{
				temp.push_back(table[i][j + k]);
			}
			if (temp == target)
				++cnt;
		}
	}

	// 纵向
	for (int i = 0; i < m - len + 1; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			string temp;
			for (int k = 0; k < len; ++k)
			{
				temp.push_back(table[i + k][j]);
			}
			if (temp == target)
				++cnt;
		}
	}

	// 右下45度方向
	for (int i = 0; i < m - len + 1; ++i)
	{
		for (int j = 0; j < n - len + 1; ++j)
		{
			string temp;
			for (int k = 0; k < len; ++k)
			{
				temp.push_back(table[i + k][j + k]);
			}
			if (temp == target)
				++cnt;
		}
	}

	return cnt;
}

void Driver()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		int m, n;
		cin >> m >> n;
		vector<vector<char>> table(m, vector<char>(n, ' '));
		for (int j = 0; j < m; ++j)
		{
			for (int k = 0; k < n; ++k)
			{
				cin >> table[j][k];
			}
		}
		string target;
		cin >> target;
		cout << CountString(table, target, m, n) << endl;
	}
}