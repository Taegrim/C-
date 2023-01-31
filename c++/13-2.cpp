#include "stdafx.h"

class A : public std::enable_shared_from_this<A> {
public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함" << std::endl;
    }

    ~A() {
        std::cout << "소멸자 호출" << std::endl;
        delete[] data;
    }

    std::shared_ptr<A> GetSharedPtr() { return shared_from_this(); }

private:
    int* data;
};

class B {
public:
    B(const std::string s) : s{ s } {
        std::cout << "자원을 획득함" << std::endl;
    }

    ~B() { std::cout << "B 소멸자 호출" << std::endl; }

    void SetOther(std::weak_ptr<B> o) { other = o; }

    void AccessOther() {
        std::shared_ptr<B> o = other.lock();
        if (o) {
            std::cout << "접근 : " << o->GetName() << std::endl;
        }
        else {
            std::cout << "이미 소멸됨" << std::endl;
        }
    }

    std::string GetName() const { return s; }


private:
    std::string s;
    std::weak_ptr<B> other;
};

int main()
{
    std::vector<std::shared_ptr<A>> v;

    v.push_back(std::shared_ptr<A>(new A()));
    v.push_back(std::shared_ptr<A>(v[0]));
    v.push_back(std::shared_ptr<A>(v[1]));

    std::cout << "참조 수 : " << v.begin()->use_count() << std::endl;

    // 벡터의 첫번째 원소 소멸
    std::cout << "첫 번째 소멸" << std::endl << std::endl;
    v.erase(v.begin());

    // 그 다음 원소 소멸
    std::cout << "다음 원소 소멸" << std::endl << std::endl;
    v.erase(v.begin());

    // 마지막 원소 소멸
    std::cout << "마지막 원소 소멸" << std::endl << std::endl;
    v.erase(v.begin());

    std::cout << "프로그램 종료" << std::endl << std::endl;


    auto pa1 = std::make_shared<A>();
    auto pa2 = pa1->GetSharedPtr();

    std::cout << pa1.use_count() << std::endl;
    std::cout << pa2.use_count() << std::endl << std::endl;

    
    
    std::cout << "Weak Ptr" << std::endl;

    std::vector<std::shared_ptr<B>> vec;
    vec.push_back(std::make_shared<B>("자원 1"));
    vec.push_back(std::make_shared<B>("자원 2"));

    vec[0]->SetOther(vec[1]);
    vec[1]->SetOther(vec[0]);

    // pa 와 pb 의 ref count 는 그대로다.
    std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
    std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

    vec[0]->AccessOther();

    vec.pop_back();
    vec[0]->AccessOther();
}