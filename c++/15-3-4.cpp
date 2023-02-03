#include <atomic>
#include <thread>
#include "stdafx.h"

using std::memory_order_relaxed;

std::atomic<bool> is_ready;
std::atomic<int> data[3];

void Producer() {
    data[0].store(1, memory_order_relaxed);
    data[1].store(2, memory_order_relaxed);
    data[2].store(3, memory_order_relaxed);
    
    // data에 store 명령들은 이 이후로 배치될 수 없음
    is_ready.store(true, std::memory_order_release);
}

void Consumer() {
    while (!is_ready.load(std::memory_order_acquire)) {}
    
    std::cout << "data[0] : " << data[0].load(memory_order_relaxed) << std::endl;
    std::cout << "data[1] : " << data[1].load(memory_order_relaxed) << std::endl;
    std::cout << "data[2] : " << data[2].load(memory_order_relaxed) << std::endl;
}

int main() {
    std::vector<std::thread> threads;

    threads.push_back(std::thread(Producer));
    threads.push_back(std::thread(Consumer));

    for (auto& th : threads)
        th.join();
}