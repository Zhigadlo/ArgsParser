#include "ValueArg.hpp"

namespace abstractions
{
	ValueArg::ValueArg(char shortName) : Arg(shortName) {}
	ValueArg::ValueArg(std::string fullName) : Arg(fullName) {}
	ValueArg::ValueArg(char shortName, std::string fullName) : Arg(shortName, fullName) {}
}