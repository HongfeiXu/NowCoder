#pragma once

/*

����ģʽ

Ref: https://blog.csdn.net/liang19890820/article/details/61615495#

����ģʽ��Singleton Pattern�������ģʽ����򵥵���ʽ֮һ����һ�ִ�����ģʽ
��Ŀ����ʹ�����һ�������Ϊϵͳ�е�Ψһʵ����

����ģʽ�漰��һ����һ���࣬���ฺ�𴴽��Լ��Ķ���ͬʱȷ��ֻ�е������󱻴�����
������ṩ��һ�ַ�����Ψһ����ķ�ʽ������ֱ�ӷ��ʣ�����Ҫʵ��������Ķ���

Ҫ��

����ģʽ��Ҫ����������

	���������ҽ���һ��ʵ��
	������������д����Լ���Ψһʵ��
	�����������������������ṩ��һʵ��

�Ӿ���ʵ�ֽǶ���˵���ɷ�Ϊ�������㣺

	�ṩһ�� private ���캯������ֹ�ⲿ���ö��������ʵ����
	�ṩһ������� static private ����
	�ṩһ�� static public ���������ڴ������ȡ�䱾��ľ�̬˽�ж������磺GetInstance()��

����֮�⣬����һЩ�ؼ��㣨��Ҫ���ע�⣬�����׺��ӣ���

	�̰߳�ȫ��˫���� - DCL������double-checked locking��
	��Դ�ͷ�

*/

#include <iostream>
#include <mutex>

using namespace std;

///////////////////////////////////////////////////
// �ֲ���̬�����ķ�ʽʵ�ֵ���ģʽ

// ��һ������ָ��
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		static Singleton instance;
//		return &instance;
//	}
//
//private:
//	Singleton() {}
//};

// ��������ֹ����
//class Singleton
//{
//public:
//	// ��ֹ����
//	Singleton(const Singleton &) = delete;
//	Singleton& operator= (const Singleton &) = delete;
//
//	static Singleton& GetInstance()
//	{
//		static Singleton instance;
//		return instance;
//	}
//
//private:
//	Singleton() {}
//};

///////////////////////////////////////////////////
// ����ʽ\����ʽ

// ����ʽ�����̰߳�ȫ��\����ʽ����
//class Singleton 
//{
//public:
//	static Singleton* GetInstance();
//
//private:
//	Singleton() {}	// ���캯������������
//
//private:
//	static Singleton *m_pSingleton;		// ָ���������ָ��
//};


///////////////////////////////////////////////////
// ����ʽ���̰߳�ȫ��
//class Singleton
//{
//public:
//	static Singleton *GetInstance();
//
//private:
//	Singleton() {}	// ���캯��
//
//private:
//	static Singleton *m_pSingleton;		// ָ���������ָ��
//	static mutex m_mutex;				// ��
//};


///////////////////////////////////////////////////
// ��Դ�ͷ�

// �����ͷţ��ֶ����ýӿ����ͷ���Դ��
// �Զ��ͷţ��ɳ����Լ��ͷţ�
class Singleton 
{
public:
	static Singleton* GetInstance();
	//static void DestroyInstance()
	//{
	//	if (m_pSingleton != nullptr)
	//	{
	//		delete m_pSingleton;
	//		m_pSingleton = nullptr;
	//	}
	//}

private:
	Singleton() {}	// ���캯������������

private:
	static Singleton *m_pSingleton;		// ָ���������ָ��

	// GC ���� ʵ���Զ��ͷ���Դ����Ҫ�� .cpp ���徲̬��Ա gc��������Ч
	class GC 
	{
	public:
		~GC()
		{
			if (m_pSingleton != nullptr)
			{
				cout << "Here destroy the m_pSingleton..." << endl;
				delete m_pSingleton;
				m_pSingleton = nullptr;
			}
		}

		static GC gc;
	};
};


void test0();

void driver();

