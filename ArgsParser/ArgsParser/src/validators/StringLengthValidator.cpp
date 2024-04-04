#include "StringLengthValidator.hpp"

#include <string>

namespace validators
{
	StringLengthValidator::StringLengthValidator(unsigned int maxStringLength) : maxStringLength(maxStringLength) {}

	bool StringLengthValidator::Validate(const void* value) const
	{
		const std::string* stringValue = static_cast<const std::string*>(value);
		if (stringValue == nullptr) return false;
		return stringValue->length() <= maxStringLength;
	}
}