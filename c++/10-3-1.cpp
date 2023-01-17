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

class User {
public:
	User(std::string name, int age) : name(name), age(age) {}
	
	bool operator<(const User& u) const { return age < u.age; }

	friend std::ostream& operator<<(std::ostream& os, const User& u);

private:
	std::string name;
	int age;
};

std::ostream& operator<<(std::ostream& os, const User& u) {
	os << "[" << u.name << ", " << u.age << "]";
	return os;
}

int main()
{
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(2);

	std::vector<int> vec2(vec);


	Print(vec.begin(), vec.end());
	std::sort(vec.begin(), vec.end(), std::greater<int>());
	Print(vec.begin(), vec.end());



	std::cout << std::endl << std::endl << "partial sort" << std::endl;

	std::partial_sort(vec2.begin(), vec2.begin() + 3, vec2.end());
	Print(vec2.begin(), vec2.end());



	// 정렬하지만 처음에 원소를 넣은 순서를 유지함
	std::cout << std::endl << std::endl << "stable sort" << std::endl;
	
	std::vector<User> v;
	for (int i = 0; i < 100; ++i) {
		std::string name = "";
		name.push_back('a' + i / 26);
		name.push_back('a' + i % 26);
		v.push_back(User(name, static_cast<int>(rand() % 10)));
	}

	std::vector<User> v2 = v;

	std::cout << std::endl << "--- 정렬 전 ---" << std::endl;
	Print(v.begin(), v.end());
	std::sort(v.begin(), v.end());
	

	std::cout << std::endl << "--- 정렬 후 ---" << std::endl;
	Print(v.begin(), v.end());
	

	std::cout << std::endl << "--- stable sort ---" << std::endl;
	std::stable_sort(v2.begin(), v2.end());
	Print(v2.begin(), v2.end());
}