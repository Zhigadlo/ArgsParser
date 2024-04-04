#include "NotValid.hpp"

namespace results
{
	NotValid::NotValid(std::string value) : HandleResult(value + ": Value is not valid") {}
}