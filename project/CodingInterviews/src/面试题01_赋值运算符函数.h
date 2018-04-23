#pragma once

/*

������01����ֵ���������

��Ŀ������Ϊ����CMyString����������Ϊ��������Ӹ�ֵ�����������

Approach:

Ҫע��
1. ������ֵ����
2. �Ը�ֵ����
3. �쳣��ȫ�����⣨������new�׳��쳣ʱ��CMyStringʵ���Ƿ���Ȼ��Ч��

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
		m_pData[0] = '\0';		// ���ַ���������Ч�ַ�������Ҫ��һλ�����ַ����������
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

// ====================���Դ���================

// ���캯�����������캯��
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

// ��ֵ���Լ�
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

// ������ֵ
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