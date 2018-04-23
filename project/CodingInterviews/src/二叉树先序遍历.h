#pragma once


/*

二叉树的前序遍历，递归方式，非递归方式

Ref: https://blog.csdn.net/gatieme/article/details/51163010

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

// ==============递归=================

class SolutionRecursive {
public:
	vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> result;
		preorder(root, result);
		return result;
	}

	void preorder(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr)
			return;
		result.push_back(root->val);
		if(root->left != nullptr)
			preorder(root->left, result);
		if(root->right != nullptr)
			preorder(root->right, result);
	}
};

// ==============非递归=================

class SolutionIterative {
public:
	vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> result;

		if (root == nullptr)
			return result;

		stack<TreeNode*> node_stack;
		TreeNode* node = root;		// 指向接下来要被访问的节点
		while (node != nullptr || !node_stack.empty())
		{
			// 如果想要访问的节点不为空，
			// 访问当前节点，若当前节点有左子树，则继续访问左孩子，直到最左节点
			while (node != nullptr)
			{
				result.push_back(node->val);
				node_stack.push(node);
				node = node->left;
			}

			// 出栈栈顶元素，转向右子树，更新node指向接下来要被访问的节点（可能为空）
			node = node_stack.top();
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
	vector<int> result_solu_recur = solu_recur.preorderTraversal(&a);
	for (auto item : result_solu_recur)
		cout << item << " ";
	cout << endl;

	SolutionIterative solu_iter;
	vector<int> result_solu_iter = solu_iter.preorderTraversal(&a);
	for (auto item : result_solu_recur)
		cout << item << " ";
	cout << endl;
}

