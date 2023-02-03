#include <atomic>
#include <thread>
#include "stdafx.h"

// memory_order_seq_cst 를 사용하면 순서를 보장하지만
// 제약 조건이 느슨할 때 보다 속도가 느림

std::atomic<bool> x(false);
std::atomic<bool> y(false);
std::atomic<int> z(0);

void WriteX() { x.store(true, std::memory_order_seq_cst); }

void WriteY() { y.store(true, std::memory_order_seq_cst); }

void ReadXThenY() {
    while (!x.load(std::memory_order_seq_cst)) {}

    if (y.load(std::memory_order_seq_cst)) 
        ++z;
}

void ReadYThenX() {
    while (!y.load(std::memory_order_seq_cst)) {}

    if (x.load(std::memory_order_seq_cst))
        ++z;
}

int main() {
    std::thread a(WriteX);
    std::thread b(WriteY);
    std::thread c(ReadXThenY);
    std::thread d(ReadYThenX);
    a.join();
    b.join();
    c.join();
    d.join();

    std::cout << "z : " << z << std::endl;
}