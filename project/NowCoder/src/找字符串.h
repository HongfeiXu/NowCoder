#pragma once

/*

С����ѧУ��ѧϰ�˹����ַ��������ۣ����������ڴ������һ���ֵ����Ŀ��
С�׵�����ֵ�����أ��ֵ��ڵ�ÿ�����ʶ�����n��'a'��m��'z'���������е��ʰ����ֵ������С�
С������ϣ�����ܰ����ҳ���k��������ʲô��

����������
�������һ����������n��m��k��1 <= n, m <= 100, 1 <= k <= 10^9�����Կո�ָ���

���������
�����k���ֵ��е��ַ���������޽⣬���-1��

ʾ��1��
���룺
2 2 6
�����
zzaa
˵����
�ֵ��е��ַ�������Ϊ aazz azaz azza zaaz zaza zzaa

TODO

��һ��Pass 30%��ʱ�临�Ӷ�̫��

������https://github.com/LyricYang/Internet-Recruiting-Algorithm-Problems/blob/master/NETEASE/Problem%20Description%202018.md#%E7%AC%AC%E5%8D%81%E4%B8%80%E9%A2%98

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution 
{
public:
	// ����ַ���a��ȫ�����е�k���ַ���
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

	// numOfA��'a'��numOfZ��'z'һ���ж���������
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

