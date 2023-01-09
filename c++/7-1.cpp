#include "stdafx.h"

// 스트림의 상태를 관리하는 4개의 플래그
// goodbit, badbit, failbit, eofbit
// 타입에 맞지 않는 값을 넣으면 failbit 이 켜지고 버퍼를 냅둔채 리턴

int main()
{
	std::cout << "스트림 플래그 비트\n";
	int t;
	std::cout << "숫자를 입력하시오 : (-1 입력 시 나가기) ";
	while (std::cin >> t){
		std::cout << "입력 : " << t << std::endl;
		if (-1 == t) 
			break;
	}
	// failbit, badbit 가 둘다 off 일때만 null 포인터를 리턴
	// 위의 cin 에 문자를 입력하면 failbit를 키고 cin을 리턴
	// 따라서 null 포인터가 리턴되고 이것이 while 문의 조건문에 들어가므로
	// 문자를 입력하면 빠져나오게 됨


	std::cout << "\n\n스트림 플래그 비트 초기화 및 버퍼 비우기\n";
	t = 0;
	while (true) {
		std::cout << "숫자를 입력하시오 : (-1 입력 시 나가기) ";
		std::cin >> t;
		std::cout << "입력 : (-1 입력시 나가기) " << t << std::endl;
		if (std::cin.fail()) {
			std::cout << "제대로 입력하세요\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		if (-1 == t)
			break;
	}
	// fail 함수는 failbit, badbit 가 true면 true 리턴
	// cin.clear() 로 플래그들 초기화
	// cin.ignore(int, char) 로 int만큼, char가 나올때까지 버퍼 비우기

	std::cout << "\n\n형식 플래그와 조작자\n";
	t = 0;
	while (true) {
		std::cout << "숫자를 입력하시오 : (-1 입력 시 나가기) ";
		//std::cin.setf(std::ios_base::hex, std::ios_base::basefield);		// 형식 플래그
		//std::cin >> t;
		std::cin >> std::hex >> t;		// 조작자
		std::cout << "입력 : (-1 입력시 나가기) " << t << std::endl;
		if (std::cin.fail()) {
			std::cout << "제대로 입력해주세요\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		if (-1 == t)
			break;
	}
	// 형식플래그로 처리
	// cin.setf(ios_base::fmtflags, ios_base::fmtflags) 는
	// 2번째인자는 x진수 처리를 초기화하고, 첫번째 인자로 받은 진수 형태로 처리하라는 것
	// 지금은 basefield 로 기존에 처리하는 방법을 초기화하고, hex(16진수) 로 처리하라고 설정
	// std::ios_base::hex 는 형식 플래그 (값)

	// 조작자로 처리
	// std::cin >> std::hex >> t 에서 std::hex를 이용해
	// cin 에서 수를 받는 방식을 변환 
	// std::hex 는 조작자(함수)

	// std::endl 은 '\n' 출력 + std::flush()
	// 한칸 띄우고 버퍼에 있는 데이터를 바로 출력


	std::cout << "\n\n스트림 버퍼" << std::endl;
	std::cout << "문자열을 입력하시오 : (-1 입력 시 나가기) ";

	std::string s;
	std::cin >> s;
	char peek = std::cin.rdbuf()->snextc();	// 스트림 위치 지정자를 한칸 전진하고 엿봄
											// 위치 지정자를 움직이지는 않음
	if (std::cin.fail())
		std::cout << "Failed";
	std::cout << "두 번째 단어 맨 앞글자 : " << peek << std::endl;
	std::cin >> s;
	std::cout << "다시 읽으면 : " << s << std::endl;
}