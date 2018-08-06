#pragma once

/*

面试题34：二叉树中和为某一值的路径

题目：输入一个二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。
从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

思路：Backtracking

*/

#include "BinaryTree.h"
#include <iostream>
#include <vector>

using namespace std;


void DFS(BinaryTreeNode* root, int& expectNumber, int currSum, vector<int>& path, vector<vector<int>>& result)
{
	path.push_back(root->m_nValue);
	currSum += root->m_nValue;
	// 访问到叶子节点
	if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
	{
		// 看当前路径的和是否满足题目要求
		if (currSum == expectNumber)
			result.push_back(path);
	}
	// 如果不是叶节点，则遍历它的子节点
	if (root->m_pLeft != nullptr)
	{
		DFS(root->m_pLeft, expectNumber, currSum, path, result);
	}
	if (root->m_pRight != nullptr)
	{
		DFS(root->m_pRight, expectNumber, currSum, path, result);
	}
	// 返回到父节点前，在路径上删除当前节点
	path.pop_back();
}

vector<vector<int>> FindPath(BinaryTreeNode* root, int expectNumber)
{
	vector<vector<int>> result;
	if (root == nullptr)
		return result;

	vector<BinaryTreeNode*> currStack;
	int currSum = 0;

	vector<int> path;

	DFS(root, expectNumber, currSum, path, result);
	return result;
}

void test1()
{
	BinaryTreeNode* A = new BinaryTreeNode();
	BinaryTreeNode* B = new BinaryTreeNode();
	BinaryTreeNode* C = new BinaryTreeNode();
	BinaryTreeNode* D = new BinaryTreeNode();
	BinaryTreeNode* E = new BinaryTreeNode();
	BinaryTreeNode* F = new BinaryTreeNode();
	BinaryTreeNode* G = new BinaryTreeNode();

	A->m_nValue = 1;
	B->m_nValue = 2;
	C->m_nValue = 4;
	D->m_nValue = 3;
	E->m_nValue = 6;
	F->m_nValue = 1;
	G->m_nValue = 7;
	A->m_pLeft = B;
	A->m_pRight = C;
	B->m_pLeft = D;
	B->m_pRight = E;
	C->m_pLeft = F;
	C->m_pRight = G;
	D->m_pLeft = nullptr;
	D->m_pRight = nullptr;
	E->m_pLeft = nullptr;
	E->m_pRight = nullptr;
	F->m_pLeft = nullptr;
	F->m_pRight = nullptr;
	G->m_pLeft = nullptr;
	G->m_pRight = nullptr;

	vector<vector<int>> result = FindPath(A, 6);
	for (int i = 0; i < result.size(); ++i)
	{
		for (int j = 0; j < result[i].size(); ++j)
			cout << result[i][j] << " ";
		cout << endl;
	}
}

void driver()
{
	test1();
}
