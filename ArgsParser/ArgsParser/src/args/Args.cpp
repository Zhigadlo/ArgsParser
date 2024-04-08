#include "Args.hpp"
#include <constants/constants.hpp>
#include <sstream>

namespace args
{
	// Bool arg realisation
	BoolArg::BoolArg(char shortName) : abstractions::Arg(shortName, false, true, nullptr) {}
	BoolArg::BoolArg(std::string fullName) : abstractions::Arg(fullName, false, true, nullptr) {}
	BoolArg::BoolArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, true, nullptr) {}

	std::string BoolArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
			info += value ? TrueString : FalseString;

		return info;
	}

	bool BoolArg::GetValue() const
	{
		return value;
	}
	void BoolArg::SetValue(bool value)
	{
		this->value = value;
	}
	results::Result BoolArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::Result::StringValueIsEmpty();

		bool boolResult;
		if (!StringToBool(value, boolResult)) return results::Result::ConvertFail("string", "bool");

		SetValue(boolResult);
		Define();
		return results::Result::Success();
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

	// Empty arg realisation
	EmptyArg::EmptyArg(char shortName) : abstractions::Arg(shortName, false, false, nullptr) {}
	EmptyArg::EmptyArg(std::string fullName) : abstractions::Arg(fullName, false, false, nullptr) {}
	EmptyArg::EmptyArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, false, nullptr) {}

	results::Result EmptyArg::Handle(const std::string& value)
	{
		if (IsDefined()) return results::Result::ArgumentIsAlreadyDefined(GetInfo());
		Define();
		return results::Result::Success();
	}

	// Help arg realisation
	HelpArg::HelpArg(char shortName, const std::vector<abstractions::Arg*>& args) : abstractions::Arg(shortName, true, false, nullptr), allArgs(args) {}
	HelpArg::HelpArg(std::string fullName, const std::vector<abstractions::Arg*>& args) : abstractions::Arg(fullName, true, false, nullptr), allArgs(args) {}
	HelpArg::HelpArg(char shortName, std::string fullName, const std::vector<abstractions::Arg*>& args) : abstractions::Arg(shortName, fullName, true, false, nullptr), allArgs(args) {}

	std::string HelpArg::GetInfo()
	{
		std::stringstream ss;
		ss << "Arguments info" << std::endl;
		ss << "--------------------" << std::endl;

		for (int i = 0; i < allArgs.size(); i++)
		{
			if (allArgs[i]->IsShortNameExist()) ss << ShortArgumentPrefix << allArgs[i]->GetShortName() << SpaceChar;

			if (allArgs[i]->IsFullNameExist()) ss << LongArgumentPrefix << allArgs[i]->GetFullName() << SpaceChar;

			ss << std::endl;
		}
		ss << "--------------------" << std::endl;

		return ss.str();
	}

	results::Result HelpArg::Handle(const std::string& value)
	{
		if (!IsDefined()) Define();
		return results::Result::Success();
	}

	// Int arg realisation
	IntArg::IntArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, false, true, validator) {}
	IntArg::IntArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, false, true, validator) {}
	IntArg::IntArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, false, true, validator) {}

	std::string IntArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		info += std::to_string(GetValue());
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
		if (value.empty()) return results::Result::StringValueIsEmpty();

		try
		{
			int result = std::stoi(value);
			abstractions::IValidator* validator = GetValidator();
			if (validator != nullptr && !validator->Validate(&result))
				return results::Result::NotValid(std::to_string(result));
			SetValue(result);
			Define();
			return results::Result::Success();
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

	// String arg realisation

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

	// Multi empty arg
	MultiEmptyArg::MultiEmptyArg(char shortName) : abstractions::Arg(shortName, true, false, nullptr) {}
	MultiEmptyArg::MultiEmptyArg(std::string fullName) : abstractions::Arg(fullName, true, false, nullptr) {}
	MultiEmptyArg::MultiEmptyArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, true, false, nullptr) {}

	std::string MultiEmptyArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
			info += std::to_string(handleCount);

		return info;
	}

	int MultiEmptyArg::GetHandleCount() const
	{
		return handleCount;
	}

	results::Result MultiEmptyArg::Handle(const std::string& value)
	{
		if (!IsDefined()) Define();
		handleCount++;
		return results::Result::Success();
	}

	// Multi int arg realisation

	MultiIntArg::MultiIntArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, true, true, validator) {}
	MultiIntArg::MultiIntArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, true, true, validator) {}
	MultiIntArg::MultiIntArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, true, true, validator) {}

	std::string MultiIntArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (!IsDefined()) return info;

		for (int i = 0; i < values.size(); i++)
		{
			info += std::to_string(values[i]);
			info += SpaceChar;
		}

		return info;
	}

	std::vector<int> MultiIntArg::GetValues() const
	{
		return values;
	}

	void MultiIntArg::SetValue(int value)
	{
		this->values.push_back(value);
	}

	results::Result MultiIntArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::Result::StringValueIsEmpty();
		try
		{
			int result = std::stoi(value);
			abstractions::IValidator* validator = GetValidator();
			if (validator != nullptr && !validator->Validate(&result))
				return results::Result::NotValid(std::to_string(result));
			this->values.push_back(result);
			Define();
			return results::Result::Success();
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

	// Multi string arg realisation

	MultiStringArg::MultiStringArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, true, true, validator) {}
	MultiStringArg::MultiStringArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, true, true, validator) {}
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
		if (validator != nullptr && !validator->Validate(&value))
			return results::Result::NotValid(value);
		SetValue(value);
		Define();
		return results::Result::Success();
	}
}