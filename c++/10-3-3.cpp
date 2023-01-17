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
	User(std::string name, int level) : name{ name }, level{ level } {}

	bool operator==(const User& user) const {
		if (name == user.name && level == user.level)
			return true;
		return false;
	}

	int GetLevel() const { return level; }
	std::string GetName() const { return name; }

private:
	std::string name;
	int level;
};

class Party {
public:
	Party() = default;

	bool AddUser(std::string name, int level) {
		User new_user(name, level);
		if (std::find(users.begin(), users.end(), new_user) != users.end())
			return false;
		users.push_back(new_user);
		return true;
	}

	bool CanJoinDungeon() {
		return std::all_of(users.begin(), users.end(), [](const User& user) {
			return user.GetLevel() >= 15;
			});
	}
	
	bool CanUseSpecialItem() {
		return std::any_of(users.begin(), users.end(), [](const User& user) {
			return user.GetLevel() >= 19;
			});
	}

private:
	std::vector<User> users;
};

int main()
{
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	auto current = vec.begin();
	while (true) {
		current = std::find(current, vec.end(), 3);
		if (current == vec.end())
			break;
		std::cout << "3 은 " << std::distance(vec.begin(), current) + 1 << " 번째 원소"
			<< std::endl;
		++current;
	}

	current = vec.begin();
	while (true) {
		current = std::find_if(current, vec.end(), [](int i) {return i % 3 == 2; });
		if (current == vec.end())
			break;
		std::cout << "3 으로 나누었을 때 나머지가 2인 원소는 " << *current << std::endl;
		++current;
	}


	std::cout << std::endl << "STL을 이용한 클래스" << std::endl;

	Party party;
	party.AddUser("철수", 15);
	party.AddUser("영희", 18);
	party.AddUser("민수", 12);
	party.AddUser("수빈", 19);

	std::cout << std::boolalpha;
	std::cout << "던전 입장 가능? " << party.CanJoinDungeon() << std::endl;
	std::cout << "특별 아이템 사용 가능? " << party.CanUseSpecialItem() << std::endl;
}