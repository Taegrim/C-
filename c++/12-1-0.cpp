#include "stdafx.h"

// const T& 형태는 우측값 또한 받을 수 있음
int Plus(const int& a, const int& b)
{
	int temp{ a + b };
	return temp;
}

int main()
{
	int a{ 2 }, b{ 3 };

	std::cout << Plus(2, 3) << ", " << Plus(a, b) << std::endl;

	int c{ 5 };
	int& ref = c;
	int&& r_ref = 6;

	ref = 8;
	r_ref = 10;

	std::cout << ref << ", " << r_ref << std::endl;
}