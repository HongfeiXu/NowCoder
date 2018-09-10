#include "����ģʽ.h"

// ����ʽ�����̰߳�ȫ��
// �ص㣺1. Lazy ��ʼ����2. �Ƕ��̰߳�ȫ
// �ŵ㣺��һ�ε��òų�ʼ���������ڴ��˷ѡ�
// ȱ�㣺����������ڡ��̰߳�ȫ�����ַ�����μ��������ܱ�֤��������������Ӱ��Ч�ʡ�

//Singleton *Singleton::m_pSingleton = nullptr;
//
//Singleton *Singleton::GetInstance()
//{
//	// δ�������Ƕ��̰߳�ȫ
//	if (m_pSingleton == nullptr)
//		m_pSingleton = new Singleton();
//	return m_pSingleton;
//}

// ����ʽ
// �ص㣺1. �� Lazy ��ʼ����2. ���̰߳�ȫ
// �е㣺û�м�����ִ��Ч�ʻ���ߡ�
// ȱ�㣺�����ʱ�ͳ�ʼ�����˷��ڴ�

Singleton *Singleton::m_pSingleton = new Singleton();

Singleton *Singleton::GetInstance()
{
	return m_pSingleton;
}

// ����ʽ���̰߳�ȫ��

//Singleton *Singleton::m_pSingleton = nullptr;
//mutex Singleton::m_mutex;
//
//Singleton *Singleton::GetInstance()
//{
//	if (m_pSingleton == nullptr)
//	{
//		std::lock_guard<std::mutex> lock(m_mutex);	// �Խ���
//		if (m_pSingleton == nullptr)
//		{
//			m_pSingleton = new Singleton();
//		}
//	}
//	return m_pSingleton;
//}


// ��Դ�ͷ�
Singleton::GC Singleton::GC::gc;

//void test0()
//{
//	Singleton* a = Singleton::GetInstance();
//	Singleton* b = Singleton::GetInstance();
//	cout << (a == b) << endl;
//}
//
//void driver()
//{
//	test0();
//}