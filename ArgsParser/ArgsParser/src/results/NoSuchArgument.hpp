#pragma once

#include "HandleResult.hpp"
namespace results
{
	class NoSuchArgument : public HandleResult
	{
	public:
		NoSuchArgument(std::string argName);
	};
}

