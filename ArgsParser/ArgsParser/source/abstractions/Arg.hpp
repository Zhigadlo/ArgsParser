#pragma once

#include <string>
#include <vector>

namespace abstractions
{
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

		virtual Arg* GetCopy();
		virtual std::string GetInfo();
	private:
		char shortName = CHAR_MAX;
		std::string fullName;
	};
}