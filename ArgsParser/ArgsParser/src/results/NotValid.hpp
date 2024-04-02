#pragma once 

#include "HandleResult.hpp"

namespace results
{
	public NotValid : public HandleResult
	{
	public:
		NotValid(std::string argName);
	};
}
