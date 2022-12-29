#include <iostream>
#include <string>
#include <format>
#include <array>

class Marine {
public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, const char* marine_name);
	~Marine();

	int Attack();
	void BeAttacked(int hit_damage);
	void Move(int x, int y);

	void ShowStatus();

private:
	int hp;
	int coord_x, coord_y;
	int damage;
	bool is_dead;
	char* name;
};

Marine::Marine()
{
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
	name = nullptr;
}

Marine::Marine(int x, int y)
{
	hp = 50;
	coord_x = x;
	coord_y = y;
	damage = 5;
	is_dead = false;
	name = nullptr;
}

Marine::Marine(int x, int y, const char* marine_name)
{
	hp = 50;
	coord_x = x;
	coord_y = y;
	damage = 5;
	is_dead = false;

	name = new char[strlen(marine_name) + 1];
	strcpy_s(name, strlen(marine_name) + 1, marine_name);
}


Marine::~Marine()
{
	if (name) {
		std::cout << name << " 삭제" << std::endl;
		delete[] name;
	}
}

void Marine::Move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::Attack()
{
	return damage;
}

void Marine::BeAttacked(int hit_damage)
{
	hp -= hit_damage;
	if (hp <= 0)
		is_dead = true;
}

void Marine::ShowStatus()
{
	if (name)
		std::cout << std::format(" *** Marine : {0} ***\n", name);
	else
		std::cout << " **** Marine ****\n";

	std::cout << std::format("Location : ( {0} , {1} )\n", coord_x, coord_y);
	std::cout << std::format("HP : {0}\n", hp);
}

int main()
{
	Marine marine1{ 2,3 };
	Marine marine2{ 3,5 };

	marine1.ShowStatus();
	marine2.ShowStatus();

	std::cout << std::endl << "마린 1 이 마린 2 를 공격\n";
	marine2.BeAttacked(marine1.Attack());

	marine1.ShowStatus();
	marine2.ShowStatus();


	// ----------------------- 마린 배열 ---------------------------
	std::cout << std::endl << std::endl;

	std::array<Marine*, 100> marines{};
	marines[0] = new Marine{ 2, 3, "Marine 1" };
	marines[1] = new Marine{ 1, 5, "Marine 2" };

	marines[0]->ShowStatus();
	marines[1]->ShowStatus();

	std::cout << std::endl << "마린 1 이 마린 2 를 공격\n";

	marines[1]->BeAttacked(marines[1]->Attack());

	marines[0]->ShowStatus();
	marines[1]->ShowStatus();

	delete marines[0];
	delete marines[1];
}