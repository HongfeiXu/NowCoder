#pragma once

/*

题目描述：




审题一定要仔细，尤其对于题目中重要的条件，要放大页面去看！！！
因为审题的原因，出错。
另外，提交出问题后，不要忙着去质疑题目，大概率是自己的逻辑有问题。谨记！

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool my_isdigit(char ch)
{
	return std::isdigit(static_cast<unsigned char>(ch));
}

bool my_isupper(char ch)
{
	return std::isupper(static_cast<unsigned char>(ch));
}

bool my_islower(char ch)
{
	return std::islower(static_cast<unsigned char>(ch));
}

bool StrongPassWd(const string& passwd, 
	const string& upperChar, 
	const string& lowerChar, 
	const string& numberChar, 
	const string& spChar,
	vector<string>& badPassWd)
{
	// rule 1
	int len = passwd.length();
	if (len < 8)
		return false;
	// rule 2
	if (passwd.find_first_of(upperChar) == string::npos
		|| passwd.find_first_of(lowerChar) == string::npos
		|| passwd.find_first_of(numberChar) == string::npos
		|| passwd.find_first_of(spChar) == string::npos)
		return false;

	// rule 3
	for (int i = 0; i <= len - 3; ++i)
	{
		if (my_isdigit(passwd[i]) && my_isdigit(passwd[i + 1]) && my_isdigit(passwd[i + 2]))
		{
			if (passwd[i + 1] - passwd[i] == passwd[i + 2] - passwd[i + 1])
				return false;
		}
	}

	// rule 4
	for (int i = 0; i <= len - 3; ++i)
	{
		if (my_isupper(passwd[i]) && my_isupper(passwd[i + 1]) && my_isupper(passwd[i + 2]))
		{
			if (passwd[i + 1] - passwd[i] == 1 && passwd[i + 2] - passwd[i + 1] == 1)
				return false;
		}
		if (my_islower(passwd[i]) && my_islower(passwd[i + 1]) && my_islower(passwd[i + 2]))
		{
			if (passwd[i + 1] - passwd[i] == 1 && passwd[i + 2] - passwd[i + 1] == 1)
				return false;
		}
	}

	// rule 5
	for (unsigned i = 0; i < badPassWd.size(); ++i)
	{
		if (passwd.find(badPassWd[i]) != string::npos)
			return false;
	}
	return true;
}

void driver()
{
	string upperChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string lowerChar = "abcdefghijklmnopqrstuvwxyz";
	string numberChar = "0123456789";
	string spChar = "!@#$%^&*()_-=+[]{},.<>/?";
	vector<string> badPassWd = { "password", "admin", "qwerty", "hello", "iloveyou", "112233" };
	int N;
	cin >> N;
	string passwd;
	for (int i = 0; i < N; ++i)
	{
		cin >> passwd;
		if (StrongPassWd(passwd, upperChar, lowerChar, numberChar, spChar, badPassWd))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
}

// 如果有和输入不相符的会输出
void driverFromFile()
{
	string upperChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string lowerChar = "abcdefghijklmnopqrstuvwxyz";
	string numberChar = "0123456789";
	string spChar = "!@#$%^&*()_-=+[]{},.<>/?";
	vector<string> badPassWd = { "password", "admin", "qwerty", "hello", "iloveyou", "112233" };

	ifstream passwordinFS("testcases/passwordin.txt");
	ifstream passwordoutFS("testcases/passwordout.txt");


	int num = 0;
	passwordinFS >> num;

	vector<string> passwordin(num);
	vector<string> passwordout(num);

	for (int i = 0; i < num; ++i)
	{
		passwordinFS >> passwordin[i];
		passwordoutFS >> passwordout[i];
	}

	//for (int i = 0; i < 10; ++i)
	//{
	//	cout << passwordin[i] << endl;
	//	cout << passwordout[i] << endl;
	//}

	string myresult;
	for (int i = 0; i < num; ++i)
	{
		if (StrongPassWd(passwordin[i], upperChar, lowerChar, numberChar, spChar, badPassWd))
			myresult = "yes";
		else
			myresult = "no";
		if (myresult != passwordout[i])
		{
			cout << "Wrong Case: " << passwordin[i] << endl;
			cout << "my result: " << myresult << endl;
			cout << "actural result: " << passwordout[i] << endl;
		}
	}
}