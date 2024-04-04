#include "ArgumentIsAlreadyDefined.hpp"

namespace results
{
	ArgumentIsAlreadyDefined::ArgumentIsAlreadyDefined(std::string argName) : Result(argName + ": Argument is already defined") {}
}