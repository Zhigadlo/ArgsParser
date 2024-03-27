#pragma once

#include <string>
#include <vector>

namespace abstractions
{
	/**
	* @brief Class for arguments without parameters
	**/
	class Arg
	{
	public:
		Arg(char shortName, std::string fullName);
		Arg(char shortName);
		Arg(std::string fullName);

		char GetShortName();
		std::string GetFullName();

		bool IsShortNameExist();
		bool IsFullNameExist();
		/**
		* @warning Make sure to call this fuction after argument defined
		**/
		void Define();
		bool IsDefined();
		
		virtual std::string GetInfo();
	private:
		char shortName = CHAR_MAX;
		std::string fullName;
		bool isDefined = false;
	};
}