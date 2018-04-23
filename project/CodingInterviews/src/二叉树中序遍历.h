#pragma once

/*

二叉树的中序遍历，递归方式，非递归方式

Ref: https://blog.csdn.net/gatieme/article/details/51163010

注：非递归方式的思路和二叉树先序遍历很类似，都用到栈，以及一个指针指向将要被访问到的节点（用来完成转向右子树访问）
只是先序遍历是是在入栈时访问节点，中序遍历是在出栈时访问节点。

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

// ==============非递归=================

class SolutionIterative {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		if (root == nullptr)
			return result;

		stack<TreeNode*> node_stack;
		TreeNode* node = root;	// 指向接下来要被访问的节点

		// 至最左节点
		while (node != nullptr || !node_stack.empty())
		{
			while (node != nullptr)
			{
				node_stack.push(node);
				node = node->left;
			}

			// 访问栈顶节点，出栈栈顶元素，转向右子树，更新node指向接下来要被访问的节点（可能为空）
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