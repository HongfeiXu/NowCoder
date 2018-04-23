#pragma once

/*

̽��C++�����μ̳����⣬����������

������������B����C�����Ƕ��̳�����ͬ����A���������ǻ�����D����Dͨ�����ؼ̳л��Ƽ̳�����B����C��
��Ϊ��״��������ʯ���������Σ������������ⱻ����س�Ϊ��ʯ���⣨���μ̳����⣩��

���������
ͨ����̳л��ƽ���������⡣��̳е�Ŀ������ĳ����������������ŵԸ�⹲�����Ļ��ࡣ���У�����Ļ����Ӷ����Ϊ����ࡣ
����������£�����������ڼ̳���ϵ�г����˶��ٴΣ����������ж�ֻ����Ψһһ�������������Ӷ���

ע�⣺������ֻӰ���ָ�����������������н�һ�����������࣬������Ӱ�������౾��

*/

#include <iostream>

using namespace std;

class Animal	// ����  
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
class Tiger : virtual public Animal	// �������ƣ�AnimalΪ�����
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
�밴���������. . .

*/