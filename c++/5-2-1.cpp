#include "stdafx.h"
#include <stdlib.h>

// ----------------------------------
// lhs, rhs를 받는 연산자 오버로딩, friend 키워드

class Complex {
public:
	Complex(double real, double img) : real{ real }, img{ img } {}
	Complex(const char* str);

	Complex(const Complex& c) = default;
	Complex& operator=(const Complex& c);

	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	friend Complex operator+(const Complex& lhs, const Complex& rhs);
	friend Complex operator-(const Complex& lhs, const Complex& rhs);
	friend Complex operator*(const Complex& lhs, const Complex& rhs);
	friend Complex operator/(const Complex& lhs, const Complex& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Complex& c);

private:
	double real, img;

	double GetNumber(const char* str, int from, int to) const;
};

Complex::Complex(const char* str)
{
	int beg{};
	int end{ static_cast<int>(strlen(str)) };
	real = 0.0;
	img = 0.0;

	int pos_i{ -1 };
	for (int i = 0; i < end; ++i) {
		if (str[i] == 'i') {
			pos_i = i;
			break;
		}
	}

	if (-1 == pos_i) {
		real = GetNumber(str, beg, end);

		return;
	}

	real = GetNumber(str, beg, pos_i);
	img = GetNumber(str, pos_i + 1, end);

	// i 부호 바로 앞이 '-' 가 아니면 이를 찾음
	if (pos_i >= 1) {
		while (pos_i > 0) {
			if (' ' == str[pos_i - 1])
				--pos_i;
			else if ('-' == str[pos_i - 1]) {
				img *= -1.0;
				break;
			}
			else
				break;
		}
	}

}

Complex& Complex::operator=(const Complex& c)
{
	real = c.real;
	img = c.img;
	return *this;
}

Complex& Complex::operator+=(const Complex& c)
{
	(*this) = (*this) + c;
	return *this;
}

Complex& Complex::operator-=(const Complex& c)
{
	(*this) = (*this) - c;
	return *this;
}

Complex& Complex::operator*=(const Complex& c)
{
	(*this) = (*this) * c;
	return *this;
}

Complex& Complex::operator/=(const Complex& c)
{
	(*this) = (*this) / c;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << std::format("({0}, {1})\n", c.real, c.img);
	return os;
}

double Complex::GetNumber(const char* str, int from, int to) const
{
	std::string s;
	for (int i = from; i < to; ++i)
		s += str[i];

	return atof(s.c_str());
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex temp{ lhs.real + rhs.real, lhs.img + rhs.img };
	return temp;
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex temp{ lhs.real - rhs.real, lhs.img - rhs.img };
	return temp;
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex temp{ lhs.real * rhs.real - lhs.img * rhs.img, lhs.real * rhs.img + lhs.img * rhs.real };
	return temp;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex temp{
		(lhs.real * rhs.real + lhs.img * rhs.img) / (rhs.real * rhs.real + rhs.img * rhs.img),
		(lhs.img * rhs.real - lhs.real * rhs.img) / (rhs.real * rhs.real + rhs.img * rhs.img) };
	return temp;
}

int main()
{
	Complex a{ 0.0, 0.0 };
	a = "-1.1 + i3.923" + a;
	a = a + a;
	std::cout << a;

	Complex b{ 1,2 };
	b = a + b;
	std::cout << b;
}