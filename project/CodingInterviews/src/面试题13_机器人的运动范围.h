#pragma once

/*

������13�������˵��˶���Χ

��Ŀ��
������һ��m�к�n�еķ���һ�������˴�����0,0�ĸ��ӿ�ʼ�ƶ���ÿһ��ֻ�������ң��ϣ����ĸ������ƶ�һ�񣬵��ǲ��ܽ�������������������λ֮�ʹ���k�ĸ��ӡ� 
���磬��kΪ18ʱ���������ܹ����뷽��35,37������Ϊ3+5+3+7 = 18�����ǣ������ܽ��뷽��35,38������Ϊ3+5+3+8 = 19�����ʸû������ܹ��ﵽ���ٸ����ӣ�

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
	// ��������Ѿ����ʹ��ģ�ֱ�ӷ���
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

// == == == == == == == == == == ���Դ��� == == == == == == == == == ==
void test(char* testName, int threshold, int rows, int cols, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (movingCount(threshold, rows, cols) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// ������ж���
void test1()
{
	test("Test1", 5, 10, 10, 21);
}

// ������ж���
void test2()
{
	test("Test2", 15, 20, 20, 359);
}

// ����ֻ��һ�У�������ֻ�ܵ��ﲿ�ַ���
void test3()
{
	test("Test3", 10, 1, 100, 29);
}

// ����ֻ��һ�У��������ܵ������з���
void test4()
{
	test("Test4", 10, 1, 10, 10);
}

// ����ֻ��һ�У�������ֻ�ܵ��ﲿ�ַ���
void test5()
{
	test("Test5", 15, 100, 1, 79);
}

// ����ֻ��һ�У��������ܵ������з���
void test6()
{
	test("Test6", 15, 10, 1, 10);
}

// ����ֻ��һ��һ��
void test7()
{
	test("Test7", 15, 1, 1, 1);
}

// ����ֻ��һ��һ��
void test8()
{
	test("Test8", 0, 1, 1, 1);
}

// �����˲��ܽ�������һ������
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