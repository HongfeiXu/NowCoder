#pragma once

/*

������33�������������ĺ����������

��Ŀ������һ���������飬�жϸ������ǲ���ĳ�����������ĺ�����������
����ǣ��򷵻� true�����򷵻� false���������������������������ֶ�������ͬ��

˼·������������е����һ���ڵ㽫���з�Ϊǰ���������֣���һ�������������ڵ��ֵ�����ȸ��ڵ�С���ڶ��������������ڵ��ֵ�����ȸ��ڵ�󡣣�������
ȷ������֮����ȥ�ݹ��ж�ÿ�������Ƿ������������

*/

#include <iostream>
#include <vector>

using namespace std;

bool VerifySequenceOfBST(int sequence[], int length)
{
	if (length == 0 )
		return false;
	int root = sequence[length - 1];
	int i = 0;
	for (; i < length - 1; ++i)
	{
		if (sequence[i] > root)
			break;
	}
	int j = i;
	for (; j < length - 1; ++j)
	{
		if (sequence[j] < root)
			return false;
	}

	bool left = true;
	if (i > 0)
		left = VerifySequenceOfBST(sequence, i);
	bool right = true;
	if (i < length - 1)
		right = VerifySequenceOfBST(sequence + i, length - i - 1);
	return left && right;
}

// �����
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		int len = sequence.size();
		if (sequence.empty())
			return false;

		int root = sequence.back();

		// �ڶ������������������ڵ��ֵС�ڸ��ڵ��ֵ
		int i = 0;
		for (; i < len - 1; ++i)
		{
			if (sequence[i] > root)
				break;
		}
		// �ڶ������������������ڵ��ֵ���ڸ��ڵ��ֵ
		int j = i;
		for (; j < len - 1; ++j)
		{
			if (sequence[j] < root)
				return false;
		}
		// �ж��������ǲ��Ƕ���������
		bool left = true;
		if (i > 0)
			left = VerifySquenceOfBST(vector<int>(sequence.begin(), sequence.begin() + i));
		// �ж��������ǲ��Ƕ���������
		bool right = true;
		if (i < len - 1)
			right = VerifySquenceOfBST(vector<int>(sequence.begin() + i, sequence.end() - 1));

		return left && right;
	}
};

void test1()
{
	int sequence[] = { 5,7,6,9,11,10,8 };
	cout << boolalpha << VerifySequenceOfBST(sequence, sizeof(sequence) / sizeof(int)) << endl;
}

void test2()
{
	cout << boolalpha << VerifySequenceOfBST(nullptr, 0) << endl;
}

void test3()
{
	int sequence[] = { 6, 3, 8, 5 };
	cout << boolalpha << VerifySequenceOfBST(sequence, sizeof(sequence) / sizeof(int)) << endl;
}

void test4()
{
	int sequence[] = { 6 };
	cout << boolalpha << VerifySequenceOfBST(sequence, sizeof(sequence) / sizeof(int)) << endl;
}

void driver()
{
	test1();
	test2();
	test3();
	test4();
}