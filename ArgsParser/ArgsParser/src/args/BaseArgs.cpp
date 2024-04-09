#include "BaseArg.hpp"

namespace args
{
#pragma region BaseArg realisaton

	BaseArg::BaseArg(char shortName, bool isReusable, bool isParamArg)
		: shortName(shortName), isReusable(isReusable), isParamArg(isParamArg) {}
	BaseArg::BaseArg(std::string fullName, bool isReusable, bool isParamArg)
		: fullName(shortName), isReusable(isReusable), isParamArg(isParamArg) {}
	BaseArg::BaseArg(char shortName, std::string fullName, bool isReusable, bool isParamArg)
		: shortName(shortName), fullName(fullName), isReusable(isReusable), isParamArg(isParamArg) {}

	bool BaseArg::IsShortNameExist() const
	{
		if (shortName == CHAR_MAX) return false;

		return true;
	}
	bool BaseArg::IsFullNameExist() const
	{
		if (fullName.empty()) return false;

		return true;
	}
	std::string BaseArg::GetInfo() const
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
	char BaseArg::GetShortName() const
	{
		return shortName;
	}
	const std::string& GetFullName() const
	{
		return fullName;
	}

	bool BaseArg::IsDefined() const
	{
		return isDefined;
	};
	bool BaseArg::IsReusable() const
	{
		return isReusable;
	}
	bool BaseArg::IsParamArg() const
	{
		return isParamArg;
	}
	void BaseArg::Define()
	{
		isDefined = true;
	}

#pragma endregion
#pragma region EmptyArg realisation

	EmptyArg::EmptyArg(char shortName, bool isReusable) : BaseArg(shortName, isReusable, false) {}
	EmptyArg::EmptyArg(std::string fullName, bool isReusable) : BaseArg(fullName, isReusable, false) {}
	EmptyArg::EmptyArg(char shortName, std::string fullName, bool isReusable) : BaseArg(shortName, fullName, isReusable, false) {}

	results::Result EmptyArg::Handle(const std::string& value)
	{
		if (IsDefined()) return results::Result::ArgumentIsAlreadyDefined(GetInfo());
		Define();
		return results::Result::Success();
	}
	bool EmptyArg::IsValidatorExist() const
	{
		return false;
	}
	bool EmptyArg::Validate()
	{
		return true;
	}

#pragma endregion
#pragma region HelpArg realisation
	HelpArg::HelpArg(char shortName, const std::vector<Arg*>& args)
		: EmptyArg(shortName, true), allArgs(args) {}
	HelpArg::HelpArg(std::string fullName, const std::vector<Arg*>& args)
		: EmptyArg(fullName, true), allArgs(args) {}
	HelpArg::HelpArg(char shortName, std::string fullName, const std::vector<Arg*>& args)
		: EmptyArg(shortName, fullName, true), allArgs(args) {}

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
#pragma region ValueArg realisation
	template<typename T>
	ValueArg::ValueArg(char shortName, bool isReusable, bool isParamArg, validators::Validator<T>* validator) 
		: BaseArg(shortName, isReusable, isParamArg), validator(validator) {}
	template<typename T>
	ValueArg::ValueArg(std::string fullName, bool isReusable, bool isParamArg, validators::Validator<T>* validator) 
		: BaseArg(fullName, isReusable, isParamArg), validator(validator) {}
	template<typename T>
	ValueArg::ValueArg(char shortName, std::string fullName, bool isReusable, bool isParamArg, validators::Validator<T>* validator)
		: BaseArg(shortName, fullName, isReusable, isParamArg), validator(validator) {}
	template<typename T>
	T ValueArg<T>::GetValue() const
	{
		return value;
	}

	bool ValueArg::IsValidatorExist() const
	{
		if (validator == nullptr) return false;
		return true;
	}
	virtual results::Result Handle(const std::string& value) override
	{

	}
	virtual std::string GetInfo() const override
	{
		std::string IntArg::GetInfo() const
		{
			std::string info = Arg::GetInfo();
			info += std::to_string(GetValue());
			return info;
		}
	}
#pragma endregion
}