#pragma once
#include <condition_variable> 
#include <functional> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 
#include <filesystem>

namespace threads
{
	class ThreadPool
	{
	public:
		ThreadPool(size_t num_threads
			= std::thread::hardware_concurrency());

		~ThreadPool();

		void enqueue(std::function<void()> task);

	private:
		std::vector<std::thread> threads;
		std::queue<std::function<void()>> tasks;
		std::mutex queueMutex;
		std::condition_variable cv;

		// Indicate whether the thread pool should stop or not 
		bool stop = false;
	};
}