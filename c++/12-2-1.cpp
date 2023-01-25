#include "stdafx.h"

class A {
public:
	A() { std::cout << "일반 생성자 호출" << std::endl; }
	A(const A& a) { std::cout << "복사 생성자 호출" << std::endl; }
	A(A&& a) { std::cout << "이동 생성자 호출" << std::endl; }
};


class MyString {
public:
	MyString();
	MyString(char c);
	MyString(const char* str);

	MyString(const MyString& str);
	MyString(MyString&& str) noexcept;
	MyString& operator=(const MyString& str);
	MyString& operator=(MyString&& str) noexcept;

	~MyString();

	int Length() const { return string_length; }
	int Capacity() const { return memory_capacity; }
	void Reserve(int size);

	char At(int i) const;

	MyString operator+(const MyString& str);
	bool operator==(const MyString& str);
	char& operator[](const int index) { return string_content[index]; }

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
	char* string_content;
	int string_length;
	int memory_capacity;
};

MyString::MyString()
{
	std::cout << "생성자 호출 !" << std::endl;
	string_length = 0;
	memory_capacity = 0;
	string_content = nullptr;
}

MyString::MyString(char c)
{
	std::cout << "생성자 호출 !" << std::endl;
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
	memory_capacity = 1;
}

MyString::MyString(const char* str)
{
	std::cout << "생성자 호출 !" << std::endl;
	string_length = strlen(str);
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; ++i)
		string_content[i] = str[i];
}

MyString::MyString(const MyString& str)
{
	std::cout << "복사 생성자 호출 !" << std::endl;
	string_length = str.string_length;
	memory_capacity = str.string_length;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; ++i)
		string_content[i] = str.string_content[i];
}

MyString::MyString(MyString&& str) noexcept
{
	std::cout << "이동 생성자 호출 !" << std::endl;
	string_length = str.string_length;
	memory_capacity = str.memory_capacity;
	string_content = str.string_content;

	str.string_content = nullptr;
	str.memory_capacity = 0;
	str.string_length = 0;
}


MyString& MyString::operator=(const MyString& str)
{
	std::cout << "복사" << std::endl;
	if (str.string_length > memory_capacity) {
		delete[] string_content;
		string_content = new char[str.string_length];
		memory_capacity = str.string_length;
	}

	string_length = str.string_length;

	for (int i = 0; i < string_length; ++i)
		string_content[i] = str.string_content[i];

	return *this;
}

MyString& MyString::operator=(MyString&& str) noexcept
{
	std::cout << "이동" << std::endl;
	string_content = str.string_content;
	string_length = str.string_length;
	memory_capacity = str.memory_capacity;

	str.string_content = nullptr;
	str.memory_capacity = 0;
	str.string_length = 0;

	return *this;
}

MyString::~MyString()
{
	if (string_content)
		delete[] string_content;
}

char MyString::At(int i) const
{
	if (i >= string_length || i < 0)
		return 0;
	else
		return string_content[i];
}

void MyString::Reserve(int size)
{
	if (size > memory_capacity) {
		char* prev_string_content = string_content;

		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i < string_length; ++i)
			string_content[i] = prev_string_content[i];

		delete[] prev_string_content;
	}
}


MyString MyString::operator+(const MyString& s)
{
	MyString str;
	str.Reserve(string_length + s.string_length);
	for (int i = 0; i < string_length; ++i)
		str.string_content[i] = string_content[i];
	for (int i = 0; i < s.string_length; ++i)
		str.string_content[string_length + i] = s.string_content[i];
	str.string_length = string_length + s.string_length;

	return str;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	for (int i = 0; i < str.string_length; ++i)
		os << str.string_content[i];
	return os;
}

bool MyString::operator==(const MyString& str)
{
	if (string_length == str.string_length) {
		for (int i = 0; i < string_length; ++i)
			if (string_content[i] != str.string_content[i])
				return false;

		return true;
	}
	return false;
}


template <typename T>
void MySwap(T& a, T& b)
{
	T tmp(std::move(a));
	a = std::move(b);
	b = std::move(tmp);
}

int main()
{
	A a;

	A b(a);

	A c(std::move(a));

	std::cout << "-----------------" << std::endl << std::endl;

	MyString str1("abc");
	MyString str2("def");
	std::cout << "Swap 전 -----" << std::endl;
	std::cout << "str1 : " << str1 << std::endl;
	std::cout << "str2 : " << str2 << std::endl;

	std::cout << "Swap 후 -----" << std::endl;
	MySwap(str1, str2);
	std::cout << "str1 : " << str1 << std::endl;
	std::cout << "str2 : " << str2 << std::endl;
}