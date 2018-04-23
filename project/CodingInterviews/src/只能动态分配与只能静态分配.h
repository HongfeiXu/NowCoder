#pragma once

/*

C++如何实现类对象只能动态分配或只能静态分配？

C++中建立类的对象有两种方式：
（1）静态建立，例如 A a;
静态建立一个类对象，就是由编译器为对象在栈空间中分配内存。使用这种方法，是直接调用类的构造函数。
（2）动态建立，例如 A* p = new A();
动态建立一个类对象，就是使用new运算符为对象在堆空间中分配内存。这个过程分为两步：第一步执行operator new( )函数，在堆空间中搜索一块内存并进行分配；第二步调用类的构造函数构造对象。
这种方法是间接调用类的构造函数。

*/

/*

只能动态分配：类对象只能通过new运算符建立在堆空间中，不能静态分配，即不能直接调用类的构造函数。

注意：编译器在为类对象分配栈空间时，会先检查类的析构函数的访问性（其实不光是析构函数，只要是非静态的函数，编译器都会进行检查）。如果类的析构函数在类外部无法访问，则编译器拒绝在栈空间上为类对象分配内存。

因此，可以将析构函数设为private，这样就无法在栈上建立类对象了。

*/

class A {
public:
	A() { }
	void destory() { delete this; }
private:
	~A() { }
};

/*

上面的方法虽然能实现只能动态建立对象，但是有一个缺点：无法实现继承。因为如果A作为基类的话，则析构函数通常要设为virtual，然后在子类中被重写，以实现多态。因此析构函数不能设为private。
C++还提供了第三种访问控制，就是protected。将析构函数设为protected，类外无法访问protected成员，但是子类可以访问。完美解决问题。实现如下：

*/

class B {
protected:
	B() { }		// 为了统一，将构造函数也设为 protected
	~B() { }
public:
	static B* create() { return new B(); }
	void destory() { delete this; }
};

/*

增加create函数是为了让代码看起来更统一，调用create函数在堆上创建类A对象，调用destory函数来释放内存。

*/

/*

只能静态分配：只有使用new运算符，对象才会被建立在堆上。因此只要限制new运算符就可以实现类对象只能建立在栈上。可以将new运算符设为私有。

*/

class C {
private:
	void* operator new(size_t t) { }          // 注意函数的第一个参数和返回值都是固定的  
	void operator delete(void* ptr) { }       // 重载了new就需要重载delete  
public:
	C() { }
	~C() { }
};

void driver()
{
	A* pA = new A();
	B* pB = B::create();
	C c;
}