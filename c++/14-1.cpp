#include <functional>
#include <algorithm>
#include "stdafx.h"

int SomeFunc1(const std::string& s)
{
	std::cout << "Func1 호출 " << s << std::endl;
	return 0;
}

struct S {
	void operator()(char c) {
		std::cout << "Func2 호출 " << c << std::endl;
	}
};

class A {
public:
	A(int c) : c{ c } {}
	int SomeFunc() {
		std::cout << "비상수 함수: " << ++c << std::endl;
		return c;
	}

	int SomeConstFuncion() const {
		std::cout << "상수 함수 : " << c << std::endl;
		return c;
	}

	int SetNumber(int i) {
		c = i;
		std::cout << "변수 설정 " << c << std::endl;
		return c;
	}

private:
	int c;
};

int main()
{
	std::function<int(const std::string&)> f1 = SomeFunc1;
	std::function<void(char)> f2 = S();
	std::function<void()> f3 = []() {std::cout << "Func3 호출" << std::endl; };

	f1("hello");
	f2('c');
	f3();

	
	// &클래스이름::함수의 형태로 전달
	// 인자로 클래스를 받아야 함
	std::cout << std::endl << "멤버 함수를 가지는 function" << std::endl;
	A a(5);
	std::function<int(A&)> f4 = &A::SomeFunc;
	std::function<int(const A&)> f5 = &A::SomeConstFuncion;
	std::function<int(A&, int)> f6 = &A::SetNumber;

	f4(a);
	f5(a);
	f6(a, 10);


	// mem_fn 을 사용하면 멤버함수를 functional 객체로 만들어서 리턴함
	std::cout << std::endl << "멤버 함수들을 함수 객체로" << std::endl;
	std::vector<int> v1(1);
	std::vector<int> v2(2);
	std::vector<int> v3(3);
	std::vector<int> v4(4);

	std::vector<std::vector<int>> container;
	container.push_back(v2);
	container.push_back(v4);
	container.push_back(v1);
	container.push_back(v3);

	std::function<size_t(const std::vector<int>&)> size_func = &std::vector<int>::size;

	std::vector<int> size_v(4);
	/*std::transform(container.begin(), container.end(), size_v.begin(),
		size_func);*/
	std::transform(container.begin(), container.end(), size_v.begin(),
		std::mem_fn(&std::vector<int>::size));
	for (auto p = size_v.begin(); p != size_v.end(); ++p)
		std::cout << "벡터 크기 : " << *p << std::endl;
}