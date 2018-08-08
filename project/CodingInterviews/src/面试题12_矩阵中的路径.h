#pragma once

/*

面试题12：矩阵中的路径

*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

// 判断从 (row, col) 字符出发能否构成目标字符串 s
bool hasPath(vector<vector<char>>& mat, int rows, int cols, int row, int col, string &s, int& index, vector<vector<bool>>& visited)
{
	// 前面的s.length()个字符已经匹配
	if (s.length() == index)
		return true;

	// 越界，则直接返回 false
	if (row < 0 || row >= rows || col < 0 || col >= cols)
		return false;

	// 当前字符不符合或者已经被访问过，返回 false
	if (mat[row][col] != s[index] || visited[row][col])
		return false;

	// 标记当前字符为已经访问
	visited[row][col] = true;
	bool result = false;
	++index;
	result = hasPath(mat, rows, cols, row - 1, col, s, index, visited) 
		|| hasPath(mat, rows, cols, row + 1, col, s, index, visited)
		|| hasPath(mat, rows, cols, row, col - 1, s, index, visited)
		|| hasPath(mat, rows, cols, row, col + 1, s, index, visited);

	// （递归）返回上一层的时候，标记为未访问
	visited[row][col] = false;
	--index;

	return result;
}

bool hasPath(char* matrix, int rows, int cols, char* str)
{
	if (matrix == nullptr || rows < 1 || cols < 1 ||str == nullptr)
		return false;

	vector<vector<char>> mat(rows, vector<char>(cols));
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			mat[i][j] = matrix[i * cols + j];
		}
	}

	string s(str);
	vector<vector<bool>> visited(rows, vector<bool>(cols, false));
	int index = 0;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (hasPath(mat, rows, cols, i, j, s, index, visited))
				return true;
		}
	}
	return false;
}

// ====================测试代码====================
void Test(char* testName, char* matrix, int rows, int cols, char* str, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (hasPath(matrix, rows, cols, str) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

//ABTG
//CFCS
//JDEH

//BFCE
void Test1()
{
	char* matrix = "ABTGCFCSJDEH";
	char* str = "BFCE";

	Test("Test1", (char*)matrix, 3, 4, str, true);
}

//ABCE
//SFCS
//ADEE

//SEE
void Test2()
{
	char* matrix = "ABCESFCSADEE";
	char* str = "SEE";

	Test("Test2", (char*)matrix, 3, 4, str, true);
}

//ABTG
//CFCS
//JDEH

//ABFB
void Test3()
{
	char* matrix = "ABTGCFCSJDEH";
	char* str = "ABFB";

	Test("Test3", (char*)matrix, 3, 4, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SLHECCEIDEJFGGFIE
void Test4()
{
	char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	char* str = "SLHECCEIDEJFGGFIE";

	Test("Test4", (char*)matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEM
void Test5()
{
	char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	char* str = "SGGFIECVAASABCEHJIGQEM";

	Test("Test5", (char*)matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEEJIGOEM
void Test6()
{
	char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	char* str = "SGGFIECVAASABCEEJIGOEM";

	Test("Test6", (char*)matrix, 5, 8, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEMS
void Test7()
{
	char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	char* str = "SGGFIECVAASABCEHJIGQEMS";

	Test("Test7", (char*)matrix, 5, 8, str, false);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAA
void Test8()
{
	char* matrix = "AAAAAAAAAAAA";
	char* str = "AAAAAAAAAAAA";

	Test("Test8", (char*)matrix, 3, 4, str, true);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAAA
void Test9()
{
	char* matrix = "AAAAAAAAAAAA";
	char* str = "AAAAAAAAAAAAA";

	Test("Test9", (char*)matrix, 3, 4, str, false);
}

//A

//A
void Test10()
{
	char* matrix = "A";
	char* str = "A";

	Test("Test10", (char*)matrix, 1, 1, str, true);
}

//A

//B
void Test11()
{
	char* matrix = "A";
	char* str = "B";

	Test("Test11", (char*)matrix, 1, 1, str, false);
}

void Test12()
{
	Test("Test12", nullptr, 0, 0, nullptr, false);
}

void driver()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	Test9();
	Test10();
	Test11();
	Test12();
}
