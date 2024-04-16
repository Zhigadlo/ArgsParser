#include <catalogs/Catalog.hpp>
#include <threads/ThreadPool.hpp>
#include <thread>
#include <chrono>

void CatalogHandle(catalogs::Catalog& catalog, threads::ThreadPool& pool)
{
	catalog.SetThreadIndex(std::this_thread::get_id());
	catalog.FindFiles();
	std::list<catalogs::Catalog>& childCatalogs = catalog.GetCatalogs();
	if (childCatalogs.empty()) return;
	for (catalogs::Catalog& childCatalog : childCatalogs)
	{
		pool.Enqueue([&childCatalog, &pool]() 
		{ 
			CatalogHandle(childCatalog, pool);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		});
	}
}

int main(const int argC, const char* argV[])
{
	const std::filesystem::path path{ "../../src" };
	catalogs::Catalog root{ path };
	threads::ThreadPool pool{ 4 };
	pool.Enqueue([&root, &pool]()
	{
		CatalogHandle(root, pool);
	});
	pool.WaitForTasksToFinish();
	
	root.ShowInfo();
}
