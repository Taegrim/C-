#include "stdafx.h"

using namespace std::literals;

//void* operator new(std::size_t count)
//{
//	std::cout << count << " bytes 할당" << std::endl;
//	return malloc(count);
//}

int main()
{
	std::cout << "s1 생성" << std::endl;
	std::string s1 = "this is a pretty long sentence!!!";
	std::cout << "s1 크기 : " << sizeof(s1) << std::endl;

	std::cout << "s2 생성" << std::endl;
	std::string s2 = "short sentence";
	std::cout << "s2 크기 : " << sizeof(s2) << std::endl;

	std::cout << std::endl << std::endl;


	auto str = "hello"s;
	std::cout << "str의 길이 : " << str.size() << std::endl;

	std::string str2 = R"foo((asdasd
Raw string
literal)
\n\n)foo";

	std::cout << str2 << std::endl << std::endl;



	// 문자열 인코딩

	std::u32string u32_str = U"UTF-32 15자리 문자열";
	std::cout << u32_str.size() << std::endl;

	std::u16string u16_str = u"안녕하세용 모두에 코드에 오신 것을 환영합니다";
	std::string jaum[] = { "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ",
						  "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
						  "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ" };

	for (char16_t c : u16_str) {
		// 유니코드 상에서 한글의 범위
		if (!(0xAC00 <= c && c <= 0xD7A3)) {
			continue;
		}

		// 한글은 AC00 부터 시작해서 한 초성당 총 0x24C(588) 개 씩 있다.
		int offset = c - 0xAC00;
		int jaum_offset = offset / 0x24C;
		std::cout << jaum[jaum_offset];
	}
}