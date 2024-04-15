#pragma once 

#include <list>
#include <vector>
#include <string>

namespace catalogs
{
	class Catalog
	{
	public:
		Catalog(std::string name);
		Catalog(std::string name, int catalogLevel);

		[[nodiscard]] std::string GetName();
		[[nodiscard]] std::string GetInfo();
		[[nodiscard]] std::vector<std::string>& GetFiles();
		[[nodiscard]] std::list<Catalog*>& GetCatalogs();
		[[nodiscard]] void AddFile(const std::string& file);
		[[nodiscard]] void AddCatalog(const std::string& catalog);
	private:
		std::string name;
		std::vector<std::string> files;
		std::list<Catalog*> childCatalogs;
		int catalogLevel = 0;
	};
}