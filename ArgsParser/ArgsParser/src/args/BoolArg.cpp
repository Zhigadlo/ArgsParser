#include <constants/constants.hpp>
#include <results/Success.hpp>
#include <results/StringValueIsEmpty.hpp>
#include "BoolArg.hpp"

namespace args
{
	BoolArg::BoolArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, false, true, validator) {}
	BoolArg::BoolArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, false, true, validator) {}
	BoolArg::BoolArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, false, true, validator) {}

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
	results::HandleResult BoolArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::StringValueIsEmpty();
		
		bool boolResult;
		if (!StringToBool(value, boolResult)) return results::HandleResult("Failed to convert string value to bool");

		SetValue(boolResult);
		Define();
		return results::Success();
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
			trimmed_str.push_back(std::tolower(c));
		
		if (trimmed_str == TrueString || trimmed_str == TrueIntString)
		{
			out = true;
			return true;
		}
		if (trimmed_str == FalseString || trimmed_str == FalseIntString)
		{
			out = false;
			return true;
		}
		
		return false;
	}
}; 