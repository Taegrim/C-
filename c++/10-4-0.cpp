#include "stdafx.h"

// base_string 은 객체에 담을 타입, 연산자들, 할당자를 템플릿 인자로 받음

// 데이터를 저장할 필요 없기 때문에 static 함수들로 되어있음 (Stateless)
struct MyCharTraits : public std::char_traits<char> {
	static int GetRealRank(char c) {
		if (isdigit(c))
			return c + 256;
		return c;
	}

	static bool lt(char c1, char c2) {
		return GetRealRank(c1) < GetRealRank(c2);
	}

	static int compare(const char* s1, const char* s2, size_t n) {
		while (n-- != 0) {
			if (GetRealRank(*s1) < GetRealRank(*s2))
				return -1;

			if (GetRealRank(*s1) > GetRealRank(*s2))
				return 1;

			++s1;
			++s2;
		}
		return 0;
	}
};

int main()
{
	std::basic_string<char, MyCharTraits> my_s1 = "1a";
	std::basic_string<char, MyCharTraits> my_s2 = "a1";

	std::cout << "숫자 우선순위가 더 낮은 문자열 " << std::boolalpha
		<< (my_s1 < my_s2) << std::endl;

	std::string s1 = "1a";
	std::string s2 = "a1";

	std::cout << "일반 문자열 " << std::boolalpha << (s1 < s2) << std::endl;
}