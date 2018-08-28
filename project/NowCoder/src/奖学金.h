#pragma once

/*

��Ŀ����ѧ��

��Ŀ����
Сv������n�ſΣ�ÿ�Ŷ��п��ԣ�Ϊ���õ���ѧ��Сv�������Լ���ƽ���ɼ�����Ϊavg��ÿ�ſ���ƽʱ�ɼ��Ϳ��Գɼ���ɣ�����Ϊr��
������֪��ÿ�ſε�ƽʱ�ɼ�Ϊai ,���������ſεĿ��Գɼ�����һ�ֵĻ���СvҪ��bi ��ʱ�临ϰ������ϰ�Ļ���Ȼ����0�֡�
ͬʱ������Ȼ���Է��ָ�ϰ���ٶ�Ҳ�����õ��������ֵķ�����Ϊ���õ���ѧ��Сv����Ҫ������ʱ�临ϰ��

��������:
��һ����������n,r,avg(n���ڵ���1С�ڵ���1e5��r���ڵ���1С�ڵ���1e9,avg���ڵ���1С�ڵ���1e6)��������n�У�ÿ����������ai��bi����С�ڵ���1e6���ڵ���1

�������:
һ������𰸡�

ʾ��1

����
5 10 9
0 5
9 1
8 1
0 1
9 100

���
43

*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool sortbysec(const pair<int, int>& lhs, const pair<int, int>& rhs)
{
	return lhs.second < rhs.second || (lhs.second == rhs.second && lhs.first < rhs.first);
}

// ϸ����Ŀ�ᷢ�֣�����ķ���ֵ������һ������INT_MAX��ֵ
long long calLeastTime(int n, int r, int avg, vector<pair<int, int>>& info)
{
	int targetTotalScore = n * avg;
	int currentToatalScore = 0;
	for (int i = 0; i < info.size(); ++i)
	{
		currentToatalScore += info[i].first;
	}

	if (currentToatalScore >= targetTotalScore)
		return 0;

	int remainScore = targetTotalScore - currentToatalScore;
	sort(info.begin(), info.end(), sortbysec);

	long long totalTime = 0;

	for (int i = 0; i < info.size(); ++i)
	{
		int testScore = r - info[i].first;
		if (testScore >= remainScore)
		{
			totalTime += remainScore * info[i].second;
			break;
		}
		else
		{
			totalTime += testScore * info[i].second;
			remainScore -= testScore;
		}
	}

	return totalTime;
}

void driver()
{
	ifstream input("testcases/scholarship.txt");

	int n, r, avg;
	input >> n >> r >> avg;
	vector<pair<int, int>> info;
	info.reserve(n);
	for (int i = 0; i < n; ++i)
	{
		int a, b;
		input >> a >> b;
		info.push_back({ a, b });
	}

	cout << calLeastTime(n, r, avg, info) << endl;
}