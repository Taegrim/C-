#include "stdafx.h"

class MyString {
	char* str;
	int len;

public:
	MyString(char c, int n);  // ���� c �� n �� �ִ� ���ڿ��� ����
	MyString(const char* s);
	MyString(const std::string& s);
	~MyString();

	void AddString(const std::string& s);   // str �ڿ� s �� ���δ�.
	void CopyString(const std::string& s);  // str �� s �� �����Ѵ�.
	int strlen() const;                       // ���ڿ� ���� ����

	friend std::ostream& operator<<(std::ostream& os, const MyString& s);
};

std::ostream& operator<<(std::ostream& os, const MyString& s)
{
	for (int i = 0; i < s.len; ++i)
		os << s.str[i];
	return os;
}


MyString::MyString(char c, int n)
{
	len = n;
	str = new char[len + 1];
	for (int i = 0; i < len; ++i)
		str[i] = c;
	str[len] = '\0';
}

MyString::MyString(const char* s)
{
	len = std::strlen(s);
	str = new char[len + 1];
	strcpy_s(str, static_cast<size_t>(len + 1), s);
}

MyString::MyString(const std::string& s)
{
	len = s.size();
	str = new char[len + 1];
	strcpy_s(str, static_cast<size_t>(len + 1), s.c_str());
}

MyString::~MyString()
{
	if (len > 0)
		delete[] str;
}

void MyString::AddString(const std::string& s)
{
	
	char* c = new char[len + s.size() + 1];
	memcpy(c, str, len);
	memcpy(c + len, s.c_str(), s.size() + 1);
	
	if(len > 0)			// ���� �迭 ����
		delete[] str;
	
	len += s.size();

	str = c;			// ���� �ø� �迭 ����Ŵ
}

void MyString::CopyString(const std::string& s)
{
	if (len > 0)
		delete[] str;

	len = s.size();
	char* c = new char[len + 1];
	strcpy_s(c, static_cast<size_t>(len + 1), s.c_str());
	
	str = c;
}

int MyString::strlen() const
{
	return len;
}

int main()
{
	MyString a{ 'A', 3 };
	MyString b{ "ASDB" };
	MyString c{ std::string{"My string!"}};
	std::string d{ "Hello!" };
	std::cout << a << ", " << b << ", " << c << ", " << d << std::endl;


	c.AddString(d);
	std::cout << a << ", " << b << ", " << c << ", " << d << std::endl;
	std::cout << "c �� ���� : " << c.strlen() << std::endl;


	c.CopyString(d);
	std::cout << a << ", " << b << ", " << c << ", " << d << std::endl;
	std::cout << "c �� ���� : " << c.strlen() << std::endl;
}