#pragma once

/*

������05��չ

��������������� A1 �� A2���ڴ��� A1 ��ĩβ���㹻��Ŀ���ռ� A2��
������һ���������� A2 �е��������ֲ��� A1 �У��������е�����������ġ�

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

	// A2 �����ֻ�δ��ȫ���� A1 �У�A1 �������Ѿ��Ƶ�����λ��
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

