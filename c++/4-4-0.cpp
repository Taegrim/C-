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

	int& c = a.AccessX();	// A�� ����x �� ����
	c = 4;
	a.ShowX();

	int d = a.AccessX();	// a�� ����x �� ������ ����
	d = 3;
	a.ShowX();

	/*int& e = a.GetX();
	e = 2;
	a.ShowX();*/
	// ���纻�� �����ϹǷ� ����

	int f = a.GetX();	// a�� �ӽ� ������x �� ������ ����
	f = 1;
	a.ShowX();
}