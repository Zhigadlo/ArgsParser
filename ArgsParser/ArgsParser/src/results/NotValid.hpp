#pragma once 

#include "HandleResult.hpp"

namespace results
{
	class NotValid : public Result
	{
	public:
		NotValid(std::string value);
	};
}
