#pragma once

/*

探讨C++中菱形继承问题，及其解决方法

假设我们有类B和类C，它们都继承了相同的类A。另外我们还有类D，类D通过多重继承机制继承了类B和类C。
因为形状类似于钻石（或者菱形），因此这个问题被形象地称为钻石问题（菱形继承问题）。

解决方法：
通过虚继承机制解决上述问题。虚继承的目的是令某个类做出声明，承诺愿意共享它的基类。其中，共享的基类子对象称为虚基类。
在这种情况下，不管虚基类在继承体系中出现了多少次，在派生类中都只包含唯一一个共享的虚基类子对象。

注意：虚派生只影响从指定了虚基类的派生类中进一步派生出的类，它不会影响派生类本身。

*/

#include <iostream>

using namespace std;

class Animal	// 基类  
{
private:
	int weight;

public:
	Animal(int weight_ = 10) : weight(weight_) { }

	int getWeight()
	{
		return weight; 
	};

};

//class Tiger : public Animal
class Tiger : virtual public Animal	// 虚基类机制，Animal为虚基类
{
public:
	Tiger(int weight_) : Animal(weight_) { }
};

//class Lion : public Animal
class Lion : virtual public Animal
{
public:
	Lion(int weight_) : Animal(weight_) { }
};

class Liger : public Tiger, public Lion
{
public:
	Liger(int weight_) : Tiger(weight_), Lion(weight_) { }
};

void driver()
{
	Liger liger(10);
	cout << "liger.getWeight() = " << liger.getWeight() << endl;
	cout << "sizeof(Animal) = " << sizeof(Animal) << endl;
	cout << "sizeof(Tiger) = " << sizeof(Tiger) << endl;
	cout << "sizeof(Lion) = " << sizeof(Lion) << endl;
	cout << "sizeof(Liger) = " << sizeof(Liger) << endl;
}

/*

liger.getWeight() = 10
sizeof(Animal) = 4
sizeof(Tiger) = 8
sizeof(Lion) = 8
sizeof(Liger) = 12
请按任意键继续. . .

*/