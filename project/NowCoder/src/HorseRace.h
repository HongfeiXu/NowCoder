#pragma once

/*

[�����]����

��һ�����޳����ܵ��ϣ���Nƥ���ڲ�ͬ��λ���ϳ�����ʼ����������ʼ�������������е�����ʼ���Լ����ٶ�һֱ����ǰ����
ÿƥ�����ٶȶ���һ������ȫ����ͬ���ľ�������ֲ����ڱ����е�ĳƥ��׷����ǰ���ĳƥ��ʱ����׷�ϵ����ͳ��֡� 
���ʰ����ϵĹ���������޳���ʱ���������ʣ�����ƥ��������ѧ�����Ƕ���

��������:
ÿ�������������1����������
����ֻ��һ�У�һ��������N
1 <= N <= 1000


�������:
���һ������������ȷ��С�������λ���֣���ʾʣ����ƥ��������ѧ����

��������1:
1
2

�������1:
1.0000
1.5000

Approach:

�⾡Ȼ��һ��40�ֵ���Ŀ�����Ҿ�Ȼû������������
��Ŀ˵�ˣ�ÿƥ�����ٶȶ���һ��������Ȼ���԰����ٶȴӴ�С����h1>h2>h3>...>hn
��Ȼ��h1һ��������֣�����Ϊ 1
h2�����ֵ����������ʼλ����h1�ĺ��棬�����Ȼ�ᱻh1������̭������Ϊ 1/2
...
hn�����ߵ����������ʼλ��������������ƥ�ĺ��棬����Ϊ 1/n

���Խ��Ϊ 1 + 1/2 + 1/3 + ... + 1/n

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
