#pragma once

#include <vector>
#include <iostream>

using namespace std;

// 在有序数组中寻找元素x，若存在则返回下表，否则返回-1
int binarySearch(const vector<int>& nums, int x)
{
	if (nums.empty())
		return -1;
	int l = 0;
	int r = nums.size() - 1;
	int mid = 0;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (nums[mid] == x)
			return mid;
		if (nums[mid] < x)
			++l;
		else
			--r;
	}
	return -1;
}

void test0()
{
	vector<int> nums{ 2, 3, 4, 10, 40 };
	cout << binarySearch(nums, 10) << endl;
}

void test1()
{
	vector<int> nums{ };
	cout << binarySearch(nums, 10) << endl;
}

void test2()
{
	vector<int> nums{ 10 };
	cout << binarySearch(nums, 10) << endl;
}

void driver()
{
	test0();
	test1();
	test2();
}