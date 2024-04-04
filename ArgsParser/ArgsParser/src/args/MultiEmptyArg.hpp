#pragma once

#include <abstractions/Arg.hpp>

namespace args
{
	class MultiEmptyArg : public abstractions::Arg
	{
	public:
		MultiEmptyArg(char shortName);
		MultiEmptyArg(std::string fullName);
		MultiEmptyArg(char shortName, std::string fullName);

		std::string GetInfo() override;
		results::HandleResult Handle(const std::string& value) override;
		[[nodiscard]] int GetHandleCount() const;
	private:
		int handleCount = 0;
	};
}