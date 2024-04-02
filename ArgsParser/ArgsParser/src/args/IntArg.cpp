#include "IntArg.hpp"
#include <results/StringValueIsEmpty.hpp>
#include <results/Success.hpp>
#include <stdexcept>

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
	results::HandleResult IntArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::StringValueIsEmpty();
		
		try
		{
			int result = std::stoi(value);
			SetValue(result);
			Define();
			return results::Success();
		}
		catch (const std::invalid_argument& e)
		{
			return results::HandleResult(e.what());
		}
		catch (const std::out_of_range& e)
		{
			return results::HandleResult(e.what());
		}
	}
}