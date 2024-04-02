#include "NotValid.hpp"

namespace results
{
public:
	NotValid::NotValid(std::string argName) : HandleResult(argName + ": Value is not valid");
}