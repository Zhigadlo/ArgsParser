#include "MultiStringArg.hpp"
#include <constants/constants.hpp>

namespace args
{
	MultiStringArg::MultiStringArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, true, true, validator) {}
	MultiStringArg::MultiStringArg(std::string fullName, abstractions::IValidator* validator ) : abstractions::Arg(fullName, true, true, validator) {}
	MultiStringArg::MultiStringArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, true, true, validator) {}

	std::string MultiStringArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (!IsDefined()) return info;

		for (int i = 0; i < values.size(); i++)
		{
			info += values[i];
			info += SpaceChar;
		}

		return info;
	}

	std::vector<std::string> MultiStringArg::GetValues() const
	{
		return values;
	}

	void MultiStringArg::SetValue(std::string value)
	{
		this->values.push_back(value);
	}

	results::Result MultiStringArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::Result::StringValueIsEmpty();
		
		abstractions::IValidator* validator = GetValidator();
		if(validator != nullptr && !validator->Validate(&value))
			return results::Result::NotValid(value);
		SetValue(value);
		Define();
		return results::Result::Success();
	}
}