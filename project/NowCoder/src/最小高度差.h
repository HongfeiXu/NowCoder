#pragma once

// ˼·��Greedy

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void findMinMaxId(vector<int>& towers, int& minId, int& maxId)
{
	minId = 0;
	maxId = 0;
	for (int i = 0; i < towers.size(); ++i)
	{
		if (towers[i] < towers[minId])
			minId = i;
		if (towers[i] > towers[maxId])
			maxId = i;
	}
}

bool adjustTowerHeight(vector<int>& towers, vector<pair<int, int>>& moves, int& minGap)
{
	//if (towers.empty())
	//	return false;

	int minId = 0, maxId = 0;
	findMinMaxId(towers, minId, maxId);
	// ����ߵ����Ͱ������߶Ȳ���ڵ���2ʱ���нн���������û�б�Ҫ
	if (towers[maxId] - towers[minId] >= 2)
	{
		moves.push_back({ maxId + 1, minId + 1 });
		--towers[maxId];
		++towers[minId];
		minGap = towers[maxId] - towers[minId];
		return true;
	}
	else
	{
		minGap = towers[maxId] - towers[minId];
		return false;
	}
}

void driver()
{
	int n, k;
	cin >> n >> k;		// 1 <=n <= 100, 1 <= k <= 1000
	vector<int> towers(n, 0);
	for (int i = 0; i < n; ++i)
	{
		cin >> towers[i];
	}
	int count = 0;		// �ƶ�������Ĵ���
	int minGap = -1;
	vector<pair<int, int>> moves;
	for (int i = 0; i < k; ++i)
	{
		// ���û�н��е�����������˵���Ѿ��ﵽ����С�߶Ȳ�0
		if (!adjustTowerHeight(towers, moves, minGap))
			break;
		++count;
	}
	cout << minGap << " " <<count << endl;
	for (int i = 0; i < moves.size(); ++i)
	{
		cout << moves[i].first << " " << moves[i].second << endl;
	}
}