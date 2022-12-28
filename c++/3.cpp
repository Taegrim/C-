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
	std::cout << "동물의 이름 : ";
	std::cin >> animal->name;

	std::cout << "동물의 나이 : ";
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
	std::cout << animal->name << " 의 상태 " << std::endl;
	std::cout << "체력 : " << animal->health << std::endl;
	std::cout << "배부름 : " << animal->food << std::endl;
	std::cout << "청결 : " << animal->clean << std::endl << std::endl;
}

int main()
{
	// ----------------------- new - delete ------------------------------
	
	char* c = new char;
	*c = 'A';
	std::cout << *c << std::endl;
	delete c;

	int size{};
	std::cout << "배열 크기 : ";
	std::cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
		std::cin >> arr[i];
	
	for (int i = 0; i < size; ++i)
		std::cout << i << " 번째 배열의 원소 : " << arr[i] << std::endl << std::endl;

	delete[] arr;



	// ----------------------- Animal 구조체 동적할당 --------------------------
	Animal* animals[10];
	int animal_num{};

	while (true) {
		std::cout << "1. 동물 추가하기" << std::endl;
		std::cout << "2. 놀기" << std::endl;
		
		int command;
		std::cin >> command;

		int select_num{};

		switch (command) {
		case 1:
			if (animal_num >= 10) {
				std::cout << "더이상 추가할 수 없습니다\n";
				break;
			}

			animals[animal_num] = new Animal;
			CreateAnimal(animals[animal_num]);

			++animal_num;
			break;

		case 2:
			std::cout << "놀고싶은 동물의 번호를 선택 : ";
			std::cin >> select_num;

			if (select_num < animal_num)
				Play(animals[select_num]);
			break;

		default:
			std::cout << "번호를 다시 선택하시오\n";
		}

		std::cout << std::endl << "-----------  하루 경과 -----------\n";
		for (int i = 0; i < animal_num; ++i)
			OneDayPass(animals[i]);
		
		for (int i = 0; i < animal_num; ++i)
			ShowStat(animals[i]);

	}

	for (int i = 0; i < animal_num; ++i)
		delete animals[i];
}