#include "stdafx.h"

class MyString {
public:
	MyString(char c);
	MyString(const char* str);
	MyString(const MyString& str);
	~MyString();

	int Length() const { return string_length; }
	int Capacity() const { return memory_capacity; }
	void Reserve(int size);

	MyString& Assign(const MyString& str);
	MyString& Assign(const char* str);

	MyString& Insert(int loc, const char* str);
	MyString& Insert(int loc, char c);
	MyString& Insert(int loc, const MyString& str);

	MyString& Erase(int loc, int num);

	int Find(int find_from, MyString& str) const;
	int Find(int find_from, const char* str) const;
	int Find(int find_from, char c) const;

	int Compare(const MyString& str) const;

	char At(int i) const;

	friend std::ostream& operator<<(std::ostream& os, const MyString str);
	
private:
	char* string_content;
	int string_length;
	int memory_capacity;
};

std::ostream& operator<<(std::ostream& os, const MyString str)
{
	for (int i = 0; i < str.string_length; ++i)
		os << str.string_content[i];
	return os;
}

MyString::MyString(char c) 
{
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
	memory_capacity = 1;
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

MyString& MyString::Assign(const MyString& str) 
{
	if (str.string_length > memory_capacity) {
		delete[] string_content;
		string_content = new char[str.string_length];
		memory_capacity = str.string_length;
	}

	for (int i = 0; i < str.string_length; ++i) 
		string_content[i] = str.string_content[i];

	string_length = str.string_length;

	return *this;
}

MyString& MyString::Assign(const char* str) 
{
	int str_length = strlen(str);

	if (str_length > memory_capacity) {
		delete[] string_content;

		string_content = new char[str_length];
		memory_capacity = str_length;
	}

	for (int i = 0; i < str_length; ++i)
		string_content[i] = str[i];
	
	string_length = str_length;

	return *this;
}

MyString& MyString::Insert(int loc, const char* str)
{
	MyString temp(str);
	return Insert(loc, temp);
}

MyString& MyString::Insert(int loc, char c) 
{
	MyString temp(c);
	return Insert(loc, temp);
}

MyString& MyString::Insert(int loc, const MyString& str) 
{
	if (loc < 0 || loc > string_length) return *this;

	if (string_length + str.string_length > memory_capacity) {
		if (memory_capacity * 2 > string_length + str.string_length)
			memory_capacity *= 2;
		else
			memory_capacity = string_length + str.string_length;

		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];


		for (int i = 0; i < loc; ++i) 
			string_content[i] = prev_string_content[i];
		

		for (int j = 0; j != str.string_length; ++j) 
			string_content[loc + j] = str.string_content[j];
		

		for (int i = loc; i < string_length; ++i) 
			string_content[str.string_length + i] = prev_string_content[i];
		

		delete[] prev_string_content;

		string_length = string_length + str.string_length;
		return *this;
	}

	for (int i = string_length - 1; i >= loc; --i) 
		string_content[i + str.string_length] = string_content[i];
	
	for (int i = 0; i < str.string_length; ++i)
		string_content[i + loc] = str.string_content[i];

	string_length = string_length + str.string_length;
	return *this;
}

MyString& MyString::Erase(int loc, int num) 
{
	if (num < 0 || loc < 0 || loc > string_length)
		return *this;

	for (int i = loc + num; i < string_length; ++i)
		string_content[i - num] = string_content[i];


	// 사용자가 문자열 크기보다 더 많이 지우려 하면
	// loc 뒤로는 없다고 볼 수 있음
	if (loc + num > string_length)
		string_length = loc;
	else
		string_length -= num;

	return *this;
}

int MyString::Find(int find_from, MyString& str) const
{
	if (str.string_length == 0) 
		return -1;

	int i, j;
	for (i = find_from; i <= string_length - str.string_length; ++i) {
		for (j = 0; j < str.string_length; ++j) 
			if (string_content[i + j] != str.string_content[j]) break;

		if (j == str.string_length) 
			return i;
	}

	return -1; 
}

int MyString::Find(int find_from, const char* str) const 
{
	MyString temp(str);
	return Find(find_from, temp);
}

int MyString::Find(int find_from, char c) const 
{
	MyString temp(c);
	return Find(find_from, temp);
}

int MyString::Compare(const MyString& str) const 
{
	for (int i = 0; i < std::min(string_length, str.string_length); ++i) {
		if (string_content[i] > str.string_content[i])
			return 1;

		else if (string_content[i] < str.string_content[i])
			return -1;
	}

	if (string_length == str.string_length) return 0;

	else if (string_length > str.string_length)
		return 1;

	return -1;
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

int main()
{
	MyString str1("매우 매우 매우 매우 긴 문자열");
	MyString str2("<사이에 삽입될 문자열>");
	str1.Reserve(30);

	std::cout << "문자열 수용량 : " << str1.Capacity() << std::endl;
	std::cout << "문자열 길이   : " << str1.Length() << std::endl;
	std::cout << str1 << std::endl;

	str1.Insert(5, str2);
	std::cout << str1 << std::endl;

	std::cout << "문자열 수용량 : " << str1.Capacity() << std::endl;
	std::cout << "문자열 길이   : " << str1.Length() << std::endl;
	std::cout << str1 << std::endl << std::endl;

	std::cout << "첫번째 \"매우\" 위치 : " << str1.Find(0, "매우") << std::endl;
	std::cout << "두번째 \"매우\" 위치 : " <<
		str1.Find(str1.Find(0, "매우") + 1, "매우") << std::endl << std::endl;


	MyString str3("abcdef");
	MyString str4("abcde");
	std::cout << "문자열 3, 4 비교 : " << str3.Compare(str4) << std::endl << std::endl;

	str3.Erase(2, 5);
	std::cout << str3 << std::endl;
	str4.Erase(2, 5);
	std::cout << str4 << std::endl;
}