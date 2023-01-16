#include "stdafx.h"
#include <set>

// STL 컨테이너 - set

template <typename T>
void Print(const std::set<T>& s)
{
	for (auto p = s.begin(); p != s.end(); ++p)
		std::cout << *p << std::endl;
}

template <typename T, typename C>
void Print(const std::set<T, C>& s)
{
	for (const auto& elm : s)
		std::cout << elm << std::endl;
}

template <typename T>
void Exists(const std::set<T>& s, T key)
{
	std::cout << key << "이(가) s의 원소인가요? ";
	auto p = s.find(key);
	if (p != s.end())
		std::cout << "네" << std::endl;
	else
		std::cout << "아니오" << std::endl;
}

class Todo {
public:
	Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}

	
	friend std::ostream& operator<<(std::ostream& os, const Todo & t) {
		os << std::format("[ 우선순위 : {} ] {}", t.priority, t.job_desc);
		return os;
	}

	friend struct TodoComp;

private:
	int priority;
	std::string job_desc;
};

struct TodoComp {
	bool operator()(const Todo& t1, const Todo& t2) const {
		if (t1.priority == t2.priority)
			return t1.job_desc < t2.job_desc;
		return t1.priority < t2.priority;
	}
};

int main()
{
	std::set<int> s;
	s.insert(10);
	s.insert(50);
	s.insert(20);
	s.insert(40);
	s.insert(30);
	s.insert(50);
	s.insert(50);

	Print(s);

	Exists(s, 20);
	Exists(s, 25);

	std::cout << std::endl << std::endl;

	std::set<Todo, TodoComp> todos;
	todos.insert(Todo(1, "졸업 작품"));
	todos.insert(Todo(2, "게임 하기"));
	todos.insert(Todo(2, "친구 만나기"));
	todos.insert(Todo(3, "운동 하기"));
	Print(todos);

	std::cout << "--------------------" << std::endl;
	std::cout << "졸작을 했다면" << std::endl;
	todos.erase(todos.find(Todo(1, "졸업 작품")));
	Print(todos);
}