#pragma once

/*

��������:
����ĵ�һ��Ϊһ��������T����ʾ�������������� ��������T�����ݡ�ÿ�����ݵĵ�һ�а�����������m��n����ʾ�ַ������������������
��������m�У�ÿһ��Ϊһ������Ϊn���ַ�������˳���ʾÿһ��֮�е��ַ����ٽ���������һ�а���һ���ַ�������ʾҪѰ�ҵĵ��ʡ�  
���ݷ�Χ�� �����������ݣ�������1<=T<=9�������������λ���ַ�����͵����е��ַ���Ϊ��д��ĸ��ҪѰ�ҵĵ������Ϊ2���ַ���
�Ϊ9���ַ����ַ����������������СΪ1�����Ϊ99�� ��������50%�������ļ����ַ������������������Ϊ���Ϊ20��


�������:
����ÿһ�����ݣ����һ�У�����һ��������Ϊ�ڸ������ַ��������ҵ������ĵ��ʵĺϷ���������

��������1:
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

�������1:
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
	
	// ����
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

	// ����
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

	// ����45�ȷ���
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