#pragma once

/*

�ж�ʱ�ӡ����ӡ�����ʱ���Ƿ񳬹��Ϸ���Χ��������������޸ĸ�λΪ0���ɡ�

*/

#include <iostream>
#include <string>

using namespace std;

void ModifyTime(string& inputTime)
{
	string hours(inputTime.begin(), inputTime.begin() + 2);
	string mins(inputTime.begin() + 3, inputTime.begin() + 5);
	string secs(inputTime.begin() + 6, inputTime.end());

	int hoursInt = stoi(hours);
	int minsInt = stoi(mins);
	int secsInt = stoi(secs);

	if (hoursInt > 23)
	{
		hours[0] = '0';
	}
	if (minsInt > 59)
	{
		mins[0] = '0';
	}
	if (secsInt > 59)
	{
		secs[0] = '0';
	}
	inputTime = hours + ":"+ mins + ":" + secs;
}

void Driver()
{
	int cnt = 0;
	cin >> cnt;
	string inputTime;
	for (int i = 0; i < cnt; ++i)
	{
		cin >> inputTime;
		ModifyTime(inputTime);
		cout << inputTime << endl;
	}
}