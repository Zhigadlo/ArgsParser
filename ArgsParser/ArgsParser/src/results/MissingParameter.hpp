#pragma once

#include "HandleResult.hpp"

namespace results
{
	class MissingParameter : public Result
	{
	public:
		MissingParameter(std::string argName);
	};
}

