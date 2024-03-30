#pragma once

#include <abstractions/Arg.hpp>
#include <stdexcept>
#include <iostream>

namespace args
{
	class IntArg : public abstractions::Arg
	{
	public:
		IntArg(char shortName);
		IntArg(std::string fullName);
		IntArg(char shortName, std::string fullName);

		std::string GetInfo() override;
		void SetValue(int value);
		bool Handle(std::string value) override;
	private:
		int value = INT_MAX;
	};
}