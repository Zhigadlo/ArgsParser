#include "MissingParameter.hpp"

namespace results
{
	MissingParameter::MissingParameter(std::string argName) : Result(argName + ": Parameter is missing") {}
}