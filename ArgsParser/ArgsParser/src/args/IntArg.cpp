#include "IntArg.hpp"
#include <results/StringValueIsEmpty.hpp>
#include <results/NotValid.hpp>
#include <results/Success.hpp>
#include <stdexcept>

namespace args
{
	IntArg::IntArg(char shortName, abstractions::IValidator* validator ) : abstractions::Arg(shortName, false, true, validator) {}
	IntArg::IntArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, false, true, validator) {}
	IntArg::IntArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, false, true, validator) {}

	std::string IntArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		info += GetValue();
		return info;
	}
	void IntArg::SetValue(int value)
	{
		this->value = value;
	}
	/**
	* @brief If value is not defined returns INT_MAX
	**/
	int IntArg::GetValue() const
	{
		return value;
	}
	results::Result IntArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::StringValueIsEmpty();
		
		try
		{
			int result = std::stoi(value);
			abstractions::IValidator* validator = GetValidator();
			if (validator != nullptr && !validator->Validate(&result))
				return results::NotValid(std::to_string(result));
			SetValue(result);
			Define();
			return results::Success();
		}
		catch (const std::invalid_argument& e)
		{
			return results::Result(e.what());
		}
		catch (const std::out_of_range& e)
		{
			return results::Result(e.what());
		}
	}
}