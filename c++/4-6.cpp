#include "stdafx.h"

class MyString {
public:
	explicit MyString(int capacity);
	MyString(const char* str);
	MyString(const MyString& str);
	~MyString();

	int Length() const {
		return string_length; 
	}

	void Print() const {
		test_int = 11;
		std::cout << *this << std::endl;
		std::cout << "mutable 멤버 변수 : " << test_int << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& os, const MyString str);

private:
	char* string_content;
	int string_length;
	int memory_capacity;

	mutable int test_int = 0;
};

std::ostream& operator<<(std::ostream& os, const MyString str)
{
	for (int i = 0; i < str.string_length; ++i)
		os << str.string_content[i];
	return os;
}

MyString::MyString(int capacity)
{
	string_content = new char[capacity];
	string_length = 0;
	memory_capacity = capacity;
	test_int = 5;
	std::cout << "문자열 수용량 : " << capacity << std::endl;
}

MyString::MyString(const char* str)
{
	string_length = strlen(str);
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; ++i)
		string_content[i] = str[i];
}

MyString::MyString(const MyString& str)
{
	string_length = str.string_length;
	memory_capacity = str.string_length;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; ++i)
		string_content[i] = str.string_content[i];
}

MyString::~MyString()
{
	delete[] string_content;
}

void Do(MyString s)
{
	std::cout << "문자열 작업 함수\n";
	return ;
}

int main()
{
	MyString s(3);

	MyString s2("hello");
	s2.Print();

}