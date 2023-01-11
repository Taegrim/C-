#include "stdafx.h"

// 함수 템플릿
// 타입이 아닌 템플릿 인자
// 디폴트 템플릿 인자

template <typename T>
T max(T& a, T& b)
{
	return a > b ? a : b;
}

template <typename T>
struct Compare {
	bool operator()(const T& a, const T& b) const { return a < b; }
};

template <typename T, typename Comp = Compare<T>>
T Min(T& a, T& b)
{
	Comp comp;
	if (comp(a, b))
		return a;
	return b;
}

template <typename T, int num = 0>
T AddNum(T t)
{
	return t + num;
}

template <typename T>
void PrintArray(const T& arr)
{
	for (int i : arr)
		std::cout << i << " ";
	std::cout << std::endl;
}

int main()
{
	std::cout << "---------- 함수 템플릿 ----------" << std::endl;
	int a = 1;
	int b = 2;
	std::cout << std::format("Max ({}, {}) -> {}", a, b, max(a, b)) << std::endl;
	//std::cout << std::format("Max ({}, {}) -> {}", a, b, max<int>(a, b)) << std::endl;


	std::string s = "hello";
	std::string t = "world";
	std::cout << std::format("Max ({}, {}) -> {}", s, t, max(s, t)) << std::endl;


	std::cout << "---------- 타입이 아닌 템플릿 인자 ----------" << std::endl;
	int x = 3;
	std::cout << "x : " << AddNum<int, 5>(x) << std::endl;

	std::array<int, 5> arr{ 1,2,3,4,5 };
	PrintArray(arr);

	std::array<int, 7> arr2{ 1,2,3,4,5,6,7 };
	PrintArray(arr2);

	std::array<int, 3> arr3{ 1,2,3 };
	PrintArray(arr3);

	std::cout << "---------- 디폴트 템플릿 인자 ----------" << std::endl;
	int i = 3;
	int j = 5;
	std::cout << std::format("Min ({}, {}) -> {}", i, j, Min(i, j)) << std::endl;

	std::string s1 = "abc";
	std::string s2 = "def";
	std::cout << std::format("Min ({}, {}) -> {}", s1, s2, Min(s1, s2)) << std::endl;
}