#include <iostream>

int main()
{
	int i{};
	char c{};
	double d{};
	float f{};

	std::cout << sizeof(i) << ", " 
		<< sizeof(c) << ", " 
		<< sizeof(d) << ", " 
		<< sizeof(f) << std::endl;


	int arr[10];
	int* p = arr;
	
	int* pi = &i;


	int lucky_number = 3;
	std::cout << "���ڸ� ���߾� ������ (1~10)" << std::endl;
	int input_number{};

	while (true) {
		std::cout << "�Է� : ";
		std::cin >> input_number;
		if (lucky_number == input_number) {
			std::cout << "�����Դϴ�\n";
			break;
		}
		else
			std::cout << "�ٽ� �����غ�����\n";
	}

	std::cout << "���Ͻô� ������ �Է��ϼ���\n";
	std::cout << "1. �̸�\n";
	std::cout << "2. �������\n";
	std::cout << "3. ����\n";
	std::cin >> input_number;

	switch (input_number) {
	case 1: std::cout << "�̵���\n"; break;
	case 2: std::cout << "19991204\n"; break;
	case 3: std::cout << "����\n"; break;

	default:
		std::cout << "�ٽ� �Է��ϼ���\n";
	}
	
}