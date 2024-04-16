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

						cv.wait(lock, [this] { return !tasks.empty() || stop; });

						if (stop && tasks.empty()) return;

						task = std::move(tasks.front());
						tasks.pop();
					}

					task();
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
		cv.notify_all();

		// Joining all worker threads to ensure they have 
		// completed their tasks 
		for (auto& thread : threads)
			if (thread.joinable()) thread.join();
	}

	void ThreadPool::enqueue(std::function<void()> task)
	{
		{
			std::unique_lock<std::mutex> lock(queueMutex);
			tasks.emplace(move(task));
		}
		cv.notify_one();
	}
}