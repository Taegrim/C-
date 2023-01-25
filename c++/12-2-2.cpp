#include "stdafx.h"

class A {
public:
	A() { std::cout << "생성자\n"; }
	A(const A& a) { std::cout << "복사 생성자\n"; }
	A(A&& a) noexcept { std::cout << "이동 생성자\n"; }
};

class B {
public:
	B(A&& a) : a_(std::move(a)) {}

	A a_;
};

int main()
{
	A a;
	std::cout << "B 생성\n";
	B b(std::move(a));
}