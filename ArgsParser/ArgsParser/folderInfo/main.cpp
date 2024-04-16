#include <catalogs/Catalog.hpp>
#include <condition_variable> 
#include <functional> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 
#include <filesystem>

class ThreadPool
{
public:
	ThreadPool(size_t num_threads
		= std::thread::hardware_concurrency())
	{
		// Creating worker threads 
		for (size_t i = 0; i < num_threads; ++i)
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

						if (stop && tasks.empty())
							return;
						
						task = std::move(tasks.front());
						tasks.pop();
					}

					task();
				}
			});
		}
	}

	~ThreadPool()
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
			thread.join();
	}
 
	void enqueue(std::function<void()> task)
	{
		{
			std::unique_lock<std::mutex> lock(queueMutex);
			tasks.emplace(move(task));
		}
		cv.notify_one();
	}

private:
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasks;
	std::mutex queueMutex;
	std::condition_variable cv;

	// Indicate whether the thread pool should stop or not 
	bool stop = false;
};

void CatalogHandle(catalogs::Catalog& catalog, ThreadPool& pool)
{
	catalog.FindFiles();
	std::list<catalogs::Catalog>& childCatalogs = catalog.GetCatalogs();
	if (childCatalogs.empty()) return;

	for (catalogs::Catalog& childCatalog : childCatalogs)
	{
		pool.enqueue([&childCatalog, &pool]() { CatalogHandle(childCatalog, pool); });
	}
}

int main(const int argC, const char* argV[])
{
	const std::filesystem::path path{ "D:\\Projects\\ArgsParser" };
	catalogs::Catalog root{ path };
	ThreadPool pool(5);
	CatalogHandle(root, pool);
	root.ShowInfo();
}
