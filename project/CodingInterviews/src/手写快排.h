#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& nums, int left, int right, int pivot_index)
{
	int pivot_value = nums[pivot_index];
	swap(nums[pivot_index], nums[right]);
	int store_index = left;
	for (int i = left; i <= right - 1; ++i)
	{
		// ������С�� pivot_value ��Ԫ�ؽ�����ǰ��
		if (nums[i] < pivot_value)
		{
			swap(nums[i], nums[store_index]);
			++store_index;
		}
	}
	swap(nums[right], nums[store_index]);
	return store_index;
}

void quickSort(vector<int>& nums, int left, int right)
{
	if (left < right)
	{
		int pivot_index = right;	// ѡȡ���һ��Ԫ����Ϊ�ָ��
		int pivot_new_index = partition(nums, left, right, pivot_index);
		quickSort(nums, left, pivot_new_index - 1);
		quickSort(nums, pivot_new_index + 1, right);
	}
}

void driver()
{
	vector<int> vec { 3,1,2,39,20,1,-3 };
	quickSort(vec, 0, vec.size() - 1);
	for (auto i : vec)
		cout << i << " ";
	cout << endl;
}
