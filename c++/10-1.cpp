#include "stdafx.h"

// STL  ( 컨테이너, 반복자, 알고리즘 )
// 컨테이너
//    - vector	
//    - list
//	  - deque

template <typename T>
void PrintVector(const std::vector<T>& v)
{
	for (int num : v)
		std::cout << num << std::endl;
	std::cout << std::endl;
}

template <typename T>
void DoubleAndPrint(std::vector<T>& v)
{
	for (auto& e : v) {
		e *= 2;
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
}

template <typename Iter>
void Print(Iter beg, Iter end)
{
	for (; beg != end; ++beg)
		std::cout << *beg << std::endl;
	std::cout << std::endl;
}

int main()
{
	std::cout << "------------ 벡터 --------------" << std::endl;
	std::vector<int> v;
	
	for (int i = 0; i < 4; ++i)
		v.push_back((i + 1) * 10);

	for (auto it = v.cbegin(); it != v.cend(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	for (auto it = v.begin(); it != v.end();) {
		if (*it == 20) {
			it = v.erase(it);
		}
		else {
			++it;
		}
	}

	Print(v.begin(), v.end());

	DoubleAndPrint(v);

	for (auto it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;


	std::cout << std::endl << std::endl;
	std::cout << "------------ 리스트 --------------" << std::endl;

	std::list<int> l;
	
	for(int i = 0; i < 4; ++i)
		l.push_back((i + 1) * 10);

	Print(l.begin(), l.end());

	for (auto it = l.begin(); it != l.end(); ++it)
		if (*it == 20)
			l.insert(it, 50);

	Print(l.begin(), l.end());

	for (auto it = l.begin(); it != l.end(); ++it)
		if (*it == 30)
			l.erase(it);

	Print(l.begin(), l.end());


	std::cout << std::endl << std::endl;
	std::cout << "------------   덱   --------------" << std::endl;

	std::deque<int> d;

	d.push_back(10);
	d.push_back(20);
	d.push_front(30);
	d.push_front(40);

	Print(d.begin(), d.end());
	d.pop_front();
	Print(d.begin(), d.end());
}