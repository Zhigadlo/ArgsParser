#include "MissingParameter.hpp"

namespace results
{
	MissingParameter::MissingParameter(char argName) : HandleResult(argName + ": Parameter is missing") {}
	MissingParameter::MissingParameter(std::string argName) : HandleResult(argName + ": Parameter is missing") {}
}