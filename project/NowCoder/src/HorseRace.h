#pragma once

/*

[编程题]赛马

在一条无限长的跑道上，有N匹马在不同的位置上出发开始赛马。当开始赛马比赛后，所有的马开始以自己的速度一直匀速前进。
每匹马的速度都不一样，且全部是同样的均匀随机分布。在比赛中当某匹马追上了前面的某匹马时，被追上的马就出局。 
请问按以上的规则比赛无限长的时间后，赛道上剩余的马匹数量的数学期望是多少

输入描述:
每个测试输入包含1个测试用例
输入只有一行，一个正整数N
1 <= N <= 1000


输出描述:
输出一个浮点数，精确到小数点后四位数字，表示剩余马匹数量的数学期望

输入例子1:
1
2

输出例子1:
1.0000
1.5000

Approach:

这尽然是一道40分的题目，而我竟然没做出来！！！
题目说了，每匹马的速度都不一样，则显然可以按照速度从大到小排序，h1>h2>h3>...>hn
显然，h1一定不会出局，期望为 1
h2不出局的条件是其初始位置在h1的后面，否则必然会被h1赶上淘汰，期望为 1/2
...
hn不出具的条件是其初始位置在其他所有马匹的后面，期望为 1/n

所以结果为 1 + 1/2 + 1/3 + ... + 1/n

*/

#include <iostream>

using namespace std;

class Solution {
public:
	double HorseRace(int N)
	{
		double result = 0.0;
		for (int i = 1; i <= N; ++i)
			result += 1.0 / i;
		return result;
	}
};

void driver()
{
	int N;
	cin >> N;
	Solution solu;
	double result = solu.HorseRace(N);
	cout.precision(4);
	cout << fixed << result << endl;
}

