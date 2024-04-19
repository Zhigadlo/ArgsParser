#include <args/BaseArg.hpp>
#include <parser/ArgsParser.hpp>
#include <condition_variable> 
#include <functional> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 
#include <filesystem>
#include <chrono>

class ThreadPool
{
public:
	ThreadPool(int num_threads)
	{
		std::vector<std::thread> tempThreads(num_threads);
		try
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
		catch (...)
		{
			for (auto& thread : tempThreads)
			{
				if (thread.joinable()) thread.join();
			}
			throw;
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
		queueCV.notify_all();

		for (auto& thread : threads)
			if (thread.joinable()) thread.join();
	}
	void WaitForTasksToFinish()
	{
		std::unique_lock<std::mutex> lock(taskCounterMutex);
		taskCounterCV.wait(lock, [this] { return taskCounter == 0; });
	}
	void Enqueue(std::function<void()> task)
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

class Catalog
{
public:
	Catalog(std::filesystem::path fullPath) : fullPath(std::move(fullPath)) {}
	Catalog(std::filesystem::path fullPath,
		int catalogLevel) : fullPath(std::move(fullPath)),
		catalogLevel(catalogLevel)
	{
	}

	[[nodiscard]] const std::filesystem::path& GetFullPath() const
	{
		return fullPath;
	}
	[[nodiscard]] const std::vector<std::filesystem::path>& GetFiles() const
	{
		return files;
	}
	[[nodiscard]] std::list<Catalog>& GetCatalogs()
	{
		return childCatalogs;
	}

	void FindFiles()
	{
		for (auto const& dir_entry : std::filesystem::directory_iterator{ fullPath })
		{
			if (dir_entry.is_directory())
				AddCatalog(dir_entry.path());
			else
				AddFile(dir_entry.path());
		}
	}
	void ShowInfo() const
	{
		PrintOffset();
		std::cout << fullPath.filename() << "[" << threadIndex << "]" << std::endl;
		if (!files.empty())
		{
			for (size_t i = 0; i < files.size(); i++)
			{
				PrintOffset();
				std::cout << files[i].filename() << std::endl;
			}
		}

		if (!childCatalogs.empty())
		{
			for (const Catalog& catalog : childCatalogs)
			{
				catalog.ShowInfo();
			}
		}
	}
	void SetThreadIndex(std::thread::id index)
	{
		threadIndex = index;
	}
private:
	void PrintOffset() const
	{
		for (int j = 0; j < catalogLevel; j++)
			std::cout << utils::SpaceChar << utils::SpaceChar;
	}
	void AddFile(const std::filesystem::path& fullPath)
	{
		files.push_back(fullPath);
	}
	void AddCatalog(const std::filesystem::path& fullPath)
	{
		Catalog newCatalog(fullPath, catalogLevel + 1);
		childCatalogs.push_back(newCatalog);
	}
	std::filesystem::path fullPath;
	std::vector<std::filesystem::path> files;
	std::list<Catalog> childCatalogs;
	int catalogLevel = 0;
	std::thread::id threadIndex;
};

void CatalogHandle(Catalog& catalog, ThreadPool& pool, std::chrono::milliseconds sleepMs)
{
	catalog.SetThreadIndex(std::this_thread::get_id());
	catalog.FindFiles();
	std::list<Catalog>& childCatalogs = catalog.GetCatalogs();
	if (childCatalogs.empty()) return;
	for (Catalog& childCatalog : childCatalogs)
	{
		pool.Enqueue([&childCatalog, &pool, sleepMs]()
			{
				CatalogHandle(childCatalog, pool, sleepMs);
				std::this_thread::sleep_for(sleepMs);
			});
	}
}
void AddArgToParser(parser::ArgsParser& parser, args::BaseArg& arg)
{
	results::Result addResult = parser.Add(arg);
	if (addResult.IsSucceded()) return;

	std::cout << addResult.GetError() << std::endl;
	std::cout << arg.GetInfo() << ": Argument was not added to parser" << std::endl;
}

int main(const int argC, const char* argV[])
{
	args::ValueArg<int> threadCountArg{ 't', "thread_count" };
	args::ValueArg<std::string> folderPathArg{ 'p', "path" };
	args::ValueArg<std::chrono::milliseconds> debugSleepMsArg{ "sleep_ms" };

	parser::ArgsParser argParser;

	argParser.AddWithoutResult(threadCountArg);
	argParser.AddWithoutResult(folderPathArg);
	argParser.AddWithoutResult(debugSleepMsArg);

	results::Result result = argParser.Parse(argC, argV);
	if (!result.IsSucceded())
	{
		std::cout << result.GetError() << std::endl;
		return 0;
	}

	if (!folderPathArg.IsDefined())
	{
		std::cout << "Error: You need to use -p or --path and define folder path" << std::endl;
		return 0;
	}

	if (!threadCountArg.IsDefined())
	{
		std::cout << "Error: You need to use -t or --thread_count and define thread count" << std::endl;
		return 0;
	}
	const std::filesystem::path path{ folderPathArg.GetValue() };

	if (!std::filesystem::exists(path))
	{
		std::cout << "Error: There is no such path " << path << std::endl;
		return 0;
	}

	Catalog root{ path };
	ThreadPool pool{ threadCountArg.GetValue() };
	std::chrono::milliseconds sleepMs(0);

	if (debugSleepMsArg.IsDefined())
		sleepMs = debugSleepMsArg.GetValue();

	pool.Enqueue([&root, &pool, sleepMs]()
		{
			CatalogHandle(root, pool, sleepMs);
		});
	pool.WaitForTasksToFinish();

	root.ShowInfo();
}
