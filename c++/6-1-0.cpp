#include "stdafx.h"

class Base {
public:
	Base() : parent_s{ "���" } { std::cout << "��� Ŭ����\n"; }

	void Print() { std::cout << parent_s << std::endl; }

protected:
	std::string parent_s;
};

class Derived : public Base {
public:
	Derived() : child_s{ "�Ļ�" } {
		std::cout << "�Ļ� Ŭ����\n"; 

		parent_s = "����";

		Print();
		Base::Print();
	}

	void Print() { std::cout << child_s << std::endl; }

private:
	std::string child_s;
};

int main()
{
	Base p;
	std::cout << "===================\n\n";
	Derived c;
}