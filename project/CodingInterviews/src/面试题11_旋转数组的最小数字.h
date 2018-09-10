#pragma once

/*

面试题11：旋转数组的最小数字

题目：把一个数组最开始的若干元素搬到数组的末尾，我们称之为数组的旋转。
输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
例如，数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组最小的值为1。

规定：若数组大小为0，则返回0。

分析：旋转后，数组划分为两个排序的子数组，前面子数组的元素都大于或等于后面子数组的元素。
使用类似二分查找的思路来解决这个问题。

*/

#include <vector>
#include <iostream>

using namespace std;

// 当两个指针指向的数字及它们中间的数字三者相同时，我们无法判断中间数字是位于前面的子数组还是后面的子数组
int minValInOrder(vector<int>::iterator b, vector<int>::iterator e)
{
	int result = *b;
	for (auto it = b + 1; it != e; ++it)
	{
		if (*it < result)
			result = *it;
	}
	return result;
}

int minVal(vector<int>& nums)
{
	if (nums.empty())
		return 0;
	int left = 0, right = nums.size() - 1;
	while (left < right)
	{
		int mid = (left + right) / 2;

		if (nums[left] == nums[mid] && nums[right] == nums[mid])
			return minValInOrder(nums.begin() + left, nums.begin() + right - 1);

		if (nums[mid] < nums[right])
			right = mid;
		else
			left = mid + 1;
	}
	return nums[left];
}

void test()
{
	vector<int> nums{ 4,5,1,2,3 };
	cout << minVal(nums) << endl;
	nums = { 4,5,5,2,3 };
	cout << minVal(nums) << endl;
	nums = { 1,1,1,1,1 };
	cout << minVal(nums) << endl;
	nums = { 3,4,5,1,2 };
	cout << minVal(nums) << endl;
	nums = {};
	cout << minVal(nums) << endl;
	nums = { 1,2,3,4,5 };
	cout << minVal(nums) << endl;
	nums = { 1,0,1,1,1 };
	cout << minVal(nums) << endl;
}

void driver()
{
	test();
}




