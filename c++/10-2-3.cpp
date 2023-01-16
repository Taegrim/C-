#include "stdafx.h"
#include <map>
#include <unordered_set>

// STL 컨테이너 - 멀티셋, 멀티맵, 정렬되지않은 셋/맵
//   - unordered_set, unordered_map 은 탐색이 보통 O(1), 최악의 경우 O(N)
//	 - rehash 가 일어나면 O(N)의 시간이 걸림
//   - 사용자 작성 클래스에 해시함수를 적용하는 법

template <typename K, typename V>
void Print(const std::multimap<K, V>& m)
{
	// 구조적 바인딩
	for (const auto [name, era] : m)
		std::cout << name << " " << era << std::endl;
}

template <typename K>
void Print(const std::unordered_set<K>& s)
{
	for (const auto& elm : s)
		std::cout << elm << std::endl;
}

template <typename K>
void Exists(const std::unordered_set<K>& s, const K& key)
{
	auto it = s.find(key);
	if (it != s.end())
		std::cout << key << " 가 존재" << std::endl;
	else
		std::cout << key << " 가 없음" << std::endl;
}


class Todo {
public:
	Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}

	bool operator==(const Todo& t) const {
		if (priority == t.priority && job_desc == t.job_desc)
			return true;
		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, const Todo& t) {
		os << std::format("[ 우선순위 : {} ] {}", t.priority, t.job_desc);
		return os;
	}
	friend struct std::hash<Todo>;

private:
	int priority;
	std::string job_desc;
};

// 사용자 작성 클래스를 받는 hash 함수를 템플릿 특수화 함
namespace std {
	template <>
	struct std::hash<Todo> {
		size_t operator()(const Todo& t) const {
			hash<string> hash_func;
			return t.priority ^ (hash_func(t.job_desc));
		}
	};
}

int main()
{
	std::multimap<int, std::string> m;
	m.insert(std::make_pair(1, "hello"));
	m.insert(std::make_pair(1, "hi"));
	m.insert(std::make_pair(1, "ahihi"));
	m.insert(std::make_pair(2, "bye"));
	m.insert(std::make_pair(2, "baba"));

	Print(m);

	std::cout << "---------------------" << std::endl << std::endl;

	//auto range = m.equal_range(1);
	auto [lower, upper] = m.equal_range(1);
	for (auto it = lower; it != upper; ++it)
		std::cout << it->first << " : " << it->second << " " << std::endl;

	std::cout << "---------------------" << std::endl << std::endl;

	std::unordered_set<std::string> s;
	s.insert("hi");
	s.insert("my");
	s.insert("name");
	s.insert("is");
	s.insert("ldh");
	s.insert("welcome");
	s.insert("to");
	s.insert("c++");
	
	Print(s);

	Exists(s, std::string("c++"));
	Exists(s, std::string("c"));
	s.erase(s.find("hi"));
	Exists(s, std::string("hi"));



	std::cout << std::endl;
	std::cout << "사용자 작성 클래스의 해시 함수 적용" << std::endl << std::endl;

	std::unordered_set<Todo> todos;

	todos.insert(Todo(2, "게임 하기"));
	todos.insert(Todo(1, "졸업 작품"));
	todos.insert(Todo(3, "운동 하기"));
	todos.insert(Todo(2, "친구 만나기"));
	Print(todos);
	std::cout << "----------------" << std::endl;
}