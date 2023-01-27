#include "stdafx.h"

class A {
public:
	A() {
		std::cout << "자원 획득" << std::endl;
		m_size = 100;
		m_data = new int[m_size];
		for (int i = 0; i < m_size; ++i)
			m_data[i] = 0;
	}
	A(int size, int num) {
		std::cout << "자원 획득" << std::endl;
		m_size = size;
		m_data = new int[size];
		for (int i = 0; i < size; ++i)
			m_data[i] = num;
	}

	~A() {
		std::cout << "자원 해제" << std::endl;
		delete[] m_data;
	}

	void Some() { std::cout << "일반 포인와 동일하게 사용 가능" << std::endl; }
	void DoSomething(int a) {
		std::cout << "무언가를 한다" << std::endl;
		m_data[0] = a;
	}

	void Print() const {
		for (int i = 0; i < m_size; ++i)
			std::cout << m_data[i] << " ";
		std::cout << std::endl;
	}

private:
	int* m_data;
	int m_size;
};

void DoSomething()
{
	///std::unique_ptr<A> pa(new A());
	auto pa = std::make_unique<A>();
	std::cout << "pa : ";
	pa->Some();

	//std::unique_ptr<A> pb = std::move(pa);
	auto pb = std::move(pa);
	std::cout << "pb : ";
	pb->Some();
}

void DoSomeThing(A* ptr)
{
	ptr->DoSomething(3);
}

int main()
{
	DoSomething();

	std::cout << std::endl << "----- 함수 인자로 넘기기 -----" << std::endl;
	auto p = std::make_unique<A>();
	DoSomeThing(p.get());

	std::cout << "----- make_unique -----" << std::endl;
	auto ptr = std::make_unique<A>(10, 3);
	ptr->Print();

	std::cout << std::endl << "----- unique_ptr 컨테이너 -----" << std::endl;
	std::vector<std::unique_ptr<A>> v;
	v.push_back(std::move(p));
	v.push_back(std::move(ptr));
	v.emplace_back(new A(10, 5));

	for (const auto& p : v)
		p->Print();
}