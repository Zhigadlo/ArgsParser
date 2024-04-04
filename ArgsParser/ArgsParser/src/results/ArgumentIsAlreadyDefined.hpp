#pragma once

#include "HandleResult.hpp"

namespace results
{
	class ArgumentIsAlreadyDefined : public Result
	{
	public:
		ArgumentIsAlreadyDefined(std::string argLongName);
	};
}

