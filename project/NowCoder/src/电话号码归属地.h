#pragma once

/*

题目描述：
小明正在实现一个电话号码归属地查询系统。
电话号码归属地的规则是由通信运营商提供的。运营商给的规则文本中，每一行包含两个字符串，
第一个字符串表示电话号码的前缀，第二个字符串表示匹配到该前缀的电话号码的归属地。
每一个前缀都是形如“123456xxxxx”这样的字符串，形式为若干个数字接着若干个“x”，
且总长度为11，其中的字符“x”表示可以匹配任意数字，即所有前6个字符为“123456”的电话号码都可以匹配到该前缀。
小明手上已经有一份这样的规则表了，并且他现在就要查询一些电话号码的归属地，那么就开工吧。

输入描述：
输入第一行为一个正整数T，表示有T组数据T组数据。
每组数据的第一行有一个正整数N，分别表示规则的数量。接下来有N行，每一行有两个字符串，第一个字符串表示电话号码的前缀，
第二个字符串表示匹配到该前缀的电话号码的归属地。前缀的形式如上所属，归属地为一个长度不超过30的字符串，由大小写字母和数字组成。
接下来一行有一个正整数M，表示要查询的电话号码的数量。接下来M行每一个为一个电话号码，由11位的数字组成。
数据保证不存在一个电话号码同时匹配到多个前缀的情况。

数据范围：
对于其中30%的数据，满足1<=M,N<=100；
对于所有数据，满足 1<=N<=20000, 1<=M<=100000, 1<=T<=5。

通过 30%

*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// 法一：pass 30%
void solution1()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		int N;
		cin >> N;
		map<string, string> dict;
		vector<string> regionNumbers;
		for (int j = 0; j < N; ++j)
		{
			string number;
			string position;
			cin >> number >> position;
			auto firstXPos = number.find('x');
			if (firstXPos != string::npos)
				number.erase(firstXPos);
			dict[number] = position;
			regionNumbers.push_back(number);
		}
		int M;
		cin >> M;
		for (int j = 0; j < M; ++j)
		{
			string inputNumber;
			cin >> inputNumber;

			if (inputNumber.length() != 11)
			{
				cout << "unknown" << endl;
				continue;
			}

			bool exists = false;
			// Time consuming, 每一个待确定归属地的号码，和所有归属地号码进行比较
			for (int k = 0; k < regionNumbers.size(); ++k)
			{
				int regionNumberLen = regionNumbers[k].length();
				if (inputNumber.length() > regionNumberLen && inputNumber.substr(0, regionNumberLen) == regionNumbers[k])
				{
					cout << dict[regionNumbers[k]] << endl;
					exists = true;
					break;
				}
			}
			if (!exists)
				cout << "unknown" << endl;
		}
	}
}

// 法二：使用 Trie 数据结构，加快字符串搜索速度，确定待定号码中，归属地号码是否已经存在，存在的话是多少

const int ALPHABET_SIZE = 10;

struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
};

TrieNode* getNode()
{
	TrieNode* pNode = new TrieNode;
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		pNode->children[i] = nullptr;
	pNode->isEndOfWord = false;
	return pNode;
}

void insert(TrieNode* root, string key)
{
	TrieNode* pCrawl = root;
	for (int i = 0; i < key.length(); ++i)
	{
		int index = key[i] - '0';
		if (pCrawl->children[index] == nullptr)
		{
			pCrawl->children[index] = getNode();
		}
		pCrawl = pCrawl->children[index];
	}
	pCrawl->isEndOfWord = true;
}

bool search(TrieNode* root, string::iterator key_iter_begin, string::iterator key_iter_end)
{
	TrieNode* pCrawl = root;
	int len = key_iter_end - key_iter_begin;
	for (int i = 0; i < len; ++i)
	{
		int index = *(key_iter_begin + i) - '0';
		if (pCrawl->children[index] == nullptr)
		{
			return false;
		}
		pCrawl = pCrawl->children[index];
	}
	return pCrawl->isEndOfWord;
}

void solution2()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		TrieNode* root = getNode();
		int N;
		cin >> N;
		unordered_map<string, string> dict;
		for (int j = 0; j < N; ++j)
		{
			string number;
			string position;
			cin >> number >> position;
			auto firstXPos = number.find('x');
			if (firstXPos != string::npos)
				number.erase(firstXPos);
			dict[number] = position;
			insert(root, number);
		}
		int M;
		cin >> M;
		for (int j = 0; j < M; ++j)
		{
			string inputNumber;
			cin >> inputNumber;

			if (inputNumber.length() != 11)
			{
				cout << "unknown" << endl;
				continue;
			}

			bool found = false;
			// 对每个号码，在Trie树中查找11次，每次查找的时间复杂度至多为11（归属地最多11位）
			for (int k = 1; k < 11; ++k)
			{
				if (search(root, inputNumber.begin(), inputNumber.begin() + k))
				{
					cout << dict[inputNumber.substr(0, k)] << endl;
					found = true;
				}
			}
			if (!found)
				cout << "unknown" << endl;
		}
	}
}