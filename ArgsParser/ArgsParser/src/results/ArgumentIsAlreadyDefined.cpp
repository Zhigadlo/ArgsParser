#include "ArgumentIsAlreadyDefined.hpp"

namespace results
{
	ArgumentIsAlreadyDefined::ArgumentIsAlreadyDefined(char argName) : HandleResult(argName + ": Argument is already defined") {}
	ArgumentIsAlreadyDefined::ArgumentIsAlreadyDefined(std::string argName) : HandleResult(std::string(argName + ": Argument is already defined")) {}
}