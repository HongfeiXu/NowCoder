#pragma once

/*



*/

#include <iostream>
#include <cmath>

using namespace std;

int CalTax(int salary)
{
	float tax = 0;
	int stage = 7;
	float edge[] = { 0, 3000, 12000, 25000, 35000, 55000, 80000 };
	float rate[] = { 0.03f, 0.1f, 0.2f, 0.25f, 0.30f, 0.35f, 0.45f };

	if (salary <= 5000)
		return 0;
	salary -= 5000;
	
	for (int i = 1; i < stage; ++i)
	{
		if (salary <= edge[i - 1])
			break;

		if (salary > edge[i - 1] && salary <= edge[i])
		{
			tax += (salary - edge[i - 1]) * rate[i - 1];
			return  static_cast<int>(round(tax));
		}
		tax += (edge[i] - edge[i - 1]) * rate[i - 1];
	}
	if (salary > edge[stage-1])
	{
		tax += (salary - edge[stage - 1]) * rate[stage - 1];
	}

	return static_cast<int>(round(tax));
}

void driver()
{
	int T;
	cin >> T;
	int salary = 0;
	for (int i = 0; i < T; ++i)
	{
		cin >> salary;
		cout << CalTax(salary) << endl;
	}
}