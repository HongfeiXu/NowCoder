#include "单例模式.h"

// 懒汉式（非线程安全）
// 特点：1. Lazy 初始化；2. 非多线程安全
// 优点：第一次调用才初始化，避免内存浪费。
// 缺点：必须加锁（在“线程安全”部分分享如何加锁）才能保证单例，但加锁会影响效率。

//Singleton *Singleton::m_pSingleton = nullptr;
//
//Singleton *Singleton::GetInstance()
//{
//	// 未加锁，非多线程安全
//	if (m_pSingleton == nullptr)
//		m_pSingleton = new Singleton();
//	return m_pSingleton;
//}

// 饿汉式
// 特点：1. 非 Lazy 初始化；2. 多线程安全
// 有点：没有加锁，执行效率会提高。
// 缺点：类加载时就初始化，浪费内存

Singleton *Singleton::m_pSingleton = new Singleton();

Singleton *Singleton::GetInstance()
{
	return m_pSingleton;
}

// 懒汉式（线程安全）

//Singleton *Singleton::m_pSingleton = nullptr;
//mutex Singleton::m_mutex;
//
//Singleton *Singleton::GetInstance()
//{
//	if (m_pSingleton == nullptr)
//	{
//		std::lock_guard<std::mutex> lock(m_mutex);	// 自解锁
//		if (m_pSingleton == nullptr)
//		{
//			m_pSingleton = new Singleton();
//		}
//	}
//	return m_pSingleton;
//}


// 资源释放
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