#include "ArgumentIsAlreadyDefined.hpp"

namespace results
{
	ArgumentIsAlreadyDefined::ArgumentIsAlreadyDefined(char argShortName) : HandleResult(std::string(": Argument is already defined").insert(0, 1, argShortName)) {}
	ArgumentIsAlreadyDefined::ArgumentIsAlreadyDefined(std::string argLongName) : HandleResult(std::string(argLongName + ": Argument is already defined")) {}
}