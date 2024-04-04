#include "MultiIntArg.hpp"
#include <results/Success.hpp>
#include <results/StringValueIsEmpty.hpp>
#include <results/NotValid.hpp>
#include <constants/constants.hpp>
#include <stdexcept>

namespace args
{
	MultiIntArg::MultiIntArg(char shortName, abstractions::IValidator* validator) : abstractions::Arg(shortName, true, true, validator) {}
	MultiIntArg::MultiIntArg(std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(fullName, true, true, validator) {}
	MultiIntArg::MultiIntArg(char shortName, std::string fullName, abstractions::IValidator* validator) : abstractions::Arg(shortName, fullName, true, true, validator) {}

	std::string MultiIntArg::GetInfo()
	{
		std::string info = Arg::GetInfo();
		if (!IsDefined()) return info;

		for (int i = 0; i < values.size(); i++)
		{
			info += std::to_string(values[i]);
			info += SpaceChar;
		}

		return info;
	}

	std::vector<int> MultiIntArg::GetValues() const
	{
		return values;
	}

	void MultiIntArg::SetValue(int value)
	{
		this->values.push_back(value);
	}

	results::Result MultiIntArg::Handle(const std::string& value)
	{
		if (value.empty()) return results::StringValueIsEmpty();
		try
		{
			int result = std::stoi(value);
			abstractions::IValidator* validator = GetValidator();
			if (validator != nullptr && !validator->Validate(&result))
				return results::NotValid(std::to_string(result));
			this->values.push_back(result);
			Define();
			return results::Success();
		}
		catch (const std::invalid_argument& e)
		{
			return results::Result(e.what());
		}
		catch (const std::out_of_range& e)
		{
			return results::Result(e.what());
		}
	}
}