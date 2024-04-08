#include "EmptyArg.hpp"

namespace args
{
	EmptyArg::EmptyArg(char shortName) : abstractions::Arg(shortName, false, false, nullptr) {}
	EmptyArg::EmptyArg(std::string fullName) : abstractions::Arg(fullName, false, false, nullptr) {}
	EmptyArg::EmptyArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, false, nullptr) {}

	results::Result EmptyArg::Handle(const std::string& value)
	{
		if (IsDefined()) return results::Result::ArgumentIsAlreadyDefined(GetInfo());
		Define();
		return results::Result::Success();
	}
}