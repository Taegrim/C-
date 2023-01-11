#include "stdafx.h"

// 템플릿 - 컴파일 시 인자를 전달해 인스턴스화 되면 코드가 생성됨
// 템플릿 특수화 - 일부 타입에 대해서만 따로 처리를 해주는 것

// 컴파일 타임에 모든 템플릿을 코드로 변환하므로
// 템플릿 오류는 컴파일 타임에 발생

template <typename T>
class Vector {
public:
    Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}
    ~Vector() {
        if (data)
            delete[] data;
    }

    void PushBack(T s) {
        if (capacity <= length) {
            T* temp = new T[capacity * 2];
            for (int i = 0; i < length; ++i)
                temp[i] = data[i];
            
            delete[] data;
            data = temp;
            capacity *= 2;
        }

        data[length++] = s;
    }

    T operator[](int i) const { return data[i]; }

    void Remove(int x) {
        for (int i = x + 1; i < length; ++i) {
            data[i - 1] = data[i];
        }
        --length;
    }

    int Size() const { return length; }

    void Swap(int i, int j) {
        T temp{ data[i] };
        data[i] = data[j];
        data[j] = temp;
    }

private:
    T* data;
    int capacity;
    int length;
};

// int 타입에 32비트를 비트별로 bool 변수를 기록하도록 함
// x64 windows 기준 int 는 4바이트
template <>
class Vector<bool> {
public:
    Vector(int n = 1) : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0) {
        for (int i = 0; i < capacity; ++i)
            data[i] = 0;
    }

    ~Vector() {
        if (data)
            delete[] data;
    }

    void PushBack(bool s) {
        if (capacity * 32 <= length) {
            unsigned int* temp = new unsigned int[capacity * 2];
            for (int i = 0; i < capacity; ++i)
                temp[i] = data[i];

            for (int i = capacity; i < 2 * capacity; ++i)
                temp[i] = 0;

            delete[] data;
            data = temp;
            capacity *= 2;
        }

        // OR 연산으로 해당 비트를 1로 변경
        if (s)
            data[length / 32] |= (1 << (length % 32));

        ++length;
    }

    // AND 연산으로 해당 비트를 확인 함
    bool operator[](int i) const { return (data[i / 32] & (1 << (i % 32))) != 0; }

    void Remove(int x) {
        for (int i = x + 1; i < length; ++i) {
            int prev = i - 1;
            int cur = i;

            // cur 위치의 비트가 1이면
            // prev 위치의 비트를 1로 변경
            if(data[cur / 32] & (1 << (cur % 32)))
                data[prev / 32] |= (1 << (prev % 32));
            // 아니면 prev 위치의 비트를 0으로 지우기
            // 전부 1인 비트에서 특정비트를 0으로 만들고 AND연산을 하면
            // 특정 비트를 0으로 만들 수 있음
            // XOR로 AND 전에 특정 비트를 0으로 바꾸기 가능
            else {
                unsigned int all_ones = 0xffffffff;
                all_ones ^= (1 << (prev % 32));
                data[prev / 32] &= all_ones;
            }
        }

        --length;
    }

    int Size() const { return length; }


private:
    unsigned int* data;
    int capacity;           // 생성된 배열의 크기
    int length;             // 실제 bool 데이터의 길이 (1 capacity = 32 length)
};

template <typename Cont>
void BubbleSort(Cont& cont)
{
    for (int i = 0; i < cont.Size(); ++i) {
        for (int j = i + 1; j < cont.Size(); ++j) {
            if (cont[i] > cont[j])
                cont.Swap(i, j);
        }
    }
}

template <typename Cont, typename Comp>
void BubbleSort(Cont& cont, const Comp& comp)
{
    for (int i = 0; i < cont.Size(); ++i) {
        for (int j = i + 1; j < cont.Size(); ++j) {
            if (!comp(cont[i], cont[j]))
                cont.Swap(i, j);
        }
    }
}

// Functor - 함수 역할을 하는 객체
struct Comp1 {
    bool operator()(int a, int b) const { return a > b; }
};

struct Comp2 {
    bool operator() (int a, int b) const { return a < b; }
};

int main()
{
    Vector<int> int_vector;
    int_vector.PushBack(3);
    int_vector.PushBack(2);

    std::cout << "-------- 정수 벡터 ----------" << std::endl;
    std::cout << "첫번째 원소 : " << int_vector[0] << std::endl;
    std::cout << "두번째 원소 : " << int_vector[1] << std::endl;


    Vector<std::string> str_vec;
    str_vec.PushBack("hello");
    str_vec.PushBack("world");
    std::cout << "-------- 문자열 벡터 -------" << std::endl;
    std::cout << "첫번째 원소 : " << str_vec[0] << std::endl;
    std::cout << "두번째 원소 : " << str_vec[1] << std::endl;


    Vector<bool> bool_vec;
    bool_vec.PushBack(true);
    bool_vec.PushBack(true);
    bool_vec.PushBack(false);
    bool_vec.PushBack(false);
    bool_vec.PushBack(false);
    bool_vec.PushBack(true);
    bool_vec.PushBack(false);
    bool_vec.PushBack(true);
    bool_vec.PushBack(false);
    bool_vec.PushBack(true);
    bool_vec.PushBack(false);
    bool_vec.PushBack(true);
    bool_vec.PushBack(false);
    bool_vec.PushBack(true);
    bool_vec.PushBack(false);
    bool_vec.PushBack(true);
    bool_vec.PushBack(false);

    std::cout << "-------- bool 벡터 -------" << std::endl;
    for (int i = 0; i < bool_vec.Size(); ++i)
        std::cout << bool_vec[i];
    std::cout << std::endl;

    


    std::cout << "\n\n 함수 템플릿을 이용한 정렬" << std::endl;
    Vector<int> v;
    v.PushBack(3);
    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(8);
    v.PushBack(5);
    v.PushBack(3);

    std::cout << "--------정렬 이전-------" << std::endl;
    for (int i = 0; i < v.Size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;


    std::cout << "--------내림차순 정렬 이후-------" << std::endl;

    Comp1 comp1;
    BubbleSort(v, comp1);

    for (int i = 0; i < v.Size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;


    std::cout << "--------오름차순 정렬 이후-------" << std::endl;

    BubbleSort(v, [](int a, int b) { return a < b; });

    for (int i = 0; i < v.Size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}