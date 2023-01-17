#include <algorithm>
#include "stdafx.h"

template <typename Iter>
void Print(Iter begin, Iter end)
{
	while (begin != end) {
		std::cout << *begin << " ";
		++begin;
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	std::vector<int> vec2{ vec.begin(), vec.end() };
	std::vector<int> vec3 = vec2;


	std::cout << "remove - erase" << std::endl;
	Print(vec.begin(), vec.end());
	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
	Print(vec.begin(), vec.end());



	std::cout << std::endl << "홀수만 제거" << std::endl;
	
	[](int i) -> bool {return i % 2; }; // 람다 다른 표기법
	// 클래스의 멤버변수를 캡쳐하려면 멤버변수가 아닌 this 포인터로
	// 클래스를 캡쳐해야 함

	int num_erased{};
	vec2.erase(std::remove_if(vec2.begin(), vec2.end(),
						[&num_erased](int i) {
							if (num_erased >= 2)
								return false;
							else if (i % 2 == 1) {
								++num_erased;
								return true;
							}
							return false;
						}),
				vec2.end());
	Print(vec2.begin(), vec2.end());




	std::cout << std::endl << "벡터 전체에 1을 더함" << std::endl;

	std::vector<int> vec4(vec3.size());

	std::transform(vec3.begin(), vec3.end(), vec4.begin(),
				[](int i) {return i + 1; });
	Print(vec3.begin(), vec3.end());
	Print(vec4.begin(), vec4.end());
}