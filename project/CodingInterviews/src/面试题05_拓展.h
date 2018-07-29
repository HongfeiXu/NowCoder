#pragma once

/*

面试题05拓展

有两个排序的数组 A1 和 A2，内存在 A1 的末尾有足够多的空余空间 A2。
请事先一个函数，把 A2 中的所有数字插入 A1 中，并且所有的数字是排序的。

*/

#include <iostream>

using namespace std;


void InsertArray(int A1[], int A2[], int lenOfA1, int lenOfA2, int capacityOfA1)
{
	if (capacityOfA1 < lenOfA1 + lenOfA2)
		return;

	int l1 = lenOfA1 - 1;
	int l2 = lenOfA2 - 1;
	int e = lenOfA1 + lenOfA2 - 1;

	while (l1 >= 0 && l2 >= 0)
	{
		if (A1[l1] >= A2[l2])
			A1[e--] = A1[l1--];
		else
			A1[e--] = A2[l2--];
	}

	// A2 中数字还未完全移入 A1 中，A1 中数字已经移到最终位置
	while (l1 == -1 && l2 >= 0)
	{
		A1[e--] = A2[l2--];
	}
}


void test1()
{
	int A1[6] = { 1,4,7 };
	int A2[] = { 3,3,5 };

	InsertArray(A1, A2, 3, 3, 6);

	for (int i = 0; i < 6; ++i)
	{
		cout << A1[i] << " ";
	}
	cout << endl;
}

void test2()
{
	int A1[3];
	int A2[] = { 3,3,5 };

	InsertArray(A1, A2, 0, 3, 3);
	for (int i = 0; i < 3; ++i)
	{
		cout << A1[i] << " ";
	}
	cout << endl;
}

void test3()
{
	int A1[3];
	int A2[] = { 4,5,6,7 };
	for (int i = 0; i < 3; ++i)
	{
		cout << A1[i] << " ";
	}
	cout << endl;
}

void driver()
{
	test1();
	test2();
	test3();
}

