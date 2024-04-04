#pragma once

#include <abstractions/Arg.hpp>

namespace args
{
	class EmptyArg : public abstractions::Arg
	{
	public:
		EmptyArg(char shortName);
		EmptyArg(std::string fullName);
		EmptyArg(char shortName, std::string fullName);

		results::HandleResult Handle(const std::string& value) override;
	};
}