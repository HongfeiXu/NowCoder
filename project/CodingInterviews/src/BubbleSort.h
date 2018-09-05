#pragma once

#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int>& nums)
{
	int size = nums.size();
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - 1 - i; ++j)
		{
			if (nums[j] > nums[j + 1])
				swap(nums[j], nums[j + 1]);
		}
	}
}

void test()
{
	vector<int> nums{ 64, 34, 25, 12, 22, 11, 90 };
	bubbleSort(nums);
	for (int i = 0; i < nums.size(); ++i)
	{
		cout << nums[i] << " ";
	}
	cout << endl;
}

void driver()
{
	test();
}