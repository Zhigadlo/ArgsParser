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

	Arg* Arg::GetCopy()
	{
		Arg* copy;

		if (IsShortNameExist() && IsFullNameExist())
			copy = new Arg(GetShortName(), GetFullName());
		else if (!IsShortNameExist()) 
			copy = new Arg(GetFullName());
		else
			copy = new Arg(GetShortName());

		return copy;
	}

	std::string Arg::GetInfo()
	{
		std::string info;
		if (IsShortNameExist())
		{
			info += '-';
			info += GetShortName();
			info += ' ';
		}

		if (IsFullNameExist())
		{
			info += "--";
			info += GetFullName();
			info += ' ';
		}

		return info;
	}
	
	char Arg::GetShortName()
	{
		return shortName;
	}

	std::string Arg::GetFullName()
	{
		return fullName;
	}
};
