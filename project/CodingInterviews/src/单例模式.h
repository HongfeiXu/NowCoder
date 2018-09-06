#pragma once

/*

单例模式

Ref: https://blog.csdn.net/liang19890820/article/details/61615495#

单例模式（Singleton Pattern）是设计模式中最简单的形式之一，是一种创建型模式
其目的是使得类的一个对象成为系统中的唯一实例。

这种模式涉及到一个单一的类，该类负责创建自己的对象，同时确保只有单个对象被创建。
这个类提供了一种访问其唯一对象的方式，可以直接访问，不需要实例化该类的对象。

要点

单例模式的要点有三个：

	单例类有且仅有一个实例
	单例类必须自行创建自己的唯一实例
	单例类必须给所有其他对象提供这一实例

从具体实现角度来说，可分为以下三点：

	提供一个 private 构造函数（防止外部调用而构造类的实例）
	提供一个该类的 static private 对象
	提供一个 static public 函数，用于创建或获取其本身的静态私有对象（例如：GetInstance()）

除此之外，还有一些关键点（需要多加注意，很容易忽视）：

	线程安全（双检锁 - DCL，即：double-checked locking）
	资源释放

*/

#include <iostream>
#include <mutex>

using namespace std;

///////////////////////////////////////////////////
// 局部静态变量的方式实现单例模式

// 法一：返回指针
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

// 法二：阻止拷贝
//class Singleton
//{
//public:
//	// 阻止拷贝
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
// 懒汉式\饿汉式

// 懒汉式（非线程安全）\饿汉式公用
//class Singleton 
//{
//public:
//	static Singleton* GetInstance();
//
//private:
//	Singleton() {}	// 构造函数（被保护）
//
//private:
//	static Singleton *m_pSingleton;		// 指向单例对象的指针
//};


///////////////////////////////////////////////////
// 懒汉式（线程安全）
//class Singleton
//{
//public:
//	static Singleton *GetInstance();
//
//private:
//	Singleton() {}	// 构造函数
//
//private:
//	static Singleton *m_pSingleton;		// 指向单例对象的指针
//	static mutex m_mutex;				// 锁
//};


///////////////////////////////////////////////////
// 资源释放

// 主动释放（手动调用接口来释放资源）
// 自动释放（由程序自己释放）
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
	Singleton() {}	// 构造函数（被保护）

private:
	static Singleton *m_pSingleton;		// 指向单例对象的指针

	// GC 机制 实现自动释放资源，需要在 .cpp 定义静态成员 gc，否则无效
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

