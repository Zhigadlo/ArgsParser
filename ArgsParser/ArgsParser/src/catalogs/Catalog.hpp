#pragma once 

#include <vector>
#include <string>
#include <results/Result.hpp>

namespace catalogs
{
	class Catalog
	{
	public:
		[[nodiscard]] std::string GetName();
		[[nodiscard]] std::string GetInfo();
		[[nodiscard]] std::vector<std::string> GetFiles();
		[[nodiscard]] std::vector<Catalog*> GetCatalogs();
		[[nodiscard]] results::Result AddFile(const std::string& file);
		[[nodiscard]] results::Result AddCatalog(const std::string& catalog);
	private:
		std::string name;
		std::vector<std::string> files;
		std::vector<Catalog*> childCatalogs;
	};
}