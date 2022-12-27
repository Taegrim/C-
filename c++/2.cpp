#include <iostream>

int* point{};

void change(int &a, int &b)
{
	int temp{ a };
	a = b;
	b = temp;
}

int test()
{
	int a = 21;
	return a;
}

// �Ʒ��� �Լ��� ���������� �����ڸ� �����ϹǷ�
// ������ �߻��ϴ� �Լ�, �Ʒ� ����Ǿ� ����
int& func(int a)
{
	a = 2;
	return a;
}

int& function(int& a)
{
	a = 11;
	return a;
}

void test_print(int& a)
{
	std::cout << "�ּ� : " <<  &a << std::endl;
}

int main()
{

	// --------------------- ���۷����� ���� �� �ٲٱ� ---------------------
	std::cout << "���۷����� ���� �� �ٲٱ�" << std::endl;

	int a{ 5 }, b{ 3 };
	std::cout << a << ", " << b << std::endl;
	change(a, b);
	std::cout << a << ", " << b << std::endl;

	int& ref_a = a;
	std::cout << "a : " << a << std::endl;
	ref_a = 8;
	std::cout << "a : " << a << std::endl << std::endl;
	

	// ---------------------- ���۷����� ���۷��� --------------------------
	std::cout << "���۷����� ���۷���" << std::endl;

	int x{};
	int& y = x;
	int& z = y;

	x = 1;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;

	y = 2;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;

	z = 3;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl << std::endl;


	// ------------------------- ��� ���۷��� ------------------------------
	std::cout << "��� ���۷���" << std::endl;

	//int& ref = 4;  X
	const int& my_ref = 4;
	int test_a{ my_ref };
	std::cout << "test_a : " << test_a << std::endl << std::endl;
	// ���ͷ� �޸��� 4�� �����ϰ� ����


	// ------------------- ���۷��� �迭/�迭 ���۷��� ----------------------
	std::cout << "���۷��� �迭 / �迭 ���۷���" << std::endl;

	//int& arr[]{ a,b }; �Ұ���

	// �迭�� ���ҵ��� �ּҷ� ã�ư� �� �־�� ��
	// ���۷����� �Ϲ������� �޸� �� ���� ������ �ּҷ� ��ȯ�� �� ����
	// ���� ���۷������� �迭�� �Ұ�����

	int arr[]{ 1,2,3 };
	int(&ref_arr)[3] = arr;
	ref_arr[0] = 3;
	ref_arr[1] = 1;
	ref_arr[2] = 2;
	std::cout << ref_arr[0] << ref_arr[1] << ref_arr[2] << std::endl << std::endl;


	// ------------------------- ���۷��� ���� -----------------------------
	std::cout << "�Լ����� ���۷��� ����" << std::endl;
	// �Լ����� ���������� ���� ���۷����� �����ϴ� ����
	// �ش� �Լ��� ���� �� ���������� �Ҹ��ϱ� ������
	// �̸� ��ȯ�޴� ������ �ش� �����ڰ� ����� ������ �߻���
	//  -> ��۸� ���۷���

	int c = function(a);
	std::cout << "a : " << a << " c : " << c << std::endl;
	c = 15;
	std::cout << "a : " << a << " c : " << c << std::endl;

	// int& d = test();
	// ���� �Ҹ��ϴ� ���� �����Ϸ� �ϱ� �빮�� ��۸� ���۷��� ���� �߻�

	const int& d = test();
	std::cout << "d : " << d << std::endl;
	// ��� ���۷����� ���������� �Լ��� ���������� ���������� ���� �� ����


	int& e = function(a);
	std::cout << "a : " << a << " e : " << e << std::endl;
	e = 33;
	std::cout << "a : " << a << " e : " << e << std::endl;

	// �Լ����� ���۷����� ������ ���� ���� ������ ���۷����� �������� �ʵ��� �����ؾ� ��
	// �Լ��� �Ű������� ���۷����� ����ϸ� �ּҸ� �����ϱ� ���� �޸𸮰� ����

	// �Լ��� �Ű������� ���۷����� �ѱ�� �ּҸ� �ѱ�� ����
	int t = 3;
	std::cout << "�ּ� : " << &t << std::endl;
	test_print(t);
}