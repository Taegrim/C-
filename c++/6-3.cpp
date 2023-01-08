#include "stdafx.h"

class Parent {
public:
    Parent() { std::cout << "Parent ������ ȣ��\n"; }
    virtual ~Parent() { std::cout << "Parent �Ҹ��� ȣ��\n"; }
};

class Child : public Parent {
public:
    Child() : Parent() { std::cout << "Child ������ ȣ��\n"; }
    ~Child() { std::cout << "Child �Ҹ��� ȣ��\n"; }
};

class Animal {
public:
    Animal(int n) : num{ n } {}
    virtual ~Animal() {}
    virtual void speak() = 0;

    virtual void Print() { std::cout << num << std::endl; }

protected:
    int num;
};

class Dog : public virtual Animal {
public:
    Dog(int n) : Animal(n) {}
    virtual ~Dog() {}
    virtual void speak() override {
        std::cout << "�п�\n";
    }

    virtual void Print() override { std::cout << num << std::endl; }
};

class Cat : public virtual Animal {
public:
    Cat(int n) : Animal(n) {}
    virtual ~Cat() {}
    virtual void speak() override {
        std::cout << "�߿˾߿�\n";
    }

    virtual void Print() override { std::cout << num << std::endl; }
};

class DogCat : public Dog, public Cat {
public:
    DogCat(int n) : Animal(n + 1), Dog(n + 2), Cat(n + 3) {}
    ~DogCat() {}
    void speak() override {
        std::cout << "�по߿˾߿�\n";
    }

    void Print() override final { std::cout << num << std::endl; }

};


int main()
{
    std::cout << "--- Child �ν��Ͻ� ---" << std::endl;
    {
        Child c; 
    }

    std::cout << "--- Parent ������ ���� Child ---" << std::endl;
    {
        Parent* p = new Child();
        delete p;
    }

    //
    std::cout << "\n-------------------------\n";

    Animal* dog = new Dog(3);
    Animal* cat = new Cat(3);

    dog->speak();
    cat->speak();


    std::cout << "\n-------------------------\n";

    Animal* dogcat = new DogCat(3);
    dogcat->Print();
    // ���� �Լ��� ���� ��� �� �ֻ��� �θ� ��ӵ�
    // �ֻ��� �θ� ����� ���� ��ӹ��� �θ� ���� ����� ������
    // �̰��� ��ӹ��� ��� ��ȣ����

}