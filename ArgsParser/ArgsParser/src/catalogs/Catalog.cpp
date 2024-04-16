#include "Catalog.hpp"
#include <utils/constants.hpp>
#include <sstream>

namespace catalogs
{
	Catalog::Catalog(std::filesystem::path fullPath) : fullPath(std::move(fullPath)) {}
	Catalog::Catalog(std::filesystem::path fullPath,
		int catalogLevel) : fullPath(std::move(fullPath)),
		catalogLevel(catalogLevel) {}

	const std::filesystem::path& Catalog::GetFullPath()
	{
		return fullPath;
	}
	const std::string& Catalog::GetInfo()
	{
		std::stringstream ss;
		for (int j = 0; j < catalogLevel; j++)
			ss << utils::SpaceChar;
		ss << fullPath.filename().string() << std::endl;
		if (files.size() > 0)
		{
			for (size_t i = 0; i < files.size(); i++)
			{
				for (int j = 0; j < catalogLevel + 1; j++)
					ss << utils::SpaceChar;
				ss << files[i].filename().string() << std::endl;
			}
		}

		if (childCatalogs.size() > 0)
		{
			for (Catalog catalog : childCatalogs)
			{
				for (int j = 0; j < catalogLevel + 1; j++)
					ss << utils::SpaceChar;
				ss << catalog.GetInfo();
			}
		}

		return ss.str();
	}
	std::vector<std::filesystem::path>& Catalog::GetFiles()
	{
		return files;
	}
	std::list<Catalog>& Catalog::GetCatalogs()
	{
		return childCatalogs;
	}
	void Catalog::AddFile(const std::filesystem::path& fullPath)
	{
		files.push_back(fullPath);
	}
	void Catalog::AddCatalog(const std::filesystem::path& fullPath)
	{
		Catalog newCatalog(fullPath, catalogLevel + 1);
		childCatalogs.push_back(newCatalog);
	}

	void Catalog::FindFiles()
	{
		for (auto const& dir_entry : std::filesystem::directory_iterator{ fullPath })
		{
			if (dir_entry.is_directory())
				AddCatalog(dir_entry.path());
			else
				AddFile(dir_entry.path());
		}
	}
}