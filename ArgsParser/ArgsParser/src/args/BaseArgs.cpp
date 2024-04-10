#include "BaseArg.hpp"
#include <utils/constants.hpp>

namespace args
{
#pragma region BaseArg realisaton

	BaseArg::BaseArg(char shortName, bool isReusable, bool isParamArg)
		: shortName(shortName), isReusable(isReusable), isParamArg(isParamArg)
	{
	}
	BaseArg::BaseArg(std::string fullName, bool isReusable, bool isParamArg)
		: fullName(fullName), isReusable(isReusable), isParamArg(isParamArg)
	{
	}
	BaseArg::BaseArg(char shortName, std::string fullName, bool isReusable, bool isParamArg)
		: shortName(shortName), fullName(fullName), isReusable(isReusable), isParamArg(isParamArg)
	{
	}

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
			info += utils::ShortArgumentPrefix;
			info += GetShortName();
			info += utils::SpaceChar;
		}

		if (IsFullNameExist())
		{
			info += utils::LongArgumentPrefix;
			info += GetFullName();
			info += utils::SpaceChar;
		}

		return info;
	}
	char BaseArg::GetShortName() const
	{
		return shortName;
	}
	const std::string& BaseArg::GetFullName() const
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

#pragma endregion
#pragma region HelpArg realisation
	HelpArg::HelpArg(char shortName, const std::vector<BaseArg*>& args)
		: EmptyArg(shortName, true), allArgs(args)
	{
	}
	HelpArg::HelpArg(std::string fullName, const std::vector<BaseArg*>& args)
		: EmptyArg(fullName, true), allArgs(args)
	{
	}
	HelpArg::HelpArg(char shortName, std::string fullName, const std::vector<BaseArg*>& args)
		: EmptyArg(shortName, fullName, true), allArgs(args)
	{
	}

	std::string HelpArg::GetInfo() const
	{
		std::string str;
		str += "Arguments info\n";
		str += "--------------------\n";

		for (int i = 0; i < allArgs.size(); i++)
		{
			if (allArgs[i]->IsShortNameExist()) 
				str += utils::ShortArgumentPrefix + allArgs[i]->GetShortName() + utils::SpaceChar;

			if (allArgs[i]->IsFullNameExist()) 
				str += utils::LongArgumentPrefix + allArgs[i]->GetFullName() + utils::SpaceChar;

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
}