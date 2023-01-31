#include <functional>
#include "stdafx.h"

void Add(int x, int y)
{
	std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void Subtract(int x, int y) {
	std::cout << x << " - " << y << " = " << x - y << std::endl;
}

struct S {
	int data;
	S(int data) : data{ data } { std::cout << "일반 생성자" << std::endl; }
	S(const S& s) {
		std::cout << "복사 생성자" << std::endl;
		data = s.data;
	}
	S(S&& s) {
		std::cout << "이동 생성자" << std::endl;
		data = s.data;
	}
};

void DoSomething(S& s1, const S& s2)
{
	s1.data = s2.data + 3;
}

int main()
{
	// 원래 함수에 특정 인자를 붙임
	std::cout << "bind" << std::endl;

	// 인자를 2개 받는 함수에서 첫번째 인자는 2로,
	// 두번째 인자는 함수 객체의 첫번째 인자를 두번째 인자로 넘김
	auto add_with_2 = std::bind(Add, 2, std::placeholders::_1);
	add_with_2(3);
	add_with_2(3, 4, 5);
	// 여러 인자를 전달해도 무시됨

	// 첫번째 인자는 함수 객체의 첫번째 인자를 첫번째 인자로,
	// 두번째인자는 2로 넘겨줌
	auto subtract_from_2 = std::bind(Subtract, std::placeholders::_1, 2);

	// 함수 = 기존의 함수
	// 함수 객체 = bind 로 만들어진 함수 객체
	// 함수의 두번째 인자는 함수 객체의 첫번째 인자로
	// 함수의 첫번째 인자는 함수 객체의 두번째 인자로 넘김
	auto negate = std::bind(Subtract, std::placeholders::_2, std::placeholders::_1);

	subtract_from_2(3);
	negate(4, 2);

	std::cout << std::endl << std::endl;

	S s1(1), s2(2);

	std::cout << "Before : " << s1.data << std::endl;

	// 명시적으로 std::ref 를 사용하지 않으면 s1 의 복사본이 전달됨
	// const 레퍼런스는 std::cref 를 사용
	auto do_something_with_s1 = std::bind(DoSomething, std::ref(s1), std::placeholders::_1);
	do_something_with_s1(s2);

	std::cout << "After : " << s1.data << std::endl;
}