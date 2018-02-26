#pragma once

/*

[�����] �ַ�������
ʱ�����ƣ�1��

�ռ����ƣ�32768K

����һ���ַ��������㽫�ַ������±��룬���������ַ��滻�ɡ��������ֵĸ���+�ַ����������ַ���AAAABCCDAA�ᱻ�����4A1B2C1D2A��
��������:
ÿ�������������1����������
ÿ��������������ֻ��һ���ַ������ַ���ֻ������дӢ����ĸ�����Ȳ�����10000��


�������:
����������ַ���

��������1:
AAAABCCDAA

�������1:
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