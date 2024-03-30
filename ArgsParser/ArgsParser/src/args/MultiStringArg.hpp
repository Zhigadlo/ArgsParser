#pragma once

#include <abstractions/Arg.hpp>

namespace args
{
	class MultiStringArg : public abstractions::Arg
	{
	public:
		MultiStringArg(char shortName);
		MultiStringArg(std::string fullName);
		MultiStringArg(char shortName, std::string fullName);

		std::string GetInfo() override;
		void SetValue(std::string value);

		results::HandleResult Handle(const std::string& value) override;
	private:
		std::vector<std::string> values;
	};
}