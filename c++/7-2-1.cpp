#include <fstream>
#include "stdafx.h"

// 파일 입출력

// txt 파일의 인코딩 방식을 ANSI로 해야 한글을 읽을 수 있음
// in.eof() 는 파일의 끝 바로 직전까지 읽게 되면 다음엔
// true를 리턴하지만 파일 읽기를 보장할 수 없으므로 사용 X

void ReadFile(const char* file_name)
{
	std::ifstream in(file_name);
	std::string s;
	if (in.is_open()) {
		while (in >> s)
			std::cout << s << std::endl;
	}
	else
		std::cout << "파일을 찾을 수 없습니다\n";
}

void ReadBinaryFile(const char* file_name)
{
	std::ifstream in(file_name, std::ios::binary);
	char c;
	if (in.is_open()) {
		while (in.read((char*)(&c), 1))
			std::cout << c << " ";
		std::cout << std::endl;
	}
	else
		std::cout << "파일을 찾을 수 없습니다\n";
}

void ReadFileUsingIterator(const char* file_name)
{
	std::ifstream in(file_name);
	std::copy(std::istreambuf_iterator<char>{in}, {}, std::ostreambuf_iterator<char>{std::cout});

	/*std::vector<char> v{ std::istreambuf_iterator<char>{in}, {} };
	std::copy(v.begin(), v.end(), std::ostreambuf_iterator<char>{std::cout});*/
}

int main()
{
	std::cout << "한번에 읽기" << std::endl << std::endl;

	std::ifstream in{ "test.txt" };
	std::string s;

	if (in.is_open()) {
		in.seekg(0, std::ios::end);

		int size = in.tellg();

		s.resize(size);

		in.seekg(0, std::ios::beg);

		in.read(&s[0], size);
		std::cout << s << std::endl;
	}
	else
		std::cout << "파일을 찾을 수 없습니다" << std::endl;

	in.close();
	in.open("test.txt");

	std::cout << "\n\n한줄 단위로 읽기" << std::endl << std::endl;

	char buf[100];
	if (in.is_open()) {
		while (in) {
			in.getline(buf, 100, '\n');
			std::cout << buf << std::endl;
		}
	}
	else
		std::cout << "파일을 찾을 수 없습니다" << std::endl;


	in.close();
	in.open("test.txt");
	s.clear();

	std::cout << "\n\n한줄 단위로 읽기 개선" << std::endl << std::endl;
	if (in.is_open()) {
		while (in) {
			getline(in, s);
			std::cout << s << std::endl;
		}
	}
	else
		std::cout << "파일을 찾을 수 없습니다" << std::endl;


	std::ofstream out("test2.txt", std::ios::app);
	if (out.is_open())
		out << "뒤에 덧붙이기";

}