#include "stdafx.h"

// ------------------------------------------------------
// EmployeeList 를 벡터, 스마트 포인터를 활용하여 변경
// 할당할 배열의 크기를 관리할 필요가 없어짐


class Employee {
public:
	Employee(std::string name, int age, std::string position, int rank) :
		name{ name }, age{ age }, position{ position }, rank{ rank } {}

	Employee(const Employee& employee) = default;

	Employee() = default;

	virtual ~Employee() {}

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

	~Manager() = default;

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
	EmployeeList() {}

	~EmployeeList() {}

	void AddEmployee(std::unique_ptr<Employee>&& employee) {
		employee_list.push_back(std::move(employee));
	}

	int CurrentEmployeeNum() const { return employee_list.size(); }

	friend std::ostream& operator<<(std::ostream& os, const EmployeeList& el);

private:
	std::vector<std::unique_ptr<Employee>>		employee_list;
};


std::ostream& operator<<(std::ostream& os, const EmployeeList& el)
{
	int total_pay{};
	for (const auto& e : el.employee_list){
		e->PrintInfo();
		total_pay += e->CaculatePay();
	}

	os << "총 비용 : " << total_pay << "만원\n";
	return os;
}

int main()
{
	EmployeeList emp_list;
	emp_list.AddEmployee(std::make_unique<Employee>("노홍철", 34, "평사원", 1));
	emp_list.AddEmployee(std::make_unique<Employee>("하하", 34, "평사원", 1));
	emp_list.AddEmployee(std::make_unique<Manager>("유재석", 41, "부장", 7, 12));
	emp_list.AddEmployee(std::make_unique<Manager>("정준하", 43, "과장", 4, 15));
	emp_list.AddEmployee(std::make_unique<Manager>("박명수", 43, "차장", 5, 13));
	emp_list.AddEmployee(std::make_unique<Employee>("정형돈", 36, "대리", 2));
	emp_list.AddEmployee(std::make_unique<Employee>("길", 36, "인턴", -2));

	std::cout << emp_list;
}