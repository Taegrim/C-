#include <iostream>

namespace test1 {
	void f() {
		std::cout << "Hello, World!\n";
	}
	void print() {
		std::cout << "Hi" << std::endl << "my name is ";
	}
}

namespace test2 {
	void f() {
		test1::f();
	}
	void print() {
		std::cout << "Psi" << std::endl;
	}
}

int main()
{
	test1::print();
	test2::print();
	test2::f();
}