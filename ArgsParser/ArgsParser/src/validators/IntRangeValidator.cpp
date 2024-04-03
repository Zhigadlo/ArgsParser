#include "IntRangeValidator.hpp"

namespace validators
{
	IntRangeValidator::IntRangeValidator(int minValue, int maxValue) : minValue(minValue), maxValue(maxValue) {}

	bool IntRangeValidator::Validate(const void* value) const
	{
		const int* intValue = static_cast<const int*>(value);
		if (intValue == nullptr) return false;
		return *intValue >= minValue && *intValue <= maxValue;
	}
}