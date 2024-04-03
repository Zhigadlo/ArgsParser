#include "PositiveIntValidator.hpp"

namespace validators
{
	bool PositiveIntValidator::Validate(const void* value) const
	{
		const int* intValue = static_cast<const int*>(value);
		if (intValue == nullptr) return false;
		return *intValue > 0;
	}
}