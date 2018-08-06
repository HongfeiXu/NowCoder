#pragma once

/*

面试题33：二叉搜索树的后序遍历序列

题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。
如果是，则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。

思路：后序遍历序列的最后一个节点将序列分为前后两个部分：第一部分是左子树节点的值，都比根节点小；第二部分是右子树节点的值，都比根节点大。（条件）
确定满足之后，在去递归判断每个子树是否满足该条件。

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

// 答题版
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		int len = sequence.size();
		if (sequence.empty())
			return false;

		int root = sequence.back();

		// 在二叉搜索树中左子树节点的值小于根节点的值
		int i = 0;
		for (; i < len - 1; ++i)
		{
			if (sequence[i] > root)
				break;
		}
		// 在二叉搜索树中右子树节点的值大于根节点的值
		int j = i;
		for (; j < len - 1; ++j)
		{
			if (sequence[j] < root)
				return false;
		}
		// 判断左子树是不是二叉搜索树
		bool left = true;
		if (i > 0)
			left = VerifySquenceOfBST(vector<int>(sequence.begin(), sequence.begin() + i));
		// 判断右子树是不是二叉搜索树
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