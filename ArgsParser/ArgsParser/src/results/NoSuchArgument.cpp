#include "NoSuchArgument.hpp"

namespace results
{
	NoSuchArgument::NoSuchArgument(std::string argName) : Result(argName + ": No such argument") {}
}