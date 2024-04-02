#include "ArgumentIsAlreadyDefined.hpp"

namespace results
{
	ArgumentIsAlreadyDefined::ArgumentIsAlreadyDefined(std::string argName) : HandleResult(std::string(argName + ": Argument is already defined")) {}
}