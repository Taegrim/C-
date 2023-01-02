#include "stdafx.h"
#include <stdlib.h>

class Complex {
public:
	Complex(double real, double img) : real{ real }, img{ img } {}
	Complex(const char* str);

	Complex(const Complex& c) = default;
	Complex& operator=(const Complex& c);

	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	Complex operator+(const char* str) const;
	Complex operator-(const char* str) const;
	Complex operator*(const char* str) const;
	Complex operator/(const char* str) const;

	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

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

Complex Complex::operator+(const Complex& c) const
{
	Complex temp{ real + c.real, img + c.img };
	return temp;
}

Complex Complex::operator-(const Complex& c) const
{
	Complex temp{ real - c.real, img - c.img };
	return temp;
}

Complex Complex::operator*(const Complex& c) const
{
	Complex temp{ real * c.real - img * c.img, real * c.img + img * c.real };
	return temp;
}

Complex Complex::operator/(const Complex& c) const
{
	Complex temp{
		(real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
		(img * c.real - real * c.img) / (c.real * c.real + c.img * c.img) };
	return temp;
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

Complex Complex::operator+(const char* str) const
{
	Complex temp{ str };
	return (*this) + temp;
}

Complex Complex::operator-(const char* str) const
{
	Complex temp{ str };
	return (*this) - temp;
}

Complex Complex::operator*(const char* str) const
{
	Complex temp{ str };
	return (*this) * temp;
}

Complex Complex::operator/(const char* str) const
{
	Complex temp{ str };
	return (*this) / temp;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << std::format("({0}, {1})\n", c.real, c.img);
	return os;
}

double Complex::GetNumber(const char* str, int from, int to) const
{
	//bool minus = false;

	//if (from > to) 
	//	return 0;
	//if ('-' == str[from])
	//	minus = true;
	//if ('-' == str[from] || '+' == str[from])
	//	++from;

	//double num{ 0.0 }, decimal{ 1.0 };

	//bool integer_part = true;
	//for (int i = from; i <= to; ++i) {
	//	if (isdigit(str[i]) && integer_part) {
	//		num *= 10.0;
	//		num += (str[i] - '0');
	//	}
	//	else if (str[i] == '.')
	//		integer_part = false;
	//	else if (isdigit(str[i]) && !integer_part) {
	//		decimal /= 10.0;
	//		num += ((str[i] - '0') * decimal);
	//	}
	//	else
	//		break;

	//}
	//if (minus)
	//	num *= -1.0;

	//return num;

	std::string s;
	for (int i = from; i < to; ++i)
		s += str[i];

	return atof(s.c_str());
}

int main()
{
	Complex a{ 1.0, 2.0 };
	Complex b{ 3.0, -2.0 };
	Complex c{ 0.0, 0.0 };
	
	c = a * b + a / b + a + b;
	a += b;

	std::cout << a << b << c;


	Complex d{ 0.0, 0.0 };
	d = d + "-1.1 + i3.923";
	std::cout << d;

	d = d - "1.2 - i1.823";
	std::cout << d;

	d = d * "2.3+i22";
	std::cout << d;

	d = d / "-12+i55";
	std::cout << d;
}