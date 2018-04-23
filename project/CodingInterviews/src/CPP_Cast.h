#pragma once

/*

P23
�� C++ �У�����4��������ת����صĹؼ��֣�
��Щ�ؼ��ָ���ʲô�ص㣬Ӧ����ʲô������ʹ�ã�

1. const_cast
��ӻ��Ƴ��ײ�const���ײ�const��ʾָ����ָ�Ķ�����һ����������ԵĶ���const��ʾָ�뱾����һ����������� C++ Primier ����� P145��p57

2. static_cast
���л�������ת�����κξ�����ȷ���������ת����ֻҪ�������ײ�const��������ʹ��static_cast��
���⣬static_cast�Ա������޷��Զ�ִ�е�����ת��Ҳ�ǳ����á���ϸ����������ӡ�

3. dynamic_cast
�����м��Ķ�̬ת�������ڽ������ָ������ð�ȫ��ת�����������ָ������á�

4. reinterpret_cast
��ת��ײ�λģʽ�����ͼ�ת����

*/

#include <iostream>
using namespace std;

// 1. const_cast
void cc_test()
{
	char c = 'A';
	const char* const_pc = &c;
	char* pc = const_cast<char*>(const_pc);			// ȥ�� const ����
	*pc = 'a';
	cout << c << endl;

	char d = 'A';
	char* pd = &d;
	const char* const_pd = const_cast<char*>(pd);	// ��� const ����
	cout << *const_pd << endl;
	*pd = 'B';
	cout << *const_pd << endl;
}

// 2. static_cast
void sc_test()
{
	int i = 3;
	int j = 2;
	double r = static_cast<double>(i) / static_cast<double>(j);
	cout << i / j << " " << r << endl;
	
	void *pr = &r;								// �κηǳ�������ĵ�ַ���ܴ��� void*
	double *pd = static_cast<double*>(pr);		// �� void* ת���س�ʼ��ָ������
	cout << *pd << endl;
	//cout << *pr << endl;	// pr ������ָ���������͵�ָ��
}

// TODO...

// 3. dynamic_cast

// 4. reinterpret_cast


