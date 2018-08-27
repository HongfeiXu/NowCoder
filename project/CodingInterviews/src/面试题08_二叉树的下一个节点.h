#pragma once

/*

面试题8：二叉树的下一个节点

题目：给定一棵二叉树和其中的一个节点，如何找出中序遍历序列的下一个节点？树中的节点除了有两个分别指向左、右子节点的指针，还有一个指向父节点的指针。

思路：

若节点N有右子树，则中序遍历的下一个节点是其右子树的最左节点
若节点N没有右子树，且N是其父节点的左孩子，则其中序遍历的下一个节点是其父节点
若节点N没有右子树，且N是其父节点的右孩子，则沿着当前父节点P向上出发，若存在P'是其父节点P''的左子树，则P''是中序遍历的下一个节点，否则N是中序遍历的最后一个节点，不存在下一个节点。

*/

#include <iostream>

using namespace std;

struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(nullptr), right(nullptr), next(nullptr) {
	}
};

class Solution {
public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == nullptr)
			return nullptr;

		TreeLinkNode* next = nullptr;
		if (pNode->right != nullptr)
		{
			next = pNode->right;
			while (next->left != nullptr)
				next = next->left;
		}
		else
		{
			TreeLinkNode* pa = pNode->next;
			if (pa == nullptr)
				next = nullptr;
			else if (pa->left == pNode)
				next = pa;
			else
			{
				TreeLinkNode* papa = pa->next;
				while (papa != nullptr && papa->right == pa)
				{
					pa = papa;
					papa = pa->next;
				}
				if (papa == nullptr)
					next = nullptr;
				else
					next = papa;
			}
		}
		return next;
	}
};

