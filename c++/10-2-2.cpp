#include "stdafx.h"
#include <map>

// STL 컨테이너 - map


template <typename K, typename V>
void Print(const std::map<K, V>& m)
{
	// 구조적 바인딩
	for (const auto [name, era] : m)
		std::cout << name << " " << era << std::endl;
}

template <typename K, typename V>
void SearchAndPrint(const std::map<K, V>& m, const K& key)
{
	auto p = m.find(key);
	if (p != m.end())
		std::cout << key << " --> " << p->second << std::endl;
	else
		std::cout << key << "은(는) 목록에 업습니다" << std::endl;
}

// const 를 사용하면 m[key] 사용불가
template <typename K, typename V>
void SearchAndPrint(std::map<K, V>& m, const K& key)
{
	if (m.contains(key))
		std::cout << key << " --> " << m[key] << std::endl;
	else
		std::cout << key << "은(는) 목록에 업습니다" << std::endl;
}

int main()
{
	std::map<std::string, double> pitcher_list;

	pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
	pitcher_list.insert(std::pair<std::string, double>("해커 ", 2.93));
	pitcher_list.insert(std::pair<std::string, double>("피어밴드 ", 2.95));


	pitcher_list.insert(std::make_pair("차우찬", 3.04));
	pitcher_list.insert(std::make_pair("장원준 ", 3.05));
	pitcher_list.insert(std::make_pair("헥터 ", 3.09));

	pitcher_list["니퍼트"] = 3.56;
	pitcher_list["박종훈"] = 3.76;
	pitcher_list["켈리"] = 3.90;

	Print(pitcher_list);

	std::cout << "-------------------------" << std::endl;

	SearchAndPrint(pitcher_list, std::string("박세웅"));
	SearchAndPrint(pitcher_list, std::string("류현진"));
	
}