#pragma once

/*

面试题13：机器人的运动范围

题目：
地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 
例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？

*/

#include <iostream>
#include <vector>

using namespace std;

int digitSum(int number)
{
	int result = 0;
	while (number != 0)
	{
		result += number % 10;
		number /= 10;
	}
	return result;
}

void movingCountAux(int threshold, int rows, int cols, int row, int col, vector<vector<bool>>& visited, int& cnt)
{
	// 出界或者已经访问过的，直接返回
	if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col])
		return;
	visited[row][col] = true;
	if (digitSum(row) + digitSum(col) > threshold)
	{
		return;
	}
	++cnt;
	movingCountAux(threshold, rows, cols, row - 1, col, visited, cnt);
	movingCountAux(threshold, rows, cols, row + 1, col, visited, cnt);
	movingCountAux(threshold, rows, cols, row, col - 1, visited, cnt);
	movingCountAux(threshold, rows, cols, row, col + 1, visited, cnt);
}

int movingCount(int threshold, int rows, int cols)
{
	if (threshold < 0 || rows == 0 || cols == 0)
		return 0;

	vector<vector<bool>> visited(rows, vector<bool>(cols, false));
	int cnt = 0;
	int row = 0, col = 0;
	movingCountAux(threshold, rows, cols, row, col, visited, cnt);

	return cnt;
}

// == == == == == == == == == == 测试代码 == == == == == == == == == ==
void test(char* testName, int threshold, int rows, int cols, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (movingCount(threshold, rows, cols) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// 方格多行多列
void test1()
{
	test("Test1", 5, 10, 10, 21);
}

// 方格多行多列
void test2()
{
	test("Test2", 15, 20, 20, 359);
}

// 方格只有一行，机器人只能到达部分方格
void test3()
{
	test("Test3", 10, 1, 100, 29);
}

// 方格只有一行，机器人能到达所有方格
void test4()
{
	test("Test4", 10, 1, 10, 10);
}

// 方格只有一列，机器人只能到达部分方格
void test5()
{
	test("Test5", 15, 100, 1, 79);
}

// 方格只有一列，机器人能到达所有方格
void test6()
{
	test("Test6", 15, 10, 1, 10);
}

// 方格只有一行一列
void test7()
{
	test("Test7", 15, 1, 1, 1);
}

// 方格只有一行一列
void test8()
{
	test("Test8", 0, 1, 1, 1);
}

// 机器人不能进入任意一个方格
void test9()
{
	test("Test9", -10, 10, 10, 0);
}

void driver()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
}