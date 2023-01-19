#include <exception>
#include "stdafx.h"

template <typename T>
class Vector {
public:
    Vector(size_t size) : size_(size) {
        data_ = new T[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = 3;
        }
    }
    ~Vector() { 
        if(data_)
            delete[] data_; 
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("vector 의 index 가 범위를 초과하였습니다.");
        }
        return data_[index];
    }

private:
    T* data_;
    size_t size_;
};

class Resource {
public:
    Resource(int id) : m_id(id) {} 
    ~Resource() { std::cout << "리소스 해제 : " << m_id << std::endl; }

private:
    int m_id;
};

int func3() {
    Resource r(3);
    throw std::runtime_error("Exception from 3!\n");
}

int func2() {
    Resource r(2);
    func3();
    std::cout << "실행 안됨" << std::endl;
    return 0;
}

int func1() {
    Resource r(1);
    func2();
    std::cout << "실행 안됨" << std::endl;
    return 0;
}

int main()
{
    Vector<int> vec(3);

    int i{}, data{};
    std::cin >> i;

    try {
        data = vec.at(i);
    }
    catch (std::out_of_range& e) {
        std::cout << "예외 발생 ! " << e.what() << std::endl;
    }

    std::cout << "읽은 데이터 : " << data << std::endl;

    
    
    // 스택 풀기 확인
    // 단, 생성자에서 예외 발생 시 소멸자 호출 X
    std::cout << std::endl << std::endl;

    try {
        func1();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }

}