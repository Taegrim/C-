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

	char At(int i) const;

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	bool operator==(const MyString& str);

private:
	char* string_content;
	int string_length;
	int memory_capacity;
};

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
	MyString str1("a word");
	MyString str2("sentence");
	MyString str3("sentence");

	if (str1 == str2)
		std::cout << "str1 과 str2 는 같다\n";
	else
		std::cout << "str1 과 str2 는 다르다\n";


	if (str2 == str3)
		std::cout << "str2 와 str3 는 같다\n";
	else
		std::cout << "str2 와 str3 는 다르다\n";
}