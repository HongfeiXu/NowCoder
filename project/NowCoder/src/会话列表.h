#pragma once

/*

从后向前访问每一行 id 序列，对于没访问过的 id，加入结果序列尾部，对于访问过的 id（用 unordered_set 控制），跳过。

*/

#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

void GetLine(vector<int>& resultIdSeq, vector<int>& rawIdSeq)
{
	unordered_set<int> us;
	for (auto iter = rawIdSeq.rbegin(); iter != rawIdSeq.rend(); ++iter)
	{
		if (us.find(*iter) == us.end())
		{
			us.insert(*iter);
			resultIdSeq.push_back(*iter);
		}
	}
}

void Driver()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		int N;
		cin >> N;
		vector<int> rawIdSeq(N);
		for (int j = 0; j < N; ++j)
			cin >> rawIdSeq[j];
		vector<int> resultIdSeq;
		GetLine(resultIdSeq, rawIdSeq);
		for (int j = 0; j < int(resultIdSeq.size()) - 1; ++j)
		{
			cout << resultIdSeq[j] << " ";
		}
		cout << resultIdSeq.back() << endl;
	}
}
