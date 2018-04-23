#pragma once

/*

二叉树的后序遍历，递归方式，非递归方式

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
	vector<int> postorderTraversal(TreeNode* root)
	{
		vector<int> result;
		postorder(root, result);
		return result;
	}

	void postorder(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr)
			return;
		if (root->left != nullptr)
			postorder(root->left, result);
		if (root->right != nullptr)
			postorder(root->right, result);
		result.push_back(root->val);
	}
};

// ==============非递归=================

// 第一种思路：
// 对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，
// 直到搜索到没有左孩子的结点，此时该结点出现在栈顶，但是此时不能将其出栈并访问，
// 因此其右孩子还为被访问。所以接下来按照相同的规则对其右子树进行相同的处理，
// 当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问。这样就保证了正确的访问顺序。
// 可以看出，在这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。
// 因此需要多设置一个变量标识该结点是否是第一次出现在栈顶。

struct TreeNode_v2 {
	int val;
	TreeNode_v2 *left;
	TreeNode_v2 *right;
	int stack_top_times;
	TreeNode_v2(int x) : val(x), left(nullptr), right(nullptr), stack_top_times(0) { }
};

class SolutionIterative {
public:
	vector<int> postorderTraversal(TreeNode_v2* root)
	{
		vector<int> result;
		if (root == nullptr)
			return result;
		stack<TreeNode_v2*> node_stack;
		TreeNode_v2* node = root;
		while (node != nullptr || !node_stack.empty())
		{
			// 至最左节点
			while (node != nullptr)
			{
				node->stack_top_times = 1;	// 节点被首次访问
				node_stack.push(node);
				node = node->left;
			}

			node = node_stack.top();
			node_stack.pop();
			// 若在栈顶出现1次，则此时增致2次，重新压入栈中，并且转向右子树
			if (node->stack_top_times == 1)
			{
				node->stack_top_times = 2;
				node_stack.push(node);
				node = node->right;
			}
			// 若已经在栈顶出现2次，说明左右子树都被访问完毕，则访问之，并置 node = nullptr，从而继续去处理新的栈顶元素
			else if (node->stack_top_times == 2)
			{
				result.push_back(node->val);
				node = nullptr;
			}
		}
		return result;
	}
};

// 第二种思路：
// 要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
// 如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，
// 但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两种情况，
// 则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，
// 左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。

// 具体实现时，用 curr 记录当前访问节点，用 pre 记录前一个被访问的节点

class SolutionIterative_v2 {
public:
	vector<int> postorderTraversal(TreeNode* root)
	{
		vector<int> result;
		if (root == nullptr)
			return result;
		stack<TreeNode*> node_stack;
		TreeNode* curr;
		TreeNode* pre = nullptr;
		
		node_stack.push(root);
		while (!node_stack.empty())
		{
			curr = node_stack.top();
			// 若满足如下三个条件之一便可以访问当前节点
			//  1--其左右孩子均为nullptr
			//  2--其左孩子刚被输出，而其右孩子为nullptr
			//  3--其右孩子刚被输出
			if ((curr->left == nullptr && curr->right == nullptr)
				|| (pre == curr->left && curr->right == nullptr)
				|| (pre == curr->right))
			{
				result.push_back(curr->val);
				node_stack.pop();
				pre = curr;
			}
			else
			{
				// 由于栈是先进后出，因此先入栈右孩子, 再入栈左孩子可以保证递归返回时先遍历左孩子
				if (curr->right != nullptr)
					node_stack.push(curr->right);
				if (curr->left != nullptr)
					node_stack.push(curr->left);
			}
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
	vector<int> result_solu_recur = solu_recur.postorderTraversal(&a);
	for (auto item : result_solu_recur)
		cout << item << " ";
	cout << endl;

	SolutionIterative_v2 solu_iter_v2;
	vector<int> result_solu_iter_v2 = solu_iter_v2.postorderTraversal(&a);
	for (auto item : result_solu_iter_v2)
		cout << item << " ";
	cout << endl;

	TreeNode_v2 a_v2(2);
	TreeNode_v2 b_v2(3);
	TreeNode_v2 c_v2(5);
	TreeNode_v2 d_v2(6);
	TreeNode_v2 e_v2(4);
	TreeNode_v2 f_v2(7);
	a_v2.left = &b_v2;
	a_v2.right = &c_v2;
	b_v2.left = &d_v2;
	b_v2.right = &e_v2;
	e_v2.left = &f_v2;

	SolutionIterative solu_iter;
	vector<int> result_solu_iter = solu_iter.postorderTraversal(&a_v2);
	for (auto item : result_solu_iter)
		cout << item << " ";
	cout << endl;
}