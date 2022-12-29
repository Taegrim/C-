#include <iostream>
#include <string>
#include <format>

class PhotonCannon {
public:
	PhotonCannon(int x, int y);
	PhotonCannon(int x, int y, const char* cannon_name);
	PhotonCannon(const PhotonCannon& other);
	~PhotonCannon();

	void ShowStatus() const;
private:
	int hp, shield;
	int coord_x, coord_y;
	int damage;
	char* name;
};

PhotonCannon::PhotonCannon(int x, int y)
{
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
	name = nullptr;
}

PhotonCannon::PhotonCannon(int x, int y, const char* cannon_name)
{
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
	name = new char[strlen(cannon_name) + 1];
	strcpy_s(name, strlen(cannon_name) + 1, cannon_name);
}

PhotonCannon::PhotonCannon(const PhotonCannon& other)
{
	hp = other.hp;
	shield = other.shield;
	coord_x = other.coord_x;
	coord_y = other.coord_y;
	damage = other.damage;

	name = new char[strlen(other.name) + 1];
	strcpy_s(name, strlen(other.name) + 1, other.name);
}

PhotonCannon::~PhotonCannon()
{
	if (name)
		delete[] name;
}

void PhotonCannon::ShowStatus() const
{
	if (name)
		std::cout << std::format("Photon Cannon : {0}\n", name);
	else
		std::cout << "Photon Cannon\n";
	std::cout << std::format("Location : ({0}, {1})\n", coord_x, coord_y);
	std::cout << std::format("HP : {0}\n", hp);
}

int main()
{
	PhotonCannon pc1{ 3, 3, "Cannon" };
	PhotonCannon pc2{ pc1 };

	pc1.ShowStatus();
	pc2.ShowStatus();
}