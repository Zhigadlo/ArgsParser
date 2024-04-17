#pragma once 

#include <list>
#include <vector>
#include <string>
#include <filesystem>
#include <thread>

namespace catalogs
{
	class Catalog
	{
	public:
		Catalog(std::filesystem::path fullPath);
		Catalog(std::filesystem::path fullPath, int catalogLevel);

		[[nodiscard]] const std::filesystem::path& GetFullPath() const;
		[[nodiscard]] const std::vector<std::filesystem::path>& GetFiles() const;
		[[nodiscard]] std::list<Catalog>& GetCatalogs();
		void AddFile(const std::filesystem::path& fullPath);
		void AddCatalog(const std::filesystem::path& fullPath);
		void FindFiles();
		void ShowInfo() const;
		void SetThreadIndex(std::thread::id index);
	private:
		std::filesystem::path fullPath;
		std::vector<std::filesystem::path> files;
		std::list<Catalog> childCatalogs;
		int catalogLevel = 0;
		std::thread::id threadIndex;
	};
}