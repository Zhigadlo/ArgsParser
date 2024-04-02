#pragma once

#include "HandleResult.hpp"

namespace results
{
	class MissingParameter : public HandleResult
	{
	public:
		MissingParameter(std::string argName);
	};
}

