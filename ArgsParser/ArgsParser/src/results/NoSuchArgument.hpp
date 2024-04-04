#pragma once

#include "HandleResult.hpp"
namespace results
{
	class NoSuchArgument : public Result
	{
	public:
		NoSuchArgument(std::string argName);
	};
}

