#include "PositiveIntValidator.hpp"

namespace validators
{
	bool PositiveIntValidator::Validate(void* value)
	{
		int* intValue = static_cast<int*>(value);
		if (intValue == nullptr) return false;
		return *intValue > 0;
	}
}