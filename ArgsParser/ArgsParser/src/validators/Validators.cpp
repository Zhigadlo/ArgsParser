#include "Validators.hpp"
#include <string>

namespace validators
{
	IntRangeValidator::IntRangeValidator(int minValue, int maxValue) : minValue(minValue), maxValue(maxValue) {}

	bool IntRangeValidator::Validate(int value) const
	{
		return value >= minValue && value <= maxValue;
	}

	bool PositiveIntValidator::Validate(int value) const
	{
		return value > 0;
	}

	StringLengthValidator::StringLengthValidator(unsigned int maxStringLength) : maxStringLength(maxStringLength) {}

	bool StringLengthValidator::Validate(std::string value) const
	{
		return value.length() <= maxStringLength;
	}
}