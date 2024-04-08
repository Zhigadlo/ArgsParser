#include "Validators.hpp"
#include <string>

namespace validators
{
	IntRangeValidator::IntRangeValidator(int minValue, int maxValue) : minValue(minValue), maxValue(maxValue) {}

	bool IntRangeValidator::Validate(const void* value) const
	{
		const int* intValue = static_cast<const int*>(value);
		if (intValue == nullptr) return false;
		return *intValue >= minValue && *intValue <= maxValue;
	}

	bool PositiveIntValidator::Validate(const void* value) const
	{
		const int* intValue = static_cast<const int*>(value);
		if (intValue == nullptr) return false;
		return *intValue > 0;
	}

	StringLengthValidator::StringLengthValidator(unsigned int maxStringLength) : maxStringLength(maxStringLength) {}

	bool StringLengthValidator::Validate(const void* value) const
	{
		const std::string* stringValue = static_cast<const std::string*>(value);
		if (stringValue == nullptr) return false;
		return stringValue->length() <= maxStringLength;
	}
}