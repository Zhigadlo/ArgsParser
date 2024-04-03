#include <constants/constants.hpp>
#include "Arg.hpp"

namespace abstractions
{
	Arg::Arg(char shortName, bool isReusable, bool isParamArg, abstractions::IValidator* validator = nullptr) : shortName(shortName),
																												isReusable(isReusable),
																												isParamArg(isParamArg),
																											    validator(validator) {}
	Arg::Arg(std::string fullName, bool isReusable, bool isParamArg, abstractions::IValidator* validator = nullptr) : fullName(fullName),
																													  isReusable(isReusable),
																													  isParamArg(isParamArg),
																													  validator(validator) {}
	Arg::Arg(char shortName, std::string fullName, bool isReusable, bool isParamArg, abstractions::IValidator* validator = nullptr) : shortName(shortName),
																																	  fullName(fullName), 
																																	  isReusable(isReusable),
																																	  isParamArg(isParamArg),
																																	  validator(validator) {}
	bool Arg::IsShortNameExist()
	{
		if (shortName == CHAR_MAX) return false;

		return true;
	}
	bool Arg::IsFullNameExist()
	{
		if (fullName.empty()) return false;

		return true;
	}

	std::string Arg::GetInfo()
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

	char Arg::GetShortName()
	{
		return shortName;
	}
	std::string Arg::GetFullName()
	{
		return fullName;
	}
	IValidator* Arg::GetValidator()
	{
		return validator;
	}
	bool Arg::IsDefined()
	{
		return isDefined;
	};
	bool Arg::IsReusable()
	{
		return isReusable;
	}
	bool Arg::IsParamArg()
	{
		return isParamArg;
	}
	void Arg::Define()
	{
		isDefined = true;
	}
}
