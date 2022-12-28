#include <iostream>

struct Animal {
	char name[30];
	int age;
	int health;
	int food;
	int clean;
};

void CreateAnimal(Animal* animal) 
{
	std::cout << "������ �̸� : ";
	std::cin >> animal->name;

	std::cout << "������ ���� : ";
	std::cin >> animal->age;

	animal->health = 100;
	animal->food = 100;
	animal->clean = 100;
}

void Play(Animal* animal)
{
	animal->health += 10;
	animal->food -= 20;
	animal->clean -= 30;
}

void OneDayPass(Animal* animal)
{
	animal->health -= 10;
	animal->food -= 30;
	animal->clean -= 20;
}

void ShowStat(Animal* animal)
{
	std::cout << animal->name << " �� ���� " << std::endl;
	std::cout << "ü�� : " << animal->health << std::endl;
	std::cout << "��θ� : " << animal->food << std::endl;
	std::cout << "û�� : " << animal->clean << std::endl << std::endl;
}

int main()
{
	// ----------------------- new - delete ------------------------------
	
	char* c = new char;
	*c = 'A';
	std::cout << *c << std::endl;
	delete c;

	int size{};
	std::cout << "�迭 ũ�� : ";
	std::cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
		std::cin >> arr[i];
	
	for (int i = 0; i < size; ++i)
		std::cout << i << " ��° �迭�� ���� : " << arr[i] << std::endl << std::endl;

	delete[] arr;



	// ----------------------- Animal ����ü �����Ҵ� --------------------------
	Animal* animals[10];
	int animal_num{};

	while (true) {
		std::cout << "1. ���� �߰��ϱ�" << std::endl;
		std::cout << "2. ���" << std::endl;
		
		int command;
		std::cin >> command;

		int select_num{};

		switch (command) {
		case 1:
			if (animal_num >= 10) {
				std::cout << "���̻� �߰��� �� �����ϴ�\n";
				break;
			}

			animals[animal_num] = new Animal;
			CreateAnimal(animals[animal_num]);

			++animal_num;
			break;

		case 2:
			std::cout << "������ ������ ��ȣ�� ���� : ";
			std::cin >> select_num;

			if (select_num < animal_num)
				Play(animals[select_num]);
			break;

		default:
			std::cout << "��ȣ�� �ٽ� �����Ͻÿ�\n";
		}

		std::cout << std::endl << "-----------  �Ϸ� ��� -----------\n";
		for (int i = 0; i < animal_num; ++i)
			OneDayPass(animals[i]);
		
		for (int i = 0; i < animal_num; ++i)
			ShowStat(animals[i]);

	}

	for (int i = 0; i < animal_num; ++i)
		delete animals[i];
}