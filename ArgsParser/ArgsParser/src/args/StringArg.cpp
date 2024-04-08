#include "StringArg.hpp"
#include <abstractions/Arg.hpp>

namespace args
{
	StringArg::StringArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, false, true, validator) {}
	StringArg::StringArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, false, true, validator) {}
	StringArg::StringArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, false, true, validator) {}

	std::string StringArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
			info += GetValue();

		return info;
	}

	std::string StringArg::GetValue() const
	{
		return value;
	}

	void StringArg::SetValue(std::string value)
	{
		this->value = value;
	}

	results::Result StringArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::Result::StringValueIsEmpty();

		abstractions::IValidator* validator = GetValidator();
		if (validator != nullptr && !validator->Validate(&value))
			return results::Result::NotValid(value);
		SetValue(value);
		Define();
		return results::Result::Success();
	}
}