#include "PositiveIntValidator.hpp"

namespace validators
{
	bool PositiveIntValidator::Validate(void* value) override
	{
		if (value == nullptr) return false;
		int* intValue = static_cast<int*>(value);
		return *intValue > 0;
	}
}