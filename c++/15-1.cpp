#include <thread>
#include <sstream>
#include "stdafx.h"

void Worker(std::vector<int>::iterator start, std::vector<int>::iterator end, int* result)
{
	int sum = 0;
	for (auto itr = start; itr < end; ++itr)
		sum += *itr;
	*result = sum;

	
	std::stringstream thread_id;
	thread_id << std::this_thread::get_id();

	 std::cout << std::format("쓰레드 {} 에서 {} 부터 {} 까지 계산한 결과 : {} \n",
		 thread_id.str(), *start, *(end - 1), sum);
}

int main()
{
	int data_size = 10000;

	std::vector<int> data(data_size);
	for (int i = 0; i < data_size; ++i)
		data[i] = i;

	std::vector<int> partial_sums(4);
	
	std::vector<std::thread> workers;
	for (int i = 0; i < partial_sums.size(); ++i) {
		workers.push_back(std::thread(Worker, data.begin() + i * (data_size / partial_sums.size()),
			data.begin() + (i + 1) * (data_size / partial_sums.size()), &partial_sums[i]));
	}

	for (auto& th : workers)
		th.join();

	int total = 0;
	for (int i = 0; i < partial_sums.size(); ++i)
		total += partial_sums[i];

	std::cout << "전체 합 : " << total << std::endl;
}