#pragma once

/*

������34���������к�Ϊĳһֵ��·��

��Ŀ������һ����������һ����������ӡ���������нڵ�ֵ�ĺ�Ϊ��������������·����
�����ĸ��ڵ㿪ʼ����һֱ��Ҷ�ڵ��������Ľڵ��γ�һ��·����

˼·��Backtracking

*/

#include "BinaryTree.h"
#include <iostream>
#include <vector>

using namespace std;


void DFS(BinaryTreeNode* root, int& expectNumber, int currSum, vector<int>& path, vector<vector<int>>& result)
{
	path.push_back(root->m_nValue);
	currSum += root->m_nValue;
	// ���ʵ�Ҷ�ӽڵ�
	if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
	{
		// ����ǰ·���ĺ��Ƿ�������ĿҪ��
		if (currSum == expectNumber)
			result.push_back(path);
	}
	// �������Ҷ�ڵ㣬����������ӽڵ�
	if (root->m_pLeft != nullptr)
	{
		DFS(root->m_pLeft, expectNumber, currSum, path, result);
	}
	if (root->m_pRight != nullptr)
	{
		DFS(root->m_pRight, expectNumber, currSum, path, result);
	}
	// ���ص����ڵ�ǰ����·����ɾ����ǰ�ڵ�
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
