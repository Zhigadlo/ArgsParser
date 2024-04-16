#include <catalogs/Catalog.hpp>
#include <threads/ThreadPool.hpp>

void CatalogHandle(catalogs::Catalog& catalog, threads::ThreadPool& pool)
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
	const std::filesystem::path path{ "D:\\Projects\\ArgsParser\\ArgsParser\\ArgsParser" };
	catalogs::Catalog root{ path };
	threads::ThreadPool pool(4);
	CatalogHandle(root, pool);
	root.ShowInfo();
}
