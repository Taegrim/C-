#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include "stdafx.h"

// Producer - Consumer 패턴

void Producer(std::queue<std::string>* downloaded_pages, std::mutex* m,
	int index)
{
	for (int i = 0; i < 5; ++i) {
		// 페이지를 읽는다고 가정하고 읽는 시간만큼 쓰레드를 멈춤
		std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
		std::string content = "웹사이트 : " + std::to_string(i) + " from thread(" +
			std::to_string(index) + ")\n";

		m->lock();
		downloaded_pages->push(content);
		m->unlock();
	}
}

void Consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
	int* num_processed)
{
	while (*num_processed < 25) {
		m->lock();
		if (downloaded_pages->empty()) {
			m->unlock();

			// downloaded_pages 가 비어있다면 계속 while문을 돌면서
			// CPU를 낭비하지 않기 위해 잠시 대기
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}


		std::string content = downloaded_pages->front();
		downloaded_pages->pop();

		++(*num_processed);
		m->unlock();

		std::cout << content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
}

int main()
{
	std::queue<std::string> downloaded_pages;
	std::mutex m;

	std::vector<std::thread> producers;
	for (int i = 0; i < 5; ++i) {
		producers.push_back(std::thread(Producer, &downloaded_pages,
			&m, i + 1));
	}

	int num_processed = 0;
	std::vector<std::thread> consumers;
	for (int i = 0; i < 3; ++i) {
		consumers.push_back(std::thread(Consumer, &downloaded_pages,
			&m, &num_processed));
	}

	for (auto& th : producers)
		th.join();

	for (auto& th : consumers)
		th.join();

}