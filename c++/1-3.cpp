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
	std::cout << "숫자를 맞추어 보세요 (1~10)" << std::endl;
	int input_number{};

	while (true) {
		std::cout << "입력 : ";
		std::cin >> input_number;
		if (lucky_number == input_number) {
			std::cout << "정답입니다\n";
			break;
		}
		else
			std::cout << "다시 생각해보세요\n";
	}

	std::cout << "원하시는 정보를 입력하세요\n";
	std::cout << "1. 이름\n";
	std::cout << "2. 생년월일\n";
	std::cout << "3. 성별\n";
	std::cin >> input_number;

	switch (input_number) {
	case 1: std::cout << "이동현\n"; break;
	case 2: std::cout << "19991204\n"; break;
	case 3: std::cout << "남자\n"; break;

	default:
		std::cout << "다시 입력하세요\n";
	}
	
}