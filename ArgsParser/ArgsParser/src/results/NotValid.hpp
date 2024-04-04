#pragma once 

#include "HandleResult.hpp"

namespace results
{
	class NotValid : public HandleResult
	{
	public:
		NotValid(std::string value);
	};
}
