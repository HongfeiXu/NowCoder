#include <iostream>
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

bool StrongPassWd(const string& passwd, const string& upperChar, const string& lowerChar, const string& numberChar, const string& spChar)
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
			if (passwd[i + 1] - passwd[i] > 0 && passwd[i + 2] - passwd[i + 1] > 0)
				return false;
		}
		if (my_islower(passwd[i]) && my_islower(passwd[i + 1]) && my_islower(passwd[i + 2]))
		{
			if (passwd[i + 1] - passwd[i] > 0 && passwd[i + 2] - passwd[i + 1] > 0)
				return false;
		}
	}

	// rule 5
	vector<string> badPassWd = { "password", "admin", "qwerty", "hello", "iloveyour", "112233" };
	for (unsigned i = 0; i < badPassWd.size(); ++i)
	{
		if (passwd.find(badPassWd[i]) != string::npos)
			return false;
	}
	return true;
}

//int main()
//{
//	string upperChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	string lowerChar = "abcdefghijklmnopqrstuvwxyz";
//	string numberChar = "0123456789";
//	string spChar = "!@#$%^&*()_-=+[]{},.<>?";
//	int N;
//	cin >> N;
//	string passwd;
//	for (int i = 0; i < N; ++i)
//	{
//		cin >> passwd;
//		if (StrongPassWd(passwd, upperChar, lowerChar, numberChar, spChar))
//			cout << "yes" << endl;
//		else
//			cout << "no" << endl;
//	}
//	return 0;
//}