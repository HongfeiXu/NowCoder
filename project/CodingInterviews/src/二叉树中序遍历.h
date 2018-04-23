#pragma once

/*

������������������ݹ鷽ʽ���ǵݹ鷽ʽ

Ref: https://blog.csdn.net/gatieme/article/details/51163010

ע���ǵݹ鷽ʽ��˼·�Ͷ�����������������ƣ����õ�ջ���Լ�һ��ָ��ָ��Ҫ�����ʵ��Ľڵ㣨�������ת�����������ʣ�
ֻ�����������������ջʱ���ʽڵ㣬����������ڳ�ջʱ���ʽڵ㡣

*/

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

// ==============�ݹ�=================

class SolutionRecursive {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		inorder(root, result);
		return result;
	}

	void inorder(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr)
			return;
		if (root->left != nullptr)
			inorder(root->left, result);
		result.push_back(root->val);
		if (root->right != nullptr)
			inorder(root->right, result);
	}
};

// ==============�ǵݹ�=================

class SolutionIterative {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		if (root == nullptr)
			return result;

		stack<TreeNode*> node_stack;
		TreeNode* node = root;	// ָ�������Ҫ�����ʵĽڵ�

		// ������ڵ�
		while (node != nullptr || !node_stack.empty())
		{
			while (node != nullptr)
			{
				node_stack.push(node);
				node = node->left;
			}

			// ����ջ���ڵ㣬��ջջ��Ԫ�أ�ת��������������nodeָ�������Ҫ�����ʵĽڵ㣨����Ϊ�գ�
			node = node_stack.top();
			result.push_back(node->val);
			node_stack.pop();
			node = node->right;
		}
		return result;
	}
};


void driver()
{
	TreeNode a(2);
	TreeNode b(3);
	TreeNode c(5);
	TreeNode d(6);
	TreeNode e(4);
	TreeNode f(7);

	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;
	e.left = &f;

	SolutionRecursive solu_recur;
	vector<int> result_solu_recur = solu_recur.inorderTraversal(&a);
	for (auto item : result_solu_recur)
		cout << item << " ";
	cout << endl;

	SolutionIterative solu_iter;
	vector<int> result_solu_iter = solu_iter.inorderTraversal(&a);
	for (auto item : result_solu_recur)
		cout << item << " ";
	cout << endl;
}