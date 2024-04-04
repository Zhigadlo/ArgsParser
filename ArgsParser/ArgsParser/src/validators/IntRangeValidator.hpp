#pragma once

#include <abstractions/IValidator.hpp>

namespace validators
{
	class IntRangeValidator : public abstractions::IValidator
	{
	public:
		IntRangeValidator(int minValue, int maxValue);

		virtual bool Validate(const void* value) const override;
	private:
		int minValue;
		int maxValue;
	};
}
