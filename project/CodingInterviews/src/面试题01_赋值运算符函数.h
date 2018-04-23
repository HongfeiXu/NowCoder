#pragma once

/*

面试题01：赋值运算符函数

题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数。

Approach:

要注意
1. 连续赋值问题
2. 自赋值问题
3. 异常安全性问题（即，当new抛出异常时，CMyString实例是否依然有效）

*/

#include <cstring>
#include <iostream>

class CMyString 
{
public:
	CMyString(char* pData = nullptr);
	CMyString(const CMyString& str);
	~CMyString(void);

	CMyString& operator=(const CMyString& rhs);

	void Print();

private:
	char* m_pData;
};

CMyString::CMyString(char* pData /*= nullptr */)
{
	if (pData == nullptr)
	{
		m_pData = new char[1];
		m_pData[0] = '\0';		// 空字符串，无有效字符，但需要有一位结束字符，方便输出
	}
	else
	{
		m_pData = new char[strlen(pData) + 1];
		strcpy(m_pData, pData);
	}
}

CMyString::CMyString(const CMyString& str)
{
	m_pData = new char[strlen(str.m_pData) + 1];
	strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString(void)
{
	if (m_pData != nullptr)
		delete[] m_pData;
}

// version 1
//CMyString& CMyString::operator=(const CMyString& rhs)
//{
//	if (this == &rhs)
//		return *this;
//
//	char* pTemp = new char[strlen(rhs.m_pData) + 1];
//	strcpy(pTemp, rhs.m_pData);
//	delete[] m_pData;
//	m_pData = pTemp;
//	return *this;
//}

// version 2
CMyString& CMyString::operator=(const CMyString& rhs)
{
	if (this == &rhs)
		return *this;

	CMyString temp(rhs);

	char* pTemp = temp.m_pData;
	temp.m_pData = this->m_pData;
	this->m_pData = pTemp;
	
	return *this;
}

void CMyString::Print()
{
	std::cout << m_pData;
}

// ====================测试代码================

// 构造函数，拷贝构造函数
void Test1()
{
	std::cout << "Test1 begins:" << std::endl;
	char* text = "Hello World";

	CMyString str1(text);
	CMyString str2(str1);

	std::cout << "The expected result is: " << text << "." << std::endl;
	std::cout << "The actual result is: ";
	str2.Print();
	std::cout << "." << std::endl;
}

// 赋值给自己
void Test2()
{
	std::cout << "Test2 begins:" << std::endl;
	char* text = "Hello World";
	CMyString str1(text);
	str1 = str1;
	std::cout << "The expected result is: " << text << "." << std::endl;
	std::cout << "The actual result is: ";
	str1.Print();
	std::cout << "." << std::endl;
}

// 连续赋值
void Test3()
{
	std::cout << "Test3 begins:" << std::endl;
	char* text = "Hello World";
	CMyString str1(text);
	CMyString str2, str3;
	str3 = str2 = str1;
	std::cout << "The expected result is: " << text << "." << std::endl;
	std::cout << "The actual result is: ";
	str2.Print();
	std::cout << "." << std::endl;
	std::cout << "The expected result is: " << text << "." << std::endl;
	std::cout << "The actual result is: ";
	str3.Print();
	std::cout << "." << std::endl;
}

void driver()
{
	Test1();
	Test2();
	Test3();
}