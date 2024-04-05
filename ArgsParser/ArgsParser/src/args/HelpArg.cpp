#include "HelpArg.hpp"
#include <results/ArgumentIsAlreadyDefined.hpp>
#include <results/Success.hpp>
#include <abstractions/Arg.hpp>
#include <constants/constants.hpp>
#include <sstream>

namespace args
{
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
		return results::Success();
	}
}