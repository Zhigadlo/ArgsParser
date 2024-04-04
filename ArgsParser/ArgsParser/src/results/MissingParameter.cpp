#include "MissingParameter.hpp"

namespace results
{
	MissingParameter::MissingParameter(std::string argName) : HandleResult(argName + ": Parameter is missing") {}
}