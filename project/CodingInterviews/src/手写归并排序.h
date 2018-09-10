#pragma once

/*

�鲢����

Refer: https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F

�鲢������merge����Ҳ�й鲢�㷨��ָ���ǽ������Ѿ���������кϲ���һ�����еĲ������鲢�����㷨�����鲢������

�ݹ鷨��Top-down��

����ռ䣬ʹ���СΪ�����Ѿ���������֮�ͣ��ÿռ�������źϲ��������
�趨����ָ�룬���λ�÷ֱ�Ϊ�����Ѿ��������е���ʼλ��
�Ƚ�����ָ����ָ���Ԫ�أ�ѡ�����С��Ԫ�ط��뵽�ϲ��ռ䣬���ƶ�ָ�뵽��һλ��
�ظ�����3ֱ��ĳһָ�뵽������β
����һ����ʣ�µ�����Ԫ��ֱ�Ӹ��Ƶ��ϲ�����β

��������Bottom-up��

ԭ�����£��������й��� n ��Ԫ�أ���

������ÿ�����������ֽ��й鲢�������γ� n/2 �����У������ÿ�����а�����/һ��Ԫ��
����ʱ����������1�������������ٴι鲢���γ� n/4 �����У�ÿ�����а�����/����Ԫ��
�ظ�����2��ֱ������Ԫ��������ϣ���������Ϊ1

*/

#include <iostream>
#include <algorithm>

using namespace std;

///////////////////////////////////////////////////////////
// �ݹ��

template<typename T>
void merge_sort_recursive(T arr[], T reg[], int start, int end)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	int start0 = start, end0 = mid;
	int start1 = mid + 1, end1 = end;
	merge_sort_recursive(arr, reg, start0, end0);
	merge_sort_recursive(arr, reg, start1, end1);

	// �ϲ�������������
	int i = start;
	while (start0 <= end0 && start1 <= end1)
	{
		if (arr[start0] < arr[start1])
			reg[i++] = arr[start0++];
		else
			reg[i++] = arr[start1++];
	}
	while (start0 <= end0)
		reg[i++] = arr[start0++];
	while (start1 <= end1)
		reg[i++] = arr[start1++];
	for (int j = start; j <= end; ++j)
	{
		arr[j] = reg[j];
	}
}

template<typename T>
void merge_sort(T arr[], const int len)
{
	T* reg = new T[len];
	merge_sort_recursive(arr, reg, 0, len - 1);
	delete reg;
}

///////////////////////////////////////////////////////////
// ������

template<typename T>
void merge_sort_iterative(T arr[], const int len)
{
	T* a = arr;
	T* b = new T[len];
	// seg Ϊÿһ�������Ӷεĳ��ȣ���1���ӵ�len
	for (int seg = 1; seg < len; seg += seg)
	{
		for (int start = 0; start < len; start += seg + seg)
		{
			int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
			// �� arr[low...mid-1]����Ϊ mid ���ܵ��� len
			int start0 = low, end0 = mid;
			// �� arr[mid...high-1]����Ϊ high ���ܵ��� len
			int start1 = mid, end1 = high;
			int k = low;
			while (start0 < end0 && start1 < end1)
			{
				if (a[start0] < a[start1])
					b[k++] = a[start0++];
				else
					b[k++] = a[start1++];
			}
			while (start0 < end0)
				b[k++] = a[start0++];
			while (start1 < end1)
				b[k++] = a[start1++];
		}
		swap(a, b);	// ���� a,b ָ�������
	}

	if (arr == a)
	{
		delete[] b;
	}
	else
	{
		for (int i = 0; i < len; ++i)
		{
			b[i] = a[i];
		}
		delete[] a;
	}
}

void test()
{
	int arr[] = { 3,1,2,6,8,4,9 };
	int len = sizeof(arr) / sizeof(int);
	merge_sort_iterative(arr, len);
	for (int i = 0; i < len; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void driver()
{
	test();
}

