#pragma once

#include "Arg.hpp"

namespace abstractions
{
	class ValueArg : public Arg
	{
	public:
		ValueArg(char shortName);
		ValueArg(std::string fullName);
		ValueArg(char shortName, std::string fullName);

		virtual bool ValueHandling(std::string value) = 0;
		virtual bool IsValueSet() = 0;
	};
}