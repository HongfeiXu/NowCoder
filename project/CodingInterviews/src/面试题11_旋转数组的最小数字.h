#pragma once

/*

������11����ת�������С����

��Ŀ����һ�������ʼ������Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
����һ����������������һ����ת�������ת�������СԪ�ء�
���磬����{3,4,5,1,2}Ϊ{1,2,3,4,5}��һ����ת����������С��ֵΪ1��

�涨���������СΪ0���򷵻�0��

��������ת�����黮��Ϊ��������������飬ǰ���������Ԫ�ض����ڻ���ں����������Ԫ�ء�
ʹ�����ƶ��ֲ��ҵ�˼·�����������⡣

*/

#include <vector>
#include <iostream>

using namespace std;

// ������ָ��ָ������ּ������м������������ͬʱ�������޷��ж��м�������λ��ǰ��������黹�Ǻ����������
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




