#include "stdafx.h"

// ----------------------------------
// WRAPPER Ŭ����
// Ÿ�Ժ�ȯ ������
// ����, ���� ���� ������

// 2���� ��ü�� ������ ���� �����ڴ� Ŭ���� �ܺο��� ����
// �������� ���� ���� ����, ���׿���, �Ʒ��� �����ڴ� ����Լ��� ����
// [] (÷��), -> (�������), = (����),  () (�Լ�ȣ��) �����ڴ� ����Լ��θ� ���� ����

class Int {
public:
	Int(int data) :data{ data } {}

	operator int() { return data; }		// ����Ÿ�� X

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

	x = a * 2 + x + 4;		// ����Ʈ ���� �����ڰ� ó����

	std::cout << ++x << std::endl;
	std::cout << x++ << std::endl;
	std::cout << x << std::endl;

	std::cout << --x << std::endl;
	std::cout << x-- << std::endl;
	std::cout << x << std::endl;

}