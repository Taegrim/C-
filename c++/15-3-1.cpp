#include <thread>
#include <atomic>
#include "stdafx.h"

// CPU 에 따라 메모리에 lock add ( 읽고, 더하고, 쓰기를 한번에 처리함)
// 명령어를 지원한다면 atomic 사용 시 mutex가 없어도
// 쓰레드에 안전하게 처리 가능하다

void Worker(std::atomic<int>& counter)
{
	for (int i = 0; i < 10000; ++i)
		++counter;
}

int main()
{
	std::atomic<int> counter(0);

	std::vector<std::thread> workers;
	for (int i = 0; i < 4; ++i)
		workers.push_back(std::thread(Worker, std::ref(counter)));

	for (int i = 0; i < workers.size(); ++i)
		workers[i].join();

	std::cout << "Counter 값 : " << counter << std::endl;
}