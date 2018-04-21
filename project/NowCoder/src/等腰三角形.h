#pragma once
/*

等腰三角形

4
...*
..*.*
.*...*
*******

AC

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

void constructTriangle(int h)
{
	vector<string> result;
	// 从下向上构造三角形
	for (int i = h; i >= 1; --i)
	{
		string curr = "";
		if (i == h)
			curr.assign(2 * h - 1, '*');
		else if (i == 1)
		{
			string begin_dot(h - i, '.');
			curr.append(begin_dot);
			curr.push_back('*');
		}
		else
		{
			string begin_dot(h - i, '.');
			curr.append(begin_dot);
			curr.push_back('*');
			string mid_dot(2 * i - 3, '.');
			curr.append(mid_dot);
			curr.push_back('*');
		}

		result.push_back(curr);
	}
	// 逆序输出
	copy(result.rbegin(), result.rend(), ostream_iterator<string>(cout, "\n"));
}

void constructTriangle_v2(int h)
{
	//vector<string> result(h);
	for (int i = 1; i <= h; ++i)
	{
		string curr;
		if (i == 1)
		{
			curr.append(h - 1, '.');
			curr.push_back('*');
		}
		else if (i == h)
		{
			curr.append(2 * h - 1, '*');
		}
		else
		{
			curr.append(h - i, '.');
			curr.push_back('*');
			curr.append(2 * i - 3, '.');
			curr.push_back('*');
		}
		cout << curr << endl;
		//result[i - 1] = curr;
	}
	// 正序输出
	//copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));
}

void driver()
{
	int h;
	cin >> h;
	constructTriangle_v2(h);
}

/*

6
.....*
....*.*
...*...*
..*.....*
.*.......*
***********
请按任意键继续. . .

*/