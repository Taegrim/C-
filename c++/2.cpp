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

// 아래의 함수는 지역변수의 참조자를 리턴하므로
// 문제가 발생하는 함수, 아래 설명되어 있음
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
	std::cout << "주소 : " <<  &a << std::endl;
}

int main()
{

	// --------------------- 레퍼런스를 통한 값 바꾸기 ---------------------
	std::cout << "레퍼런스를 통한 값 바꾸기" << std::endl;

	int a{ 5 }, b{ 3 };
	std::cout << a << ", " << b << std::endl;
	change(a, b);
	std::cout << a << ", " << b << std::endl;

	int& ref_a = a;
	std::cout << "a : " << a << std::endl;
	ref_a = 8;
	std::cout << "a : " << a << std::endl << std::endl;
	

	// ---------------------- 레퍼런스의 레퍼런스 --------------------------
	std::cout << "레퍼런스의 레퍼런스" << std::endl;

	int x{};
	int& y = x;
	int& z = y;

	x = 1;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;

	y = 2;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;

	z = 3;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl << std::endl;


	// ------------------------- 상수 레퍼런스 ------------------------------
	std::cout << "상수 레퍼런스" << std::endl;

	//int& ref = 4;  X
	const int& my_ref = 4;
	int test_a{ my_ref };
	std::cout << "test_a : " << test_a << std::endl << std::endl;
	// 리터럴 메모리의 4를 참조하고 있음


	// ------------------- 레퍼런스 배열/배열 레퍼런스 ----------------------
	std::cout << "레퍼런스 배열 / 배열 레퍼런스" << std::endl;

	//int& arr[]{ a,b }; 불가능

	// 배열은 원소들을 주소로 찾아갈 수 있어야 함
	// 레퍼런스는 일반적으론 메모리 상에 없기 때문에 주소로 변환될 수 없음
	// 따라서 레퍼런스들의 배열은 불가능함

	int arr[]{ 1,2,3 };
	int(&ref_arr)[3] = arr;
	ref_arr[0] = 3;
	ref_arr[1] = 1;
	ref_arr[2] = 2;
	std::cout << ref_arr[0] << ref_arr[1] << ref_arr[2] << std::endl << std::endl;


	// ------------------------- 레퍼런스 리턴 -----------------------------
	std::cout << "함수에서 레퍼런스 리턴" << std::endl;
	// 함수에서 지역변수에 대한 레퍼런스를 리턴하는 것은
	// 해당 함수가 끝날 때 지역변수가 소멸하기 때문에
	// 이를 반환받는 변수는 해당 참조자가 사라져 오류가 발생함
	//  -> 댕글링 레퍼런스

	int c = function(a);
	std::cout << "a : " << a << " c : " << c << std::endl;
	c = 15;
	std::cout << "a : " << a << " c : " << c << std::endl;

	// int& d = test();
	// 위는 소멸하는 값을 참조하려 하기 대문에 댕글링 레퍼런스 문제 발생

	const int& d = test();
	std::cout << "d : " << d << std::endl;
	// 상수 레퍼런스는 예외적으로 함수의 지역변수를 참조값으로 받을 수 있음


	int& e = function(a);
	std::cout << "a : " << a << " e : " << e << std::endl;
	e = 33;
	std::cout << "a : " << a << " e : " << e << std::endl;

	// 함수에서 레퍼런스를 리턴할 때는 지역 변수의 레퍼런스를 리턴하지 않도록 주의해야 함
	// 함수의 매개변수로 레퍼런스를 사용하면 주소를 전달하기 위해 메모리가 사용됨

	// 함수의 매개변수로 레퍼런스를 넘기면 주소를 넘기는 형태
	int t = 3;
	std::cout << "주소 : " << &t << std::endl;
	test_print(t);
}