#include <fstream>
#include "stdafx.h"

// ofstream 연산자 오버로딩

class Human {
public:
	Human(const std::string& name, int age) :name{ name }, age{ age } {}
	
	std::string GetInfo() const {
		return std::format("Name : {} / Age : {}", name, std::to_string(age));
	}

	friend std::ofstream& operator<<(std::ofstream& out, const Human& h) {
		out << h.GetInfo();
		return out;
	}

private:
	std::string name;
	int age;
};

int main()
{
	std::ofstream out("Human.txt");
	Human h("이동현", 24);
	out << h << std::endl;
}
