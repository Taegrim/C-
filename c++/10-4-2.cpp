#include "stdafx.h"

// const string& 를 인자로 받는 함수에 문자열 리터럴을 전달하면
// 암묵적 변환으로 인해 불필요한 string 객체 생성이 일어남

// const char* 를 인자로 받는 함수의 경우 string 을 직접 전달할 수 없고
// c_str 과정에서 문자열의 길이를 읽기 때문에 함수 내부에서
// 길이 정보가 필요하면 다시 계산 필요

// string_view 로 위의 문제를 해결
// 문자열을 소유가 아닌 참조하는 것이므로 보고있는 문자열이 소멸되지 않아야 함

void* operator new(std::size_t count) {
	std::cout << count << " bytes 할당 " << std::endl;
	return malloc(count);
}

bool contains_very(const std::string& str) {
	std::cout << str.size() << std::endl;
	return str.find("very") != std::string::npos;
}

bool ContainsVery(std::string_view str) {
	return str.find("very") != std::string_view::npos;
}

int main()
{
	std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
		<< std::endl;


	std::cout << std::boolalpha << ContainsVery("c++ string is very easy to use")
		<< std::endl;
	
	std::cout << ContainsVery("c++ string is not easy to use") << std::endl;

	std::string str = "some long long long long long string";
	std::cout << "--------------------" << std::endl;
	std::cout << ContainsVery(str) << std::endl;

	
	
	std::cout << std::endl << std::endl;


	// string은 substr이 부분 문자열을 새로 생성함
	std::cout << "string -----" << std::endl;
	std::string s = "sometimes string is very slow";
	std::cout << "--------------------" << std::endl;
	std::cout << s.substr(0, 20) << std::endl << std::endl;

	// string_view 는 substr로 또 다른 view를 생성함
	std::cout << "string_view -----" << std::endl;
	std::string_view sv = s;
	std::cout << "--------------------" << std::endl;
	std::cout << sv.substr(0, 20) << std::endl;
}