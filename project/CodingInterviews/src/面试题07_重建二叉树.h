#pragma once

/*

面试题7：重建二叉树

题目：输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序和中序结构中都不含重复的数字。

*/

#include <iostream>
#include <exception>
#include <cstdio>

#include "BinaryTree.h"

using namespace std;

// 对于前序遍历序列和中序遍历序列不匹配的情况不能做出正确处理
BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
	if (length == 0)
		return nullptr;

	BinaryTreeNode* curr = new BinaryTreeNode();
	curr->m_nValue = preorder[0];
	curr->m_pLeft = nullptr;
	curr->m_pRight = nullptr;

	if (length == 1)
	{
		if (preorder[0] == inorder[0])
			return curr;
		else
			throw exception("Invalid input.");
	}

	// 记录根节点在 inorder 中的位置
	int pos = 0;
	for (; pos < length; ++pos)
	{
		if (inorder[pos] == preorder[0])
			break;
	}
	if (pos == length)
		throw std::exception("Invalid input.");
	int leftSubtreeLength = pos;
	int rightSubtreeLength = length - pos - 1;

	curr->m_pLeft = Construct(preorder + 1, inorder, leftSubtreeLength);
	curr->m_pRight = Construct(preorder + leftSubtreeLength + 1, inorder + leftSubtreeLength + 1, rightSubtreeLength);
	return curr;
}

// ====================测试代码====================
void Test(char* testName, int* preorder, int* inorder, int length)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The preorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", preorder[i]);
	printf("\n");

	printf("The inorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", inorder[i]);
	printf("\n");

	try
	{
		BinaryTreeNode* root = Construct(preorder, inorder, length);
		PrintTree(root);

		DestroyTree(root);
	}
	catch (std::exception& exception)
	{
		printf(exception.what());
		printf("\n");
	}
}

// 普通二叉树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
	const int length = 8;
	int preorder[length] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inorder[length] = { 4, 7, 2, 1, 5, 3, 8, 6 };

	Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5
void Test2()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 5, 4, 3, 2, 1 };

	Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \ 
//              2   
//               \ 
//                3 
//                 \
//                  4
//                   \
//                    5
void Test3()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 1, 2, 3, 4, 5 };

	Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4()
{
	const int length = 1;
	int preorder[length] = { 1 };
	int inorder[length] = { 1 };

	Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3  
//         / \     / \
//        4   5   6   7
void Test5()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 5, 1, 6, 3, 7 };

	Test("Test5", preorder, inorder, length);
}

// 输入空指针
void Test6()
{
	Test("Test6", nullptr, nullptr, 0);
}

// 输入的两个序列不匹配
void Test7()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 8, 1, 6, 3, 7 };

	Test("Test7: for unmatched input", preorder, inorder, length);
}

void driver()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
}