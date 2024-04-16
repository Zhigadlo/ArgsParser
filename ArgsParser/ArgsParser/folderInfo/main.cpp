#include <catalogs/Catalog.hpp>
#include <threads/ThreadPool.hpp>
#include <args/BaseArg.hpp>
#include <parser/ArgsParser.hpp>
#include <thread>
#include <chrono>

void CatalogHandle(catalogs::Catalog& catalog, threads::ThreadPool& pool, std::chrono::milliseconds sleepMs)
{
	catalog.SetThreadIndex(std::this_thread::get_id());
	catalog.FindFiles();
	std::list<catalogs::Catalog>& childCatalogs = catalog.GetCatalogs();
	if (childCatalogs.empty()) return;
	for (catalogs::Catalog& childCatalog : childCatalogs)
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
	const std::filesystem::path path{ folderPathArg.GetValue()};
	
	if (!std::filesystem::exists(path))
	{
		std::cout << "Error: There is no such path " << path << std::endl;
		return 0;
	}

	catalogs::Catalog root{ path };
	threads::ThreadPool pool{ threadCountArg.GetValue() };
	std::chrono::milliseconds sleepMs(0);
	
	if(debugSleepMsArg.IsDefined())
		sleepMs = debugSleepMsArg.GetValue();

	pool.Enqueue([&root, &pool, sleepMs]()
	{
		CatalogHandle(root, pool, sleepMs);
	});
	pool.WaitForTasksToFinish();
	
	root.ShowInfo();
}
