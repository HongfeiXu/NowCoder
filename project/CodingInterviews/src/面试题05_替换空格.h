#pragma once

/*

������05���滻�ո�

��Ŀ����ʵ��һ�����������ַ����е�ÿ���ո��滻�ɡ�%20�������磬
���롰We are happy.�����������We%20are%20happy.����

*/

#include <string>
#include <iostream>
#include <cstring>

using namespace std;

// Time: O(n)
// Space: O(n)
string ReplaceSpace(string input)
{
	string output;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == ' ')
			output.append("%20");
		else
			output.push_back(input[i]);
	}
	return output;
}

// length Ϊ s ��������
void ReplaceSpaceV2(char s[], int length)
{
	int originalLength = 0;
	int numOfBlank = 0;
	int i = 0;
	while (s[i] != '\0')
	{
		++originalLength;
		if (s[i] == ' ')
			++numOfBlank;
		++i;
	}

	for (int j = originalLength - 1; j >= 0; --j)
	{
		if (s[j] == ' ')
		{
			--numOfBlank;
			s[j + numOfBlank * 2 + 2] = '0';
			s[j + numOfBlank * 2 + 1] = '2';
			s[j + numOfBlank * 2 + 0] = '%';
		}
		else
		{
			s[j + numOfBlank * 2] = s[j];
		}
	}
}

void ReplaceSpaceV3(char s[], int length)
{
	if (s == nullptr || length <= 0)
		return;

	int originalLength = 0;
	int numOfBlank = 0;
	int i = 0;
	while (s[i] != '\0')
	{
		++originalLength;
		if (s[i] == ' ')
			++numOfBlank;
		++i;
	}

	int newLength = originalLength + 2 * numOfBlank;
	if (newLength > length)
		return;

	int indexOfOriginal = originalLength;
	int indexOfNew = newLength;
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
	{
		if (s[indexOfOriginal] == ' ')
		{
			s[indexOfNew--] = '0';
			s[indexOfNew--] = '2';
			s[indexOfNew--] = '%';
		}
		else
		{
			s[indexOfNew--] = s[indexOfOriginal];
		}
		--indexOfOriginal;
	}
}

// ====================���Դ���================

void test1()
{
	string input = "We are happy.";
	string result = ReplaceSpace(input);
	cout << result << endl;
	cout << result.size() << endl;
}

void test2()
{
	char str[100] = "A B C";
	ReplaceSpaceV3(str, 100);
	cout << str << endl;
}

void driver()
{
	test1();
	test2();
}
