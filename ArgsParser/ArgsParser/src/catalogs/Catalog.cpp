#include "Catalog.hpp"
#include <sstream>

namespace catalogs
{
	Catalog::Catalog(std::string name) : name(std::move(name)) {}
	Catalog::Catalog(std::string name, 
				     int catalogLevel) : name(std::move(name)),
									     catalogLevel(catalogLevel) {}

	std::string Catalog::GetName()
	{
		return name;
	}
	std::string Catalog::GetInfo()
	{
		std::stringstream ss;
		ss << name;
		for (size_t i = 0; i < files.size(); i++)
		{
			for (int j = 0; j < catalogLevel; j++)
				ss << "\t";
			ss << files[i] << std::endl;
		}
		return ss.str();
	}
	std::vector<std::string>& Catalog::GetFiles()
	{
		return files;
	}
	std::list<Catalog*>& Catalog::GetCatalogs()
	{
		return childCatalogs;
	}
	void Catalog::AddFile(const std::string& file)
	{
		files.push_back(file);
	}
	void Catalog::AddCatalog(const std::string& catalog)
	{
		Catalog newCatalog(catalog, catalogLevel + 1);
		childCatalogs.push_back(&newCatalog);
	}
}