#include <string>
#include "Arg.hpp"

namespace abstractions
{
	Arg::Arg(char shortName)
	{
		this->shortName = shortName;
	}
	Arg::Arg(std::string fullName)
	{
		this->fullName = fullName;
	}
	Arg::Arg(char shortName, std::string fullName)
	{
		this->shortName = shortName;
		this->fullName = fullName;
	}
	bool Arg::IsShortNameExist()
	{
		if (shortName == CHAR_MAX) return false;

		return true;
	}
	bool Arg::IsFullNameExist()
	{
		if (fullName.empty()) return false;

		return true;
	}

	char Arg::GetShortName()
	{
		return this->shortName;
	}

	std::string Arg::GetFullName()
	{
		return Arg::fullName;
	}
};
