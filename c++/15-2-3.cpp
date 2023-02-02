#include <chrono>
#include <condition_variable>
#include <queue>
#include <thread>
#include <mutex>
#include "stdafx.h"

// condition_variable

void Producer(std::queue<std::string>* downloaded_pages, std::mutex* m,
	int index, std::condition_variable* cv)
{
	for (int i = 0; i < 5; ++i) {
		// 페이지를 읽는다고 가정하고 읽는 시간만큼 쓰레드를 멈춤
		std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
		std::string content = "웹사이트 : " + std::to_string(i) + " from thread(" +
			std::to_string(index) + ")\n";

		m->lock();
		downloaded_pages->push(content);
		m->unlock();

		// Consumer 에게 알림
		// 자고있는 쓰레드를 하나 깨워서 조건을 다시 검사하도록 함
		cv->notify_one();
	}
}

void Consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
	int* num_processed, std::condition_variable* cv)
{
	while (*num_processed < 25) {
		// lock_guard 와 달리 생성자가 아니어도 lock 가능
		// cv->wait 가 unique_lock 을 받기 때문에 unique_lock을 사용
		std::unique_lock<std::mutex> lk(*m);

		// 다운로드된 페이지가 있거나, 처리한 페이지가 25면 깨어남
		// 해당 조건이 거짓이면 lk 를 unlock 하고 sleep 상태에 들어감
		cv->wait(lk, [&](){return !downloaded_pages->empty() || *num_processed == 25; });

		// 페이지 처리가 끝나서 wait 을 탈출했다면 쓰레드를 종료하도록 함
		if (*num_processed == 25) {
			lk.unlock();
			return;
		}

		std::string content = downloaded_pages->front();
		downloaded_pages->pop();

		++(*num_processed);
		lk.unlock();

		std::cout << content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
}

int main()
{
	std::queue<std::string> downloaded_pages;
	std::mutex m;
	std::condition_variable cv;

	std::vector<std::thread> producers;
	for (int i = 0; i < 5; ++i) {
		producers.push_back(std::thread(Producer, &downloaded_pages,
			&m, i + 1, &cv));
	}

	int num_processed = 0;
	std::vector<std::thread> consumers;
	for (int i = 0; i < 3; ++i) {
		consumers.push_back(std::thread(Consumer, &downloaded_pages,
			&m, &num_processed, &cv));
	}

	for (auto& th : producers)
		th.join();

	// Producer가 끝났다면 Consumer가 전부 일어나서 작업할 필요가 있음
	// 나머지 자고 있는 쓰레드들을 모두 깨움
	cv.notify_all();

	for (auto& th : consumers)
		th.join();

}