#include <abstractions/Arg.hpp>
#include "MultiStringArg.hpp"
#include <vector>
#include <iostream>

namespace args
{
	MultiStringArg::MultiStringArg(char shortName) : abstractions::Arg(shortName, true, true) {}
	MultiStringArg::MultiStringArg(std::string fullName) : abstractions::Arg(fullName, true, true) {}
	MultiStringArg::MultiStringArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, true, true) {}

	std::string MultiStringArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
		{
			for (int i = 0; i < values.size(); i++)
			{
				info += values[i];
				info += ' ';
			}
		}
		return info;
	}

	void MultiStringArg::SetValue(std::string value)
	{
		this->values.push_back(value);
	}

	bool MultiStringArg::Handle(std::string value)
	{
		if (value.empty())
		{
			std::cerr << "Error: string value is empty." << std::endl;
			return false;
		}
		SetValue(value);
		Define();
		return true;
	}
}