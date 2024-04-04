#include "StringArg.hpp"
#include <abstractions/Arg.hpp>
#include <results/StringValueIsEmpty.hpp>
#include <results/NotValid.hpp>
#include <results/Success.hpp>

namespace args
{
	StringArg::StringArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, true, true, validator) {}
	StringArg::StringArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, true, true, validator) {}
	StringArg::StringArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, true, true, validator) {}

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
		if (value.empty()) return results::StringValueIsEmpty();

		abstractions::IValidator* validator = GetValidator();
		if (validator != nullptr && !validator->Validate(&value))
			return results::NotValid(value);
		SetValue(value);
		Define();
		return results::Success();
	}
}