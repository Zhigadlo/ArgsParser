#include "NoSuchArgument.hpp"

namespace results
{
	NoSuchArgument::NoSuchArgument(std::string argName) : HandleResult(argName + ": No such argument"){}
	NoSuchArgument::NoSuchArgument(char argName) : HandleResult(argName + ": No such argument"){}
}