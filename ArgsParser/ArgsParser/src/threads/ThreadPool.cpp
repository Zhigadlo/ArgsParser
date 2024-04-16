#include "ThreadPool.hpp"

namespace threads
{
	ThreadPool::ThreadPool(int num_threads)
	{
		for (int i = 0; i < num_threads; ++i)
		{
			threads.emplace_back([this]
			{
				while (true)
				{
					std::function<void()> task;
					// unlocks the queue before executing the task 
					{
						std::unique_lock<std::mutex> lock(queueMutex);

						queueCV.wait(lock, [this] { return !tasks.empty() || stop; });

						if (stop && tasks.empty()) return;

						task = std::move(tasks.front());
						tasks.pop();
					}

					task();
					{
						std::unique_lock<std::mutex> taskCounterLock(taskCounterMutex);
						--taskCounter;
					}

					// Notify the main thread that a task has been completed
					taskCounterCV.notify_one();
				}
			});
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			// Lock the queue to update the stop flag safely 
			std::unique_lock<std::mutex> lock(queueMutex);
			stop = true;
		}

		// Notify all threads 
		queueCV.notify_all();

		for (auto& thread : threads)
			if (thread.joinable()) thread.join();
	}

	void ThreadPool::Enqueue(std::function<void()> task)
	{
		{
			std::unique_lock<std::mutex> lock(queueMutex);

			// Increment the task counter when a new task is enqueued
			{
				std::unique_lock<std::mutex> taskCounterLock(taskCounterMutex);
				++taskCounter;
			}

			tasks.emplace(move(task));
		}
		queueCV.notify_one();
	}
	void ThreadPool::WaitForTasksToFinish()
	{
		// Wait until all tasks are completed
		std::unique_lock<std::mutex> lock(taskCounterMutex);
		taskCounterCV.wait(lock, [this] { return taskCounter == 0; });
	}
}