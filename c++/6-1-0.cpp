#include "stdafx.h"

class Base {
public:
	Base() : parent_s{ "기반" } { std::cout << "기반 클래스\n"; }

	void Print() { std::cout << parent_s << std::endl; }

protected:
	std::string parent_s;
};

class Derived : public Base {
public:
	Derived() : child_s{ "파생" } {
		std::cout << "파생 클래스\n"; 

		parent_s = "변경";

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