#include <abstractions/Arg.hpp>
#include "BoolArg.hpp"
#include <iostream>

namespace args
{
	BoolArg::BoolArg(char shortName) : abstractions::Arg(shortName, false, true) {}
	BoolArg::BoolArg(std::string fullName) : abstractions::Arg(fullName, false, true) {}
	BoolArg::BoolArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, true) {}

	std::string BoolArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
			info += value ? TrueString : FalseString;

		return info;
	}
	void BoolArg::SetValue(bool value)
	{
		this->value = value;
	}
	bool BoolArg::Handle(std::string value)
	{
		if (value.empty())
		{
			std::cerr << "Error: string value is empty." << std::endl;
			return false;
		}

		bool boolResult;
		if (!StringToBool(value, boolResult)) return false;

		SetValue(boolResult);
		Define();
		return true;
	}
	/**
	* @brief Converts string value to bool value, before string try to convert
	* string value to bool makes all string characters to lower case
	* @param str string value for converting
	* @param out pointer to variable for result
	* @return true if converting is successfull otherwise returns false
	**/
	bool BoolArg::StringToBool(const std::string& str, bool& out)
	{
		std::string trimmed_str;
		trimmed_str.reserve(str.size());

		for (char c : str)
		{
			trimmed_str.push_back(std::tolower(c));
		}

		if (trimmed_str == TrueString || trimmed_str == "1")
		{
			out = true;
			return true;
		}
		if (trimmed_str == FalseString || trimmed_str == "0")
		{
			out = false;
			return true;
		}
		std::cerr << "Error: invalid bool string value." << std::endl;
		return false;
	}
}; 