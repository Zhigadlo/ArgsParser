#pragma once

#include "HandleResult.hpp"

namespace results
{
	class MissingParameter : public HandleResult
	{
	public:
		MissingParameter(char argName);
		MissingParameter(std::string argName);
	};
}

