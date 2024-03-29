#include <abstractions/Arg.hpp>
#include "IntArg.hpp"
#include <stdexcept>
#include <iostream>

namespace args
{
	IntArg::IntArg(char shortName) : abstractions::Arg(shortName, false, true) {}
	IntArg::IntArg(std::string fullName) : abstractions::Arg(fullName, false, true) {}
	IntArg::IntArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, true) {}

	std::string IntArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
			info += std::to_string(value);
		return info;
	}
	void IntArg::SetValue(int value)
	{
		this->value = value;
	}
	bool IntArg::Handle(std::string value)
	{
		if (value.empty())
		{
			std::cerr << "Error: string value is empty." << std::endl;
			return false;
		}

		int result;

		try
		{
			result = std::stoi(value);
			SetValue(result);
			Define();
			return true;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what() << value << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << e.what() << value << std::endl;
		}

		return false;
	}
}