#include "EmptyArg.hpp"

namespace args
{
	EmptyArg::EmptyArg(char shortName) : abstractions::Arg(shortName, false, false) {}
	EmptyArg::EmptyArg(std::string fullName) : abstractions::Arg(fullName, false, false) {}
	EmptyArg::EmptyArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, false) {}

	results::HandleResult EmptyArg::Handle(const std::string& value)
	{
		if (IsDefined()) return results::HandleResult("Value is already defined.");
		Define();
		return results::HandleResult();
	}
}