#include "stdafx.h"

class A {

public:
    A(int data) : data_(data) { std::cout << "일반 생성자 호출!" << std::endl; }

    A(const A& a) : data_(a.data_) {
        std::cout << "복사 생성자 호출!" << std::endl;
    }

    A(const A&& a) noexcept : data_(a.data_) {
        std::cout << "대입 생성자 호출! " << std::endl;
    }

private:
    int data_;
};

class MyString {
public:
	MyString();
	MyString(char c);
	MyString(const char* str);

	MyString(const MyString& str);
	MyString(MyString&& str) noexcept;

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
}

MyString::~MyString()
{
	if(string_content)
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


int main()
{
    A a(1);
    A b(a);


    A c(A(2));      // 컴파일러가 복사를 생략함



	std::cout << "-----" << std::endl;
	MyString str1("abc");
	MyString str2("def");

	std::cout << "-----" << std::endl;

	//MyString str3 = str1 + str2;
	// 컴파일러에서 최적화를 했는지 이동생성자 호출 X

	MyString str3(std::move(MyString(str1 + str2)));



	std::cout << "-----" << std::endl << std::endl;

	MyString s("abc");
	std::vector<MyString> v;
	v.resize(0);

	std::cout << "----- 첫 번째 원소 추가 -----" << std::endl;
	v.push_back(s);
	std::cout << "----- 두 번째 원소 추가 -----" << std::endl;
	v.push_back(s);
	std::cout << "----- 세 번째 원소 추가 -----" << std::endl;
	v.push_back(s);
	std::cout << "----- 네 번째 원소 추가 -----" << std::endl;
	v.emplace_back(std::move(s));
	std::cout << "----- 다섯 번째 원소 추가 -----" << std::endl;
	v.emplace_back("123");
}