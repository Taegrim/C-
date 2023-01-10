#include <fstream>
#include <sstream>
#include "stdafx.h"

// 문자열 스트림 sstream (istringstream, ostringstream )
// 문자열을 스트림으로 볼 수 있게 해주는 장치
// 

double ToNumber(const std::string& s)
{
	std::istringstream ss(s);
	double d;

	ss >> d;
	return d;
}

std::string ToStr(int x)
{
	std::ostringstream ss;
	ss << x;

	return ss.str();
}

int main()
{
	std::istringstream ss("123");
	int x;
	ss >> x;

	std::cout << "입력받은 데이터 : " << x << std::endl;

	std::cout << "변환 : 1 + 2 = " << ToNumber("1") + ToNumber("2") << std::endl;

	std::cout << "문자열로 변환 : 1 + 2 = " << ToStr(1 + 2) << std::endl;
}