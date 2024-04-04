#include "MultiEmptyArg.hpp"
#include <results/Success.hpp>
#include <results/StringValueIsEmpty.hpp>
#include <results/NotValid.hpp>
#include <constants/constants.hpp>

namespace args
{
	MultiEmptyArg::MultiEmptyArg(char shortName) : abstractions::Arg(shortName, true, true, nullptr) {}
	MultiEmptyArg::MultiEmptyArg(std::string fullName) : abstractions::Arg(fullName, true, true, nullptr) {}
	MultiEmptyArg::MultiEmptyArg(char shortName, std::string fullName) : abstractions::Arg(shortName, fullName, true, true, nullptr) {}

	std::string MultiEmptyArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (IsDefined())
			info += std::to_string(handleCount);

		return info;
	}

	int MultiEmptyArg::GetHandleCount() const
	{
		return handleCount;
	}

	results::Result MultiEmptyArg::Handle(const std::string& value)
	{
		if (!IsDefined()) Define();
		handleCount++;
		return results::Success();
	}
}