#include "EmptyArg.hpp"

namespace args
{
	EmptyArg::EmptyArg(char shortName) : abstractions::Arg(shortName, false, false) {}
	EmptyArg::EmptyArg(std::string fullName) : abstractions::Arg(fullName, false, false) {}
	EmptyArg::EmptyArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, false, false) {}

	bool EmptyArg::Handle(std::string value)
	{
		if (IsDefined()) return false;
		Define();
		return true;
	}
}