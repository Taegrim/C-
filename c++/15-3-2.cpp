#include <thread>
#include <atomic>
#include "stdafx.h"

using std::memory_order_relaxed;

// memory order

// T1, T2 쓰레드 실행 시 (1,0)  (0,1)  (1,1) 중 하나의 결과가 나옴

void T1(std::atomic<int>* a, std::atomic<int>* b)
{
	b->store(1, memory_order_relaxed);		// b = 1 (쓰기)
	int x = a->load(memory_order_relaxed);	// x = a (읽기)

	printf("x : %d\n", x);
}

void T2(std::atomic<int>* a, std::atomic<int>* b)
{
	a->store(1, memory_order_relaxed);		// a = 1 (쓰기)
	int y = b->load(memory_order_relaxed);	// y = b (읽기)

	printf("y : %d\n", y);
}

void Worker(std::atomic<int>* counter)
{
	for (int i = 0; i < 10000; ++i)
		counter->fetch_add(1, memory_order_relaxed);

	// fetch_add 는 ++counter 와 같은 역할을 함
	// ++ 는 순서 재배치와 상관없이 증가하기만 하면 되므로
	// memory_order_relaxed 를 사용할 수 있음
}

int main()
{
	std::vector<std::thread> threads;

	std::atomic<int> a(0);
	std::atomic<int> b(0);

	threads.push_back(std::thread(T1, &a, &b));
	threads.push_back(std::thread(T2, &a, &b));

	for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
	}


	std::vector<std::thread> th;
	std::atomic<int> counter(0);

	for (int i = 0; i < 4; ++i)
		th.push_back(std::thread(Worker, &counter));

	for (auto& t : th)
		t.join();

	std::cout << "Counter : " << counter << std::endl;
}