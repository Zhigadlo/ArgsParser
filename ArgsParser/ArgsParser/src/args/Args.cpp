#include "Args.hpp"
#include <constants/constants.hpp>
#include <results/Result.hpp>
#include <sstream>

namespace args
{
#pragma region Abstract arg realisation
	Arg::Arg(char shortName, bool isReusable, bool isParamArg, std::unique_ptr<validators::IValidator> validator = nullptr) : shortName(shortName),
		isReusable(isReusable),
		isParamArg(isParamArg),
		validator(std::move(validator))
	{
	}
	Arg::Arg(std::string fullName, bool isReusable, bool isParamArg, std::unique_ptr<validators::IValidator> validator = nullptr) : fullName(fullName),
		isReusable(isReusable),
		isParamArg(isParamArg),
		validator(std::move(validator))
	{
	}
	Arg::Arg(char shortName, std::string fullName, bool isReusable, bool isParamArg, std::unique_ptr<validators::IValidator> validator = nullptr) : shortName(shortName),
		fullName(fullName),
		isReusable(isReusable),
		isParamArg(isParamArg),
		validator(std::move(validator))
	{
	}
	bool Arg::IsShortNameExist() const
	{
		if (shortName == CHAR_MAX) return false;

		return true;
	}
	bool Arg::IsFullNameExist() const
	{
		if (fullName.empty()) return false;

		return true;
	}

	std::string Arg::GetInfo() const
	{
		std::string info;
		if (IsShortNameExist())
		{
			info += ShortArgumentPrefix;
			info += GetShortName();
			info += SpaceChar;
		}

		if (IsFullNameExist())
		{
			info += LongArgumentPrefix;
			info += GetFullName();
			info += SpaceChar;
		}

		return info;
	}

	char Arg::GetShortName() const
	{
		return shortName;
	}
	const std::string& Arg::GetFullName() const
	{
		return fullName;
	}
	validators::IValidator* Arg::GetValidator() const
	{
		return validator.get();
	}
	bool Arg::IsDefined() const
	{
		return isDefined;
	};
	bool Arg::IsReusable() const
	{
		return isReusable;
	}
	bool Arg::IsParamArg() const
	{
		return isParamArg;
	}
	void Arg::Define()
	{
		isDefined = true;
	}
#pragma endregion
#pragma region Bool arg realisation
	BoolArg::BoolArg(char shortName) : Arg(shortName, false, true, nullptr) {}
	BoolArg::BoolArg(std::string fullName) : Arg(fullName, false, true, nullptr) {}
	BoolArg::BoolArg(char shortName, std::string fullName) : Arg(shortName, fullName, false, true, nullptr) {}

	std::string BoolArg::GetInfo() const
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
#pragma endregion
#pragma region Empty arg realisation
	EmptyArg::EmptyArg(char shortName) : Arg(shortName, false, false, nullptr) {}
	EmptyArg::EmptyArg(std::string fullName) : Arg(fullName, false, false, nullptr) {}
	EmptyArg::EmptyArg(char shortName, std::string fullName) : Arg(shortName, fullName, false, false, nullptr) {}

	results::Result EmptyArg::Handle(const std::string& value)
	{
		if (IsDefined()) return results::Result::ArgumentIsAlreadyDefined(GetInfo());
		Define();
		return results::Result::Success();
	}
#pragma endregion
#pragma region Help arg realisation
	HelpArg::HelpArg(char shortName, const std::vector<Arg*>& args) : Arg(shortName, true, false, nullptr), allArgs(args) {}
	HelpArg::HelpArg(std::string fullName, const std::vector<Arg*>& args) : Arg(fullName, true, false, nullptr), allArgs(args) {}
	HelpArg::HelpArg(char shortName, std::string fullName, const std::vector<Arg*>& args) : Arg(shortName, fullName, true, false, nullptr), allArgs(args) {}

	std::string HelpArg::GetInfo() const
	{
		std::string str;
		str += "Arguments info\n";
		str += "--------------------\n";

		for (int i = 0; i < allArgs.size(); i++)
		{
			if (allArgs[i]->IsShortNameExist()) str += ShortArgumentPrefix + allArgs[i]->GetShortName() + SpaceChar;

			if (allArgs[i]->IsFullNameExist()) str += LongArgumentPrefix + allArgs[i]->GetFullName() + SpaceChar;

			str += "\n";
		}
		str += "--------------------\n";

		return str;
	}

	results::Result HelpArg::Handle(const std::string& value)
	{
		if (!IsDefined()) Define();
		return results::Result::Success();
	}
#pragma endregion
#pragma region Int arg realisation
	IntArg::IntArg(char shortName, std::unique_ptr<validators::IValidator> validator = nullptr) : Arg(shortName, false, true, std::move(validator)) {}
	IntArg::IntArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr) : Arg(fullName, false, true, std::move(validator)) {}
	IntArg::IntArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr) : Arg(shortName, fullName, false, true, std::move(validator)) {}

	std::string IntArg::GetInfo() const
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
			validators::IValidator* validator = GetValidator();
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
#pragma endregion
#pragma region String arg realisation

	StringArg::StringArg(char shortName, std::unique_ptr<validators::IValidator> validator = nullptr) : Arg(shortName, false, true, std::move(validator)) {}
	StringArg::StringArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr) : Arg(fullName, false, true, std::move(validator)) {}
	StringArg::StringArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr) : Arg(shortName, fullName, false, true, std::move(validator)) {}

	std::string StringArg::GetInfo() const
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
			info += GetValue();

		return info;
	}

	const std::string& StringArg::GetValue() const
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

		validators::IValidator* validator = GetValidator();
		if (validator != nullptr && !validator->Validate(&value))
			return results::Result::NotValid(value);
		SetValue(value);
		Define();
		return results::Result::Success();
	}
#pragma endregion
#pragma region Multi empty arg
	MultiEmptyArg::MultiEmptyArg(char shortName) : Arg(shortName, true, false, std::unique_ptr<validators::IValidator>()) {}
	MultiEmptyArg::MultiEmptyArg(std::string fullName) : Arg(fullName, true, false, std::unique_ptr<validators::IValidator>()) {}
	MultiEmptyArg::MultiEmptyArg(char shortName, std::string fullName) : Arg(shortName, fullName, true, false, std::unique_ptr<validators::IValidator>()) {}

	std::string MultiEmptyArg::GetInfo() const
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
#pragma endregion
#pragma region Multi int arg realisation

	MultiIntArg::MultiIntArg(char shortName, std::unique_ptr<validators::IValidator> validator = std::unique_ptr<validators::IValidator>()) : Arg(shortName, true, true, std::move(validator)) {}
	MultiIntArg::MultiIntArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = std::unique_ptr<validators::IValidator>()) : Arg(fullName, true, true, std::move(validator)) {}
	MultiIntArg::MultiIntArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = std::unique_ptr<validators::IValidator>()) : Arg(shortName, fullName, true, true, std::move(validator)) {}

	std::string MultiIntArg::GetInfo() const
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

	const std::vector<int>& MultiIntArg::GetValues() const
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
			validators::IValidator* validator = GetValidator();
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
#pragma endregion
#pragma region Multi string arg realisation

	MultiStringArg::MultiStringArg(char shortName, std::unique_ptr<validators::IValidator> validator = std::unique_ptr<validators::IValidator>()) : Arg(shortName, true, true, std::move(validator)) {}
	MultiStringArg::MultiStringArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = std::unique_ptr<validators::IValidator>()) : Arg(fullName, true, true, std::move(validator)) {}
	MultiStringArg::MultiStringArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = std::unique_ptr<validators::IValidator>()) : Arg(shortName, fullName, true, true, std::move(validator)) {}

	std::string MultiStringArg::GetInfo() const
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

		validators::IValidator* validator = GetValidator();
		if (validator != nullptr && !validator->Validate(&value))
			return results::Result::NotValid(value);
		SetValue(value);
		Define();
		return results::Result::Success();
	}
#pragma endregion
}