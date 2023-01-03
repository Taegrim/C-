#include "stdafx.h"

// ----------------------------------
// WRAPPER 클래스
// 타입변환 연산자
// 전위, 후위 증감 연산자

// 2개의 객체가 동등한 이항 연산자는 클래스 외부에서 정의
// 동등하지 않은 이항 연산, 단항연산, 아래의 연산자는 멤버함수로 정의
// [] (첨자), -> (멤버접근), = (대입),  () (함수호출) 연산자는 멤버함수로만 정의 가능

class Int {
public:
	Int(int data) :data{ data } {}

	operator int() { return data; }		// 리턴타입 X

	Int& operator++() {
		++data;
		return *this;
	}
	Int& operator--() {
		--data;
		return *this;
	}

	Int operator++(int) {
		Int temp{ *this };
		data++;
		return temp;
	}
	Int operator--(int) {
		Int temp{ *this };
		data--;
		return temp;
	}

private:
	int data;
};

int main()
{
	Int x = 3;
	int a = x + 4;

	x = a * 2 + x + 4;		// 디폴트 대입 연산자가 처리함

	std::cout << ++x << std::endl;
	std::cout << x++ << std::endl;
	std::cout << x << std::endl;

	std::cout << --x << std::endl;
	std::cout << x-- << std::endl;
	std::cout << x << std::endl;

}