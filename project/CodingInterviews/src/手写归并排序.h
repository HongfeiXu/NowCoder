#pragma once

/*

归并排序

Refer: https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F

归并操作（merge），也叫归并算法，指的是将两个已经排序的序列合并成一个序列的操作。归并排序算法依赖归并操作。

递归法（Top-down）

申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
设定两个指针，最初位置分别为两个已经排序序列的起始位置
比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
重复步骤3直到某一指针到达序列尾
将另一序列剩下的所有元素直接复制到合并序列尾

迭代法（Bottom-up）

原理如下（假设序列共有 n 个元素）：

将序列每相邻两个数字进行归并操作，形成 n/2 个序列，排序后每个序列包含两/一个元素
若此时序列数不是1个则将上述序列再次归并，形成 n/4 个序列，每个序列包含四/三个元素
重复步骤2，直到所有元素排序完毕，即序列数为1

*/

#include <iostream>
#include <algorithm>

using namespace std;

///////////////////////////////////////////////////////////
// 递归版

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

	// 合并两个有序数组
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
// 迭代版

template<typename T>
void merge_sort_iterative(T arr[], const int len)
{
	T* a = arr;
	T* b = new T[len];
	// seg 为每一个有序子段的长度，从1增加到len
	for (int seg = 1; seg < len; seg += seg)
	{
		for (int start = 0; start < len; start += seg + seg)
		{
			int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
			// 左 arr[low...mid-1]，因为 mid 可能等于 len
			int start0 = low, end0 = mid;
			// 右 arr[mid...high-1]，因为 high 可能等于 len
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
		swap(a, b);	// 交换 a,b 指向的数组
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

