#include "stdafx.h"

class Parent {
public:
    Parent() { std::cout << "Parent 생성자 호출\n"; }
    virtual ~Parent() { std::cout << "Parent 소멸자 호출\n"; }
};

class Child : public Parent {
public:
    Child() : Parent() { std::cout << "Child 생성자 호출\n"; }
    ~Child() { std::cout << "Child 소멸자 호출\n"; }
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
        std::cout << "왈왈\n";
    }

    virtual void Print() override { std::cout << num << std::endl; }
};

class Cat : public virtual Animal {
public:
    Cat(int n) : Animal(n) {}
    virtual ~Cat() {}
    virtual void speak() override {
        std::cout << "야옹야옹\n";
    }

    virtual void Print() override { std::cout << num << std::endl; }
};

class DogCat : public Dog, public Cat {
public:
    DogCat(int n) : Animal(n + 1), Dog(n + 2), Cat(n + 3) {}
    ~DogCat() {}
    void speak() override {
        std::cout << "왈왈야옹야옹\n";
    }

    void Print() override final { std::cout << num << std::endl; }

};


int main()
{
    std::cout << "--- Child 인스턴스 ---" << std::endl;
    {
        Child c; 
    }

    std::cout << "--- Parent 포인터 만든 Child ---" << std::endl;
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
    // 같은 함수를 다중 상속 시 최상위 부모 상속됨
    // 최상위 부모에 멤버가 없고 상속받은 부모에 같은 멤버가 있으면
    // 이것을 상속받을 경우 모호해짐

}