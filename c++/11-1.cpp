#include "stdafx.h"

class Parent : public std::exception {
public:
	virtual const char* what() const noexcept override { return "Parent!\n"; }
};

class Child : public Parent {
public:
	const char* what() const noexcept override { return "Child!\n"; }
};

int func(int c) {
	if (c == 1) {
		throw Parent();
	}
	else if (c == 2) {
		throw Child();
	}
	else if (c == 3) {
		throw std::runtime_error("error");
	}
	return 0;
}

int NoExceptFunc() noexcept
{
	// noexcept 함수에서 예외처리 시 
	// 런타임에서 프로그램이 종료됨

	//throw std::runtime_error("error");
	return 3;
}

int main()
{
	int c;
	std::cin >> c;


	// 부모클래스 catch 는 자식클래스 catch 뒤에 써야 함
	// 반대로 쓸 경우 자식클래스를 throw 하더라도
	// 부모클래스 Catch 문으로 들어감
	try {
		func(c);
	}
	catch (Child& c) {
		std::cout << "Child Catch!" << std::endl;
		std::cout << c.what();
	}
	catch (Parent& p) {
		std::cout << "Parent Catch!" << std::endl;
		std::cout << p.what();
	}
	catch (...) {
		std::cout << "Default Catch" << std::endl;
	}

	int i{};
	try {
		i = NoExceptFunc();
	}
	catch(...){
		std::cout << "Error" << std::endl;
	}
	
	std::cout << i << std::endl;
}