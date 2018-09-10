#pragma once

/*

面试题10：斐波那契数列

题目一：求斐波那契数列的第n项

写一个函数，输入n，求斐波那契数列的第n项

*/


#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

long long Fibonacci(unsigned int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

long long FibonacciDP(unsigned int n)
{
	long long arr[2];
	arr[0] = 0;
	arr[1] = 1;
	if (n < 2)
		return arr[n];
	int temp = 0;
	for (int i = 2; i <= n; ++i)
	{
		temp = arr[1];
		arr[1] = arr[0] + arr[1];
		arr[0] = temp;
	}
	return arr[1];
}

void test0()
{
	cout << "FibonacciDP()" << endl;
	auto t0 = std::chrono::high_resolution_clock::now();
	cout << FibonacciDP(45) << endl;
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";

	cout << "Fibonacci()" << endl;
	t0 = std::chrono::high_resolution_clock::now();
	cout << Fibonacci(45) << endl;
	t1 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
}

void driver()
{
	test0();
}