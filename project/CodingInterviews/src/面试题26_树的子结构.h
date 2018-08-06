#pragma once

/*

面试题26：树的子结构

题目：输入两棵二叉树 A 和 B，判断 B 是不是 A 的子结构。（约定：若pRoot2为空，则一定是pRoot1的子结构）

*/

#include <iostream>

using namespace std;

struct BinaryTreeNode {
	double m_dbValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

bool Equal(double num1, double num2)
{
	return (num1 - num2 > -1e-7) && (num1 - num2 < 1e-7);
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot2 == nullptr)
		return true;
	if (pRoot1 == nullptr)
		return false;
	
	if (!Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
		return false;
	return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	bool result = false;
	if (pRoot2 == nullptr)
		result = true;
	else if (pRoot1 != nullptr)
	{
		if (Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
		{
			result = DoesTree1HaveTree2(pRoot1, pRoot2);
		}
		if (!result)
		{
			result = HasSubtree(pRoot1->m_pLeft, pRoot2);
		}
		if (!result)
		{
			result = HasSubtree(pRoot1->m_pRight, pRoot2);
		}
	}
	return result;
}

// 测试：1(2,(3,))   2(3,)
void test1()
{
	BinaryTreeNode* A = new BinaryTreeNode();
	A->m_dbValue = 1;
	BinaryTreeNode* B = new BinaryTreeNode();
	B->m_dbValue = 2;
	BinaryTreeNode* C = new BinaryTreeNode();
	C->m_dbValue = 3;
	A->m_pLeft = B;
	A->m_pRight = nullptr;
	B->m_pLeft = C;
	B->m_pRight = nullptr;
	C->m_pLeft = nullptr;
	C->m_pRight = nullptr;
	
	BinaryTreeNode* D = new BinaryTreeNode();
	D->m_dbValue = 2;
	BinaryTreeNode* E = new BinaryTreeNode();
	E->m_dbValue = 3;
	D->m_pLeft = E;
	D->m_pRight = nullptr;
	E->m_pLeft = nullptr;
	E->m_pRight = nullptr;

	cout << boolalpha << HasSubtree(A, D) << endl;
}

void test2()
{
	BinaryTreeNode* A = nullptr;
	BinaryTreeNode* B = nullptr;

	cout << boolalpha << HasSubtree(A, B) << endl;
}

void test3()
{
	BinaryTreeNode* A = new BinaryTreeNode();
	A->m_dbValue = 1;
	BinaryTreeNode* B = new BinaryTreeNode();
	B->m_dbValue = 2;
	BinaryTreeNode* C = new BinaryTreeNode();
	C->m_dbValue = 3;
	BinaryTreeNode* D = new BinaryTreeNode();
	D->m_dbValue = 4;
	BinaryTreeNode* E = new BinaryTreeNode();
	E->m_dbValue = 5;
	A->m_pLeft = B;
	A->m_pRight = C;
	B->m_pLeft = D;
	B->m_pRight = E;
	C->m_pLeft = nullptr;
	C->m_pRight = nullptr;

	BinaryTreeNode* F = new BinaryTreeNode();
	F->m_dbValue = 2;
	BinaryTreeNode* G = new BinaryTreeNode();
	G->m_dbValue = 4;
	F->m_pRight = nullptr;
	G->m_pLeft = nullptr;
	G->m_pRight = nullptr;

	cout << boolalpha << HasSubtree(A, F) << endl;
}

void driver()
{
	test1();
	test2();
	test3();
}