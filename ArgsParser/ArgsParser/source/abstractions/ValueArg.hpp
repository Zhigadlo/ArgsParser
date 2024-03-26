#pragma once

#include "Arg.hpp"

namespace abstractions
{
	class ValueArg : public Arg
	{
	public:
		virtual bool IsValueSet() = 0;
		ValueArg(char shortName);
		ValueArg(std::string fullName);
		ValueArg(char shortName, std::string fullName);
	};
}