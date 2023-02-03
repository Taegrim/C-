#include <atomic>
#include <thread>
#include "stdafx.h"

// 생산자 - 소비자 관계에선 memory_order_relaxed 를 사용할 수 없음
// 코드 재배치가 될 경우 제대로된 결과를 얻을 수 없기 때문

// memory_order_release
//  - 해당 명령 이전의 모든 메모리 명령이 해당 명령 이후로 재배치될 수 없음
//  - memory_order_acquire 로 변수를 읽을 때 이전의 명령들이 실행되었음을
//    관찰할 수 있음

void Producer(std::atomic<bool>* is_ready, int* data) {
    *data = 10;
    is_ready->store(true, std::memory_order_release);
}

void Consumer(std::atomic<bool>* is_ready, int* data) {

    while (!is_ready->load(std::memory_order_acquire)) {}

    std::cout << "data : " << *data << std::endl;
}

int main() {
    std::vector<std::thread> threads;

    std::atomic<bool> is_ready(false);
    int data = 0;

    threads.push_back(std::thread(Producer, &is_ready, &data));
    threads.push_back(std::thread(Consumer, &is_ready, &data));

    for (auto& th : threads)
        th.join();
}