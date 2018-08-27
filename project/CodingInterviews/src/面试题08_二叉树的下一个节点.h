#pragma once

/*

������8������������һ���ڵ�

��Ŀ������һ�ö����������е�һ���ڵ㣬����ҳ�����������е���һ���ڵ㣿���еĽڵ�����������ֱ�ָ�������ӽڵ��ָ�룬����һ��ָ�򸸽ڵ��ָ�롣

˼·��

���ڵ�N�����������������������һ���ڵ�����������������ڵ�
���ڵ�Nû������������N���丸�ڵ�����ӣ����������������һ���ڵ����丸�ڵ�
���ڵ�Nû������������N���丸�ڵ���Һ��ӣ������ŵ�ǰ���ڵ�P���ϳ�����������P'���丸�ڵ�P''������������P''�������������һ���ڵ㣬����N��������������һ���ڵ㣬��������һ���ڵ㡣

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

