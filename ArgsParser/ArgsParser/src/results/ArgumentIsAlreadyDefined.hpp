#pragma once

#include "HandleResult.hpp"

namespace results
{
	class ArgumentIsAlreadyDefined : public HandleResult
	{
	public:
		ArgumentIsAlreadyDefined(std::string argLongName);
	};
}

