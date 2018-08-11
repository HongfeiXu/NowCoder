#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void foo()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		int N;
		cin >> N;
		map<string, string> dict;
		vector<string> regionNumbers;
		for (int j = 0; j < N; ++j)
		{
			string number;
			string position;
			cin >> number >> position;
			auto firstXPos = number.find('x');
			number = number.substr(0, firstXPos);
			dict[number] = position;
			regionNumbers.push_back(number);
		}
		int M;
		cin >> M;
		for (int j = 0; j < M; ++j)
		{
			string inputNumber;
			cin >> inputNumber;

			if (inputNumber.length() != 11)
			{
				cout << "unknown" << endl;
				continue;
			}

			bool exists = false;
			for (int k = 0; k < regionNumbers.size(); ++k)
			{
				int regionNumberLen = regionNumbers[k].length();
				if (inputNumber.length() > regionNumberLen && inputNumber.substr(0, regionNumberLen) == regionNumbers[k])
				{
					cout << dict[regionNumbers[k]] << endl;
					exists = true;
					break;
				}
			}
			if (!exists)
				cout << "unknown" << endl;
		}
	}
}