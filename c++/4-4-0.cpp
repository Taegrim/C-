#include "stdafx.h"

class A {
public:
	A(int c) : x{ c } {}

	int& AccessX() { return x; }
	int GetX() const { return x; }
	void ShowX() const { std::cout << x << std::endl; }

private:
	int x;
};

int main()
{
	A a{ 5 };
	a.ShowX();

	int& c = a.AccessX();	// A의 원본x 를 참조
	c = 4;
	a.ShowX();

	int d = a.AccessX();	// a의 원본x 를 값으로 받음
	d = 3;
	a.ShowX();

	/*int& e = a.GetX();
	e = 2;
	a.ShowX();*/
	// 복사본을 참조하므로 오류

	int f = a.GetX();	// a의 임시 생성된x 를 값으로 받음
	f = 1;
	a.ShowX();
}