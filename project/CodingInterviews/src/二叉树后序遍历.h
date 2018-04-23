#pragma once

/*

�������ĺ���������ݹ鷽ʽ���ǵݹ鷽ʽ

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

// ==============�ݹ�=================

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

// ==============�ǵݹ�=================

// ��һ��˼·��
// ������һ���P��������ջ��Ȼ������������һֱ����������
// ֱ��������û�����ӵĽ�㣬��ʱ�ý�������ջ�������Ǵ�ʱ���ܽ����ջ�����ʣ�
// ������Һ��ӻ�Ϊ�����ʡ����Խ�����������ͬ�Ĺ������������������ͬ�Ĵ���
// �����������Һ���ʱ���ý���ֳ�����ջ������ʱ���Խ����ջ�����ʡ������ͱ�֤����ȷ�ķ���˳��
// ���Կ���������������У�ÿ����㶼���γ�����ջ����ֻ���ڵڶ��γ�����ջ��ʱ�����ܷ�������
// �����Ҫ������һ��������ʶ�ý���Ƿ��ǵ�һ�γ�����ջ����

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
			// ������ڵ�
			while (node != nullptr)
			{
				node->stack_top_times = 1;	// �ڵ㱻�״η���
				node_stack.push(node);
				node = node->left;
			}

			node = node_stack.top();
			node_stack.pop();
			// ����ջ������1�Σ����ʱ����2�Σ�����ѹ��ջ�У�����ת��������
			if (node->stack_top_times == 1)
			{
				node->stack_top_times = 2;
				node_stack.push(node);
				node = node->right;
			}
			// ���Ѿ���ջ������2�Σ�˵��������������������ϣ������֮������ node = nullptr���Ӷ�����ȥ�����µ�ջ��Ԫ��
			else if (node->stack_top_times == 2)
			{
				result.push_back(node->val);
				node = nullptr;
			}
		}
		return result;
	}
};

// �ڶ���˼·��
// Ҫ��֤����������Ӻ��Һ��ӷ���֮����ܷ��ʣ���˶�����һ���P���Ƚ�����ջ��
// ���P���������Ӻ��Һ��ӣ������ֱ�ӷ�����������P�������ӻ����Һ��ӣ�
// ���������Ӻ��Һ��Ӷ��ѱ����ʹ��ˣ���ͬ������ֱ�ӷ��ʸý�㡣�����������������
// ��P���Һ��Ӻ�����������ջ�������ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ��
// �������Һ���ǰ�汻���ʣ����Ӻ��Һ��Ӷ��ڸ����ǰ�汻���ʡ�

// ����ʵ��ʱ���� curr ��¼��ǰ���ʽڵ㣬�� pre ��¼ǰһ�������ʵĽڵ�

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
			// ������������������֮һ����Է��ʵ�ǰ�ڵ�
			//  1--�����Һ��Ӿ�Ϊnullptr
			//  2--�����Ӹձ�����������Һ���Ϊnullptr
			//  3--���Һ��Ӹձ����
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
				// ����ջ���Ƚ�������������ջ�Һ���, ����ջ���ӿ��Ա�֤�ݹ鷵��ʱ�ȱ�������
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