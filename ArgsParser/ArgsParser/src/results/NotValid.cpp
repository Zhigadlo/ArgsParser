#include "NotValid.hpp"

namespace results
{
	NotValid::NotValid(std::string value) : Result(value + ": Value is not valid") {}
}