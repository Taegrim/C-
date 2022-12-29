#include "stdafx.h"

class Marine {
public:
	Marine() :hp{ 50 }, coord_x{ 0 }, coord_y{ 0 }, default_damage{ 5 }, is_dead{ false }
	{
		++marine_count; 
	}
	Marine(int x, int y) : coord_x{ x }, coord_y{ y }, hp{ 50 },
		default_damage{ 5 }, is_dead{ false } 
	{
		++marine_count; 
	}
	Marine(int x, int y, int damage) : coord_x{ x }, coord_y{ y }, hp{ 50 },
		default_damage{ damage }, is_dead{ false } 
	{
		++marine_count;
	}
	~Marine() { --marine_count; }

	int Attack() const;
	Marine& BeAttacked(int hit_damage);
	void Move(int x, int y);

	void ShowStatus() const;
	static void ShowTotalMarine();
private:
	int					coord_x, coord_y;
	int					hp;
	bool				is_dead;
	
	const int			default_damage;

	static int			marine_count;
	const static int	i{};
};

int Marine::marine_count{};	// Ŭ���� ����ƽ ��� ������ �������� ���� �ʿ�

void Marine::ShowTotalMarine()	// ��ü�� ���ϴ� ���� �ƴ� Ŭ������ ���ӵ�
{
	std::cout << std::format("���� �� ���� �� :  : {0}\n", marine_count);
}


void Marine::Move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::Attack() const
{
	return default_damage;
}

Marine& Marine::BeAttacked(int hit_damage)
{
	hp -= hit_damage;
	if (hp <= 0)
		is_dead = true;
	
	return *this;
}

void Marine::ShowStatus() const
{
	std::cout << " **** Marine ****\n";
	std::cout << std::format("Location : ( {0} , {1} )\n", coord_x, coord_y);
	std::cout << std::format("HP : {0}\n", hp);
}


void CreateMarine()
{
	Marine marine3{ 10,10,4 };
	marine3.ShowTotalMarine();
}


int main()
{
	Marine marine1{ 5, 7, 5 };
	marine1.ShowTotalMarine();

	Marine marine2{ 1, 3, 5 };
	marine2.ShowTotalMarine();

	CreateMarine();

	std::cout << "\n���� 1 �� ���� 2 �� �� �� ����\n";
	marine2.BeAttacked(marine1.Attack()).BeAttacked(marine1.Attack());
	
	marine1.ShowStatus();
	marine2.ShowStatus();
	Marine::ShowTotalMarine();
}