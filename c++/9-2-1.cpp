#include "stdafx.h"

// 가변 길이 템플릿
// 임의의 개수의 인자를 받는 함수
// 파라미터 팩이 없는 함수가 우선순위가 높음

// 자신 앞의 함수만을 알 수 있기 때문에
// 템플릿 함수 작성 시 순서를 유의해야 함


// 가변 길이 템플릿 예시
template <typename T>
void Print(T arg)
{
	std::cout << arg << std::endl;
}

template <typename T, typename... Types>
void Print(T arg, Types... args)
{
	std::cout << arg << ", ";
	Print(args...);
}

// 문자열 합치기
size_t GetStringSize(const char* s)
{
	return strlen(s);
}

size_t GetStringSize(const std::string& s)
{
	return s.size();
}

template <typename String, typename... Strings>
size_t GetStringSize(const String& s, const Strings... strs)
{
	return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(std::string& str)
{
	return;
}

template <typename String, typename... Strings>
void AppendToString(std::string& concat_str, const String& s, Strings... strs)
{
	concat_str.append(s);
	AppendToString(concat_str, strs...);
}

template <typename String>
std::string StrCat(const String& s)
{
	return std::string(s);
}

template <typename String, typename... Strings>
std::string StrCat(const String& s, Strings... strs)
{
	size_t total_size = GetStringSize(s, strs...);

	std::string concat_str;
	concat_str.reserve(total_size);

	concat_str = s;

	AppendToString(concat_str, strs...);

	return concat_str;
}


// 인자들의 평균 구하기, sizeof... 연산자
int SumAll() {
	return 0; 
}

template <typename... Ints>
int SumAll(int num, Ints... nums)
{
	return num + SumAll(nums...);
}

template <typename... Ints>
double Average(Ints... nums)
{
	return static_cast<double>(SumAll(nums...)) / sizeof...(nums);
}


int main()
{
	Print(1, 3.1, "abc");
	Print(1, 1, 2, 3, 4, 5, 6, 7.0, 8.1f);


	std::cout << "\n\n문자열 이어붙이기" << std::endl;
	std::cout << StrCat(std::string("this"), " ", "is", std::string(" a"),
		" ", std::string("sentence")) << std::endl;


	std::cout << "\n\n인자들의 평균 구하기" << std::endl;
	std::cout << Average(1, 4, 2, 3, 10) << std::endl;
}