#pragma once

#include <abstractions/IValidator.hpp>

namespace validators
{
	class StringLengthValidator : public abstractions::IValidator
	{
	public:
		StringLengthValidator(int maxStringLength);

		virtual bool Validate(const void* value) const override;

	private:
		int maxStringLength;
	};
}
