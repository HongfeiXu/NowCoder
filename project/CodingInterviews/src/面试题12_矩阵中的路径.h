#pragma once

/*

������12�������е�·��

��Ŀ����
�����һ�������������ж���һ���������Ƿ����һ������ĳ�ַ��������ַ���·����
·�����ԴӾ����е�����һ�����ӿ�ʼ��ÿһ�������ھ������������ң����ϣ������ƶ�һ�����ӡ�
���һ��·�������˾����е�ĳһ�����ӣ���֮�����ٴν���������ӡ� 
���� a b c e s f c s a d e e ������3 X 4 �����а���һ���ַ���"bcced"��·����
���Ǿ����в�����"abcb"·������Ϊ�ַ����ĵ�һ���ַ�bռ���˾����еĵ�һ�еڶ�������֮��·�������ٴν���ø��ӡ�

Approach:

Backtracking

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		bool* visited = new bool[rows * cols];
		memset(visited, 0, rows*cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (hasPath(matrix, rows, cols, i, j, str, 0, visited))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool hasPath(char* matrix, int rows, int cols, int i, int j, char* str, int k, bool* visited)
	{
		if (k == strlen(str))
			return true;

		// Խ���ж�
		if (i < 0 || i > rows || j < 0 || j > cols)
			return false;

		// �ַ���ͬ�������Ѿ����ʹ�
		if (matrix[i * cols + j] != str[k] || visited[i * cols + j])
			return false;

		// ����ǰλ�ñ��Ϊ�ѷ��ʣ������ظ�����
		visited[i * cols + j] = true;
		bool result = false;
		result = hasPath(matrix, rows, cols, i - 1, j, str, k + 1, visited)
			|| hasPath(matrix, rows, cols, i + 1, j, str, k + 1, visited)
			|| hasPath(matrix, rows, cols, i, j - 1, str, k + 1, visited)
			|| hasPath(matrix, rows, cols, i, j + 1, str, k + 1, visited);

		// (�ݹ�)������һ��ʱ������ǰλ�ñ��Ϊδ����
		visited[i * cols + j] = false;

		return result;
	}
};

// ====================���Դ���====================
void Test(char* testName, char* matrix, int rows, int cols, char* str, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution solu;
	if (solu.hasPath(matrix, rows, cols, str) == expected)
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
