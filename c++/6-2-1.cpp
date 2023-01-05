#include "stdafx.h"

// ------------------------------------------------------
// virtual 키워드, 상속과 다형성
// 가상함수는 런타임에 실행되는 동적 바인딩 함수

// 클래스에 가상함수가 있다면 가상함수 테이블이 만들어지고
// 해당 테이블로 어느 함수를 호출할지 런타임에 결정함
//  -> 6-3 에 서술


class Employee {
public:
	Employee(std::string name, int age, std::string position, int rank) :
		name{ name }, age{ age }, position{ position }, rank{ rank } {}

	Employee(const Employee& employee) = default;

	Employee() = default;

	virtual int CaculatePay() const { return 200 + rank * 50; }

	virtual void PrintInfo() {
		std::cout << std::format("{:<6} ({:>6}, {}) ==> {} 만원\n", name, position, age, CaculatePay());
	}

protected:
	std::string name;
	int age;
	std::string position;		// 직책
	int rank;					// 직책의 순위
};

class Manager : public Employee {
public:
	Manager(std::string name, int age, std::string position, int rank, int year_of_service) :
		Employee(name, age, position, rank), year_of_service{ year_of_service } {}

	int CaculatePay() const override { return 200 + rank * 50 + 5 * year_of_service; }

	void PrintInfo() override {
		std::cout << std::format("{:<6} ({:>6}, {}, {}년차) ==> {} 만원\n",
			name, position, age, year_of_service, CaculatePay());
	}

private:
	int year_of_service;
};

class EmployeeList {
public:
	EmployeeList(int alloc_employee) : alloc_employee{ alloc_employee }{
		employee_list = new Employee* [alloc_employee];
		current_employee = 0;
	}

	~EmployeeList() {
		for (int i = 0; i < current_employee; ++i)
			delete employee_list[i];
		delete[] employee_list;
	}

	void AddEmployee(Employee* employee) {
		// 할당한 리스트보다 현재 직원이 많아지면 2배 크기로 재할당
		if (current_employee >= alloc_employee) {
			alloc_employee *= 2;

			Employee** temp = new Employee* [alloc_employee];
			for (int i = 0; i < current_employee; ++i)
				temp[i] = employee_list[i];

			delete[] employee_list;
			employee_list = temp;
		}

		employee_list[current_employee] = employee;
		++current_employee;
	}

	int CurrentEmployeeNum() const { return current_employee; }

	friend std::ostream& operator<<(std::ostream& os, const EmployeeList& el);

private:
	int alloc_employee;

	int current_employee;
	Employee** employee_list;
};


std::ostream& operator<<(std::ostream& os, const EmployeeList& el)
{
	int total_pay{};
	for (int i = 0; i < el.current_employee; ++i) {
		el.employee_list[i]->PrintInfo();
		total_pay += el.employee_list[i]->CaculatePay();
	}

	os << "총 비용 : " << total_pay << "만원\n";
	return os;
}

int main()
{
	EmployeeList emp_list{ 4 };
	emp_list.AddEmployee(new Employee("노홍철", 34, "평사원", 1));
	emp_list.AddEmployee(new Employee("하하", 34, "평사원", 1));
	emp_list.AddEmployee(new Manager("유재석", 41, "부장", 7, 12));
	emp_list.AddEmployee(new Manager("정준하", 43, "과장", 4, 15));
	emp_list.AddEmployee(new Manager("박명수", 43, "차장", 5, 13));
	emp_list.AddEmployee(new Employee("정형돈", 36, "대리", 2));
	emp_list.AddEmployee(new Employee("길", 36, "인턴", -2));

	std::cout << emp_list;
}