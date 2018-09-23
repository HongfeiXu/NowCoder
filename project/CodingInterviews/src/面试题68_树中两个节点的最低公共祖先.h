#pragma once

/*

面试题 68：树中两个节点的最低公共祖先

这棵树不是二叉搜索树，甚至不是二叉树。

思路：

1. 确定从根到两个节点的两条路径
2. 找出这两条路径最后的公共节点，即为最低公共祖先

*/

#include <vector>
#include <iostream>

using namespace std;

struct TreeNode
{
	char data;
	vector<TreeNode*> m_vChildren;
};

bool GetNodePath(TreeNode* pRoot, TreeNode* pNode, vector<TreeNode*>& path)
{
	path.push_back(pRoot);

	if (pRoot == pNode)
		return true;

	bool found = false;

	for (unsigned i = 0; i < pRoot->m_vChildren.size(); ++i)
	{
		if (GetNodePath(pRoot->m_vChildren[i], pNode, path))
		{
			found = true;
			break;
		}
	}

	// 若通过 pRoot 无法到达目标节点，则从 path 中弹出 pRoot
	if (!found)
		path.pop_back();

	return found;
}

TreeNode* GetLastCommonNode(const vector<TreeNode*>& path1, const vector<TreeNode*>& path2)
{
	vector<TreeNode*>::const_iterator it1 = path1.begin();
	vector<TreeNode*>::const_iterator it2 = path2.begin();

	TreeNode* pLast = nullptr;
	while (it1 != path1.end() && it2 != path2.end() && *it1 == *it2)
	{
		pLast = *it1;
		++it1;
		++it2;
	}

	return pLast;
}

TreeNode* GetLastCommonParent(TreeNode* pRoot, TreeNode* pNode1, TreeNode* pNode2)
{
	if (pRoot == nullptr || pNode1 == nullptr || pNode2 == nullptr)
		return nullptr;

	vector<TreeNode*> path1;
	GetNodePath(pRoot, pNode1, path1);

	vector<TreeNode*> path2;
	GetNodePath(pRoot, pNode2, path2);

	return GetLastCommonNode(path1, path2);
}

void test0()
{
	TreeNode* A = new TreeNode;
	A->data = 'A';
	TreeNode* B = new TreeNode;
	B->data = 'B';
	TreeNode* C = new TreeNode;
	C->data = 'C';
	TreeNode* D = new TreeNode;
	D->data = 'D';
	TreeNode* E = new TreeNode;
	E->data = 'E';
	TreeNode* F = new TreeNode;
	F->data = 'F';
	TreeNode* G = new TreeNode;
	G->data = 'G';
	TreeNode* H = new TreeNode;
	H->data = 'H';
	TreeNode* I = new TreeNode;
	I->data = 'I';
	TreeNode* J = new TreeNode;
	J->data = 'J';

	A->m_vChildren.push_back(B);
	A->m_vChildren.push_back(C);
	B->m_vChildren.push_back(D);
	B->m_vChildren.push_back(E);
	D->m_vChildren.push_back(F);
	D->m_vChildren.push_back(G);
	E->m_vChildren.push_back(H);
	E->m_vChildren.push_back(I);
	E->m_vChildren.push_back(J);

	cout << GetLastCommonParent(A, F, H)->data << endl;
}

void driver()
{
	test0();
}

