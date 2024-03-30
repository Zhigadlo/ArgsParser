#include "MultiStringArg.hpp"
#include <constants/constants.hpp>

namespace args
{
	MultiStringArg::MultiStringArg(char shortName) : abstractions::Arg(shortName, true, true) {}
	MultiStringArg::MultiStringArg(std::string fullName) : abstractions::Arg(fullName, true, true) {}
	MultiStringArg::MultiStringArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, true, true) {}

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

	void MultiStringArg::SetValue(std::string value)
	{
		this->values.push_back(value);
	}

	results::HandleResult MultiStringArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::HandleResult("String value is empty");
		
		SetValue(value);
		Define();
		return results::HandleResult();
	}
}