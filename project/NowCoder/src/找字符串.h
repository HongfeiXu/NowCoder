#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ����ַ���a��ȫ���У����ֵ�������
vector<string> permute(string a)
{
	vector<string> result;
	if (a.empty())
		return result;

	sort(a.begin(), a.end());
	result.push_back(a);
	while (next_permutation(a.begin(), a.end()))
		result.push_back(a);
	return result;
}

void driver()
{
	int n, m, k;
	cin >> n >> m >> k;
	string s(n, 'a');
	string temp(m, 'z');
	s.append(temp);
	vector<string> worlds = permute(s);
	if (worlds.size() < k)
		cout << "-1" << endl;
	else
		cout << worlds[k - 1] << endl;
}