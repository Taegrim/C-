#include <thread>
#include <mutex>
#include "stdafx.h"

// 데드락
// 일반적인 상황에선 쓰레드가 하나의 락을 사용한다면
// 데드락은 발생하지 않을 것

void Worker1(std::mutex& m1, std::mutex& m2)
{
	for (int i = 0; i < 100; ++i) {
		m1.lock();
		m2.lock();
		std::cout << "Worker1 Hi!" << std::endl;

		m2.unlock();
		m1.unlock();
	}
}

void Worker2(std::mutex& m1, std::mutex& m2)
{
	for (int i = 0; i < 100; ++i) {
		while (true) {
			m2.lock();

			// m1이 lock이 되어있다면
			// m2의 lock을 풀고 while문을 반복함
			if (m1.try_lock()) {
				m2.unlock();
				continue;
			}

			std::cout << "Worker2 Hi!" << std::endl;

			m1.unlock();
			m2.unlock();
			break;
		}
	}
}


int main()
{
	std::mutex m1;
	std::mutex m2;

	std::vector<std::thread> workers;

	std::thread t1(Worker1, std::ref(m1), std::ref(m2));
	std::thread t2(Worker2, std::ref(m1), std::ref(m2));

	t1.join();
	t2.join();
}