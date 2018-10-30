#pragma once

/*

求斐波那契数列的第一百万项

> Ref: https://www.zhihu.com/question/292320341/answer/

这结果有 208988 个十进位，应该需要
- 高精度整数运算
- 快速幂

*/

#include <iomanip>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

template<typename T>
int cntDigits(T num)
{
	int cnt = 0;
	while (num != 0)
	{
		num /= 10;
		++cnt;
	}
	return cnt;
}

// 高精度整数的加法和乘法的简单实现
template<typename T = std::uint64_t, T m = 1000000000ULL, unsigned places = 9>
class BigUint {
	std::vector<T> d;
public:
	BigUint() = default;
	BigUint(T x)
	{
		assert(x < m);
		d.push_back(x);
	}

	bool empty() const
	{
		return d.empty();
	}

	BigUint operator+(const BigUint& r) const
	{
		BigUint sum;
		T carry = 0;
		auto& e = r.d;
		auto n = std::max(d.size(), e.size());
		sum.d.reserve(n + 1);
		for (unsigned i = 0; i < n; ++i)
		{
			T a = i < d.size() ? d[i] : 0;
			T b = i < e.size() ? e[i] : 0;
			sum.d.push_back((a + b +carry) % m);
			carry = (a + b + carry) / m;
		}
		if (carry > 0)
			sum.d.push_back(carry);
		return sum;
	}

	BigUint operator*(const BigUint& r) const
	{
		BigUint product;
		auto& e = r.d;
		product.d.resize(d.size() + e.size());
		for (unsigned i = 0; i < d.size(); ++i)
		{
			for (unsigned j = 0; j < e.size(); ++j)
			{
				T temp = d[i] * e[j] + product.d[i + j];
				T lo = temp % m;
				T hi = temp / m;
				product.d[i + j] = lo;
				product.d[i + j + 1] += hi;
			}
		}
		while (product.d.size() > 1 && product.d.back() == 0)
			product.d.pop_back();
		return product;
	}
	friend std::ostream& operator<<(std::ostream& os, const BigUint& u)
	{
		int cnt_of_digits = 0;
		if (u.d.size() != 0)
			cnt_of_digits = cntDigits(u.d.back()) + (u.d.size() - 1) * places;
		os << cnt_of_digits << " digits" << endl;
			
		auto itr = u.d.rbegin();
		os << *itr++;
		while (itr != u.d.rend() && itr - u.d.rbegin() < 10)
			os << std::setfill('0') << std::setw(places) << *itr++;
		return os;
	}
};

// 斐波那契的矩阵形式
// https://en.wikipedia.org/wiki/Fibonacci_number#Matrix_form
template<typename T>
class Matrix22 {
public:
	Matrix22(T m00_, T m01_, T m10_, T m11_) : m00(m00_), m01(m01_), m10(m10_), m11(m11_) {}
	Matrix22 operator*(const Matrix22& r) const
	{
		return Matrix22(
			m00 * r.m00 + m01 * r.m10, m00 * r.m01 + m01 * r.m11, 
			m10 * r.m00 + m11 * r.m10, m10 * r.m01 + m11 * r.m11
		);
	}
	T m00, m01, m10, m11;
};

// 快速幂
template<typename T, typename I>
T power(const T& x, I n)
{
	if (n == 1)
		return x;
	else if (n % 2 == 0)
		return power(x * x, n / 2);
	else
		return x * power(x * x, (n - 1) / 2);
}

// 31043ms
void test0()
{
	int n = 1000000;
	auto t0 = std::chrono::high_resolution_clock::now();
	auto result = power(Matrix22<BigUint<>>{1, 1, 1, 0}, n - 1).m00;
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << result << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
}

// 通过 memoization 减少重复计算
// F[2n] = (F[n-1] + F[n+1]) * F[n]
// F[2n + 1] = F[n] * F[n] + F[n+1] * F[n+1]
static std::vector<BigUint<>> g_f = { 0,1,1,2 };
const BigUint<>& f(int n)
{
	if (!g_f[n].empty())
		return g_f[n];
	else if (n % 2 == 0)
		return g_f[n] = (f(n / 2 - 1) + f(n / 2 + 1)) * f(n / 2);
	else
		return g_f[n] = (f(n / 2) * f(n / 2) + f(n / 2 + 1) * f(n / 2 + 1));
}

// 6710ms
void test1()
{
	int n = 1000000;
	g_f.resize(n + 1);
	auto t0 = std::chrono::high_resolution_clock::now();
	auto result = f(n);
	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout << f(n) << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
}

void driver()
{
	test1();
}