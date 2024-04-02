#include "ArgumentIsAlreadyDefined.hpp"

namespace results
{
	ArgumentIsAlreadyDefined::ArgumentIsAlreadyDefined(std::string argName) : HandleResult(argName + ": Argument is already defined") {}
}