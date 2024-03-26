#pragma once

#include <string>

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

		virtual bool IsValueExist() = 0;

		virtual std::string GetInfo() = 0;
	private:
		char shortName = CHAR_MAX;
		std::string fullName;
	};
}