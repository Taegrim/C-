#include "stdafx.h"

// 템플릿 타입의 우측값 레퍼런스는 '보편적 레퍼런스' 로 
// 좌측값 또한 받을 수 있다
// 레퍼런스 겹침 (reference collapsing) 규칙에 의해 템플릿 타입을 추론한다
//  - &  의 &  -> 좌측값 레퍼런스
//  - &  의 && -> 좌측값 레퍼런스
//  - && 의 &  -> 좌측값 레퍼런스
//  - && 의 && -> 우측값 레퍼런스

template <typename T>
void Wrapper2(T&& u)
{
	g(std::forward<T>(u));
	// u 가 우측값 레퍼런스일 때만 move 를 적용한 것처럼 작동함
}

template <typename T>
void Wrapper(T&& u)
{
	g(u);
}

class A {
};

void g(A& a) { std::cout << "좌측값 레퍼런스 호출" << std::endl; }
void g(const A& a) { std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; }
void g(A&& a) { std::cout << "우측값 레퍼런스 호출" << std::endl; }


int main()
{
	A a;
	const A ca;

	std::cout << "----- 원본 -----" << std::endl;
	g(a);
	g(ca);
	g(A());

	std::cout << "----- Wrapper -----" << std::endl;
	Wrapper(a);
	Wrapper(ca);
	Wrapper(A());

	std::cout << "----- forward Wrapper -----" << std::endl;
	Wrapper2(a);
	Wrapper2(ca);
	Wrapper2(A());
}