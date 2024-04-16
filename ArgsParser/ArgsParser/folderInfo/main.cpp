#include <catalogs/Catalog.hpp>
#include <threads/ThreadPool.hpp>
#include <thread>
#include <chrono>

void CatalogHandle(catalogs::Catalog& catalog, threads::ThreadPool& pool, std::thread::id threadIndex)
{
	catalog.SetThreadIndex(threadIndex);
	catalog.FindFiles();
	std::list<catalogs::Catalog>& childCatalogs = catalog.GetCatalogs();
	if (childCatalogs.empty()) return;
	for (catalogs::Catalog& childCatalog : childCatalogs)
	{
		pool.enqueue([&childCatalog, &pool]() 
		{ 
			CatalogHandle(childCatalog, pool, std::this_thread::get_id());
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		});
	}
}

int main(const int argC, const char* argV[])
{
	const std::filesystem::path path{ "D:\\Projects\\ArgsParser" };
	catalogs::Catalog root{ path };
	threads::ThreadPool pool{ 2 };
	pool.enqueue([&root, &pool]()
	{
		root.SetThreadIndex(std::this_thread::get_id());
		CatalogHandle(root, pool, std::this_thread::get_id());
	});
	//pool.waitForTasksToFinish();
	std::this_thread::sleep_for(std::chrono::seconds(1)); 

	
	root.ShowInfo();
}
