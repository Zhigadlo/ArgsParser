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
		ThreadPool(int num_threads);

		~ThreadPool();
		void WaitForTasksToFinish();
		void Enqueue(std::function<void()> task);
	private:
		std::vector<std::thread> threads;
		std::queue<std::function<void()>> tasks;
		std::mutex queueMutex;
		std::condition_variable queueCV;

		// Indicate whether the thread pool should stop or not 
		bool stop = false;

		// Counter for the number of enqueued tasks
		int taskCounter = 0;

		std::mutex taskCounterMutex;
		std::condition_variable taskCounterCV;
	};
}