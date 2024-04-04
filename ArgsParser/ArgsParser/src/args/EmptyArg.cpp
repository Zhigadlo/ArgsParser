#include "EmptyArg.hpp"
#include <results/ArgumentIsAlreadyDefined.hpp>
#include <results/Success.hpp>

namespace args
{
	EmptyArg::EmptyArg(char shortName) : abstractions::Arg(shortName, false, false, nullptr) {}
	EmptyArg::EmptyArg(std::string fullName) : abstractions::Arg(fullName, false, false, nullptr) {}
	EmptyArg::EmptyArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, false, nullptr) {}

	results::HandleResult EmptyArg::Handle(const std::string& value)
	{
		if (IsDefined()) return results::ArgumentIsAlreadyDefined(GetInfo());
		Define();
		return results::Success();
	}

	std::string& EmptyArg::GetValue()
	{
		std::string strValue;
		return strValue;
	}
}