#pragma once

/*

��Ŀ������
С������ʵ��һ���绰��������ز�ѯϵͳ��
�绰��������صĹ�������ͨ����Ӫ���ṩ�ġ���Ӫ�̸��Ĺ����ı��У�ÿһ�а��������ַ�����
��һ���ַ�����ʾ�绰�����ǰ׺���ڶ����ַ�����ʾƥ�䵽��ǰ׺�ĵ绰����Ĺ����ء�
ÿһ��ǰ׺�������硰123456xxxxx���������ַ�������ʽΪ���ɸ����ֽ������ɸ���x����
���ܳ���Ϊ11�����е��ַ���x����ʾ����ƥ���������֣�������ǰ6���ַ�Ϊ��123456���ĵ绰���붼����ƥ�䵽��ǰ׺��
С�������Ѿ���һ�������Ĺ�����ˣ����������ھ�Ҫ��ѯһЩ�绰����Ĺ����أ���ô�Ϳ����ɡ�

����������
�����һ��Ϊһ��������T����ʾ��T������T�����ݡ�
ÿ�����ݵĵ�һ����һ��������N���ֱ��ʾ�������������������N�У�ÿһ���������ַ�������һ���ַ�����ʾ�绰�����ǰ׺��
�ڶ����ַ�����ʾƥ�䵽��ǰ׺�ĵ绰����Ĺ����ء�ǰ׺����ʽ����������������Ϊһ�����Ȳ�����30���ַ������ɴ�Сд��ĸ��������ɡ�
������һ����һ��������M����ʾҪ��ѯ�ĵ绰�����������������M��ÿһ��Ϊһ���绰���룬��11λ��������ɡ�
���ݱ�֤������һ���绰����ͬʱƥ�䵽���ǰ׺�������

���ݷ�Χ��
��������30%�����ݣ�����1<=M,N<=100��
�����������ݣ����� 1<=N<=20000, 1<=M<=100000, 1<=T<=5��

ͨ�� 30%

*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// ��һ��pass 30%
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
			// Time consuming, ÿһ����ȷ�������صĺ��룬�����й����غ�����бȽ�
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

// ������ʹ�� Trie ���ݽṹ���ӿ��ַ��������ٶȣ�ȷ�����������У������غ����Ƿ��Ѿ����ڣ����ڵĻ��Ƕ���

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
			// ��ÿ�����룬��Trie���в���11�Σ�ÿ�β��ҵ�ʱ�临�Ӷ�����Ϊ11�����������11λ��
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