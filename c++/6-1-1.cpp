#include "stdafx.h"

class Employee {
public:
	Employee(std::string name, int age, std::string position, int rank) :
		name{ name }, age{ age }, position{ position }, rank{ rank } {}

	Employee(const Employee& employee) = default;

	Employee() = default;

	int CaculatePay() const { return 200 + rank * 50; }
	
	void PrintInfo() {
		std::cout << std::format("{:<6} ({:>6}, {}) ==> {} ����\n", name, position, age, CaculatePay());
	}

protected:
	std::string name;
	int age;
	std::string position;		// ��å
	int rank;					// ��å�� ����
};

class Manager : public Employee {
public:
	Manager(std::string name, int age, std::string position, int rank, int year_of_service) :
		Employee(name, age, position, rank), year_of_service{ year_of_service } {}

	Manager(const Manager& manager) = default;

	Manager() = default;

	int CaculatePay() { return 200 + rank * 50 + 5 * year_of_service; }

	void PrintInfo() {
		std::cout << std::format("{:<6} ({:>6}, {}, {}����) ==> {} ����\n",
			name, position, age, year_of_service, CaculatePay());
	}

private:
	int year_of_service;
};

class EmployeeList {
public:
	EmployeeList(int alloc_employee) : alloc_employee{ alloc_employee }
		, alloc_manager{ alloc_employee } 
	{
		employee_list = new Employee* [alloc_employee];
		current_employee = 0;

		manager_list = new Manager* [alloc_manager];
		current_manager = 0;
	}

	~EmployeeList() {
		for (int i = 0; i < current_employee; ++i)
			delete employee_list[i];
		delete[] employee_list;

		for (int i = 0; i < current_manager; ++i)
			delete manager_list[i];
		delete[] manager_list;
	}

	void AddEmployee(Employee* employee) {
		// �Ҵ��� ����Ʈ���� ���� ������ �������� 2�� ũ��� ���Ҵ�
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

	void AddManager(Manager* manager) {
		if (current_manager >= alloc_manager) {
			alloc_manager *= 2;

			Manager** temp = new Manager* [alloc_manager];
			for (int i = 0; i < current_manager; ++i)
				temp[i] = manager_list[i];

			delete[] manager_list;
			manager_list = temp;
		}
		
		manager_list[current_manager] = manager;
		++current_manager;
	}
	
	int CurrentEmployeeNum() const { return current_employee; }
	int CurrentManagerNum() const { return current_manager; }
	
	friend std::ostream& operator<<(std::ostream& os, const EmployeeList& el);

private:
	int alloc_employee;
	int alloc_manager;

	int current_employee;
	Employee** employee_list;

	int current_manager;
	Manager** manager_list;
};


std::ostream& operator<<(std::ostream& os, const EmployeeList& el)
{
	int total_pay{};
	for (int i = 0; i < el.current_employee; ++i) {
		el.employee_list[i]->PrintInfo();
		total_pay += el.employee_list[i]->CaculatePay();
	}

	for (int i = 0; i < el.current_manager; ++i) {
		el.manager_list[i]->PrintInfo();
		total_pay += el.manager_list[i]->CaculatePay();
	}

	os << "�� ��� : " << total_pay << "����\n";
	return os;
}

int main()
{
	EmployeeList emp_list{ 3 };
	emp_list.AddEmployee(new Employee("��ȫö", 34, "����", 1));
	emp_list.AddEmployee(new Employee("����", 34, "����", 1));
	emp_list.AddManager(new Manager("���缮", 41, "����", 7, 12));
	emp_list.AddManager(new Manager("������", 43, "����", 4, 15));
	emp_list.AddManager(new Manager("�ڸ��", 43, "����", 5, 13));
	emp_list.AddEmployee(new Employee("������", 36, "�븮", 2));
	emp_list.AddEmployee(new Employee("��", 36, "����", -2));

	std::cout << emp_list;
}