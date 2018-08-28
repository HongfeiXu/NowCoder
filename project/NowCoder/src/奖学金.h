#pragma once

/*

题目：奖学金

题目描述
小v今年有n门课，每门都有考试，为了拿到奖学金，小v必须让自己的平均成绩至少为avg。每门课由平时成绩和考试成绩组成，满分为r。
现在他知道每门课的平时成绩为ai ,若想让这门课的考试成绩多拿一分的话，小v要花bi 的时间复习，不复习的话当然就是0分。
同时我们显然可以发现复习得再多也不会拿到超过满分的分数。为了拿到奖学金，小v至少要花多少时间复习。

输入描述:
第一行三个整数n,r,avg(n大于等于1小于等于1e5，r大于等于1小于等于1e9,avg大于等于1小于等于1e6)，接下来n行，每行两个整数ai和bi，均小于等于1e6大于等于1

输出描述:
一行输出答案。

示例1

输入
5 10 9
0 5
9 1
8 1
0 1
9 100

输出
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

// 细读题目会发现，这里的返回值可能是一个超过INT_MAX的值
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