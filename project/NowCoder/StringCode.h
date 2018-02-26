#pragma once

/*

[编程题] 字符串编码
时间限制：1秒

空间限制：32768K

给定一个字符串，请你将字符串重新编码，将连续的字符替换成“连续出现的个数+字符”。比如字符串AAAABCCDAA会被编码成4A1B2C1D2A。
输入描述:
每个测试输入包含1个测试用例
每个测试用例输入只有一行字符串，字符串只包括大写英文字母，长度不超过10000。


输出描述:
输出编码后的字符串

输入例子1:
AAAABCCDAA

输出例子1:
4A1B2C1D2A

*/

#include <string>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void solver()
{
	string S;
	cin >> S;
	vector<pair<int, char>> table;
	for (int i = 0; i < S.size();)
	{
		pair<int, char> item { 1, S[i] };
		int j = i + 1;
		while (j < S.size() && S[i] == S[j])
		{
			++item.first;
			++j;
		}
		table.push_back(item);
		i = j;
	}
	string result;
	for (const auto & item : table)
	{
		result.append(to_string(item.first));
		result.push_back(item.second);
	}
	cout << result << endl;
}