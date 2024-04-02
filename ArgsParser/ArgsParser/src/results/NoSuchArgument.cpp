#include "NoSuchArgument.hpp"

namespace results
{
	NoSuchArgument::NoSuchArgument(std::string argName) : HandleResult(argName + ": No such argument") {}
}