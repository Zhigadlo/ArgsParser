#pragma once 

#include <abstractions/IValidator.hpp>

namespace validators
{
	class PositiveIntValidator : public abstractions::IValidator
	{
	public:
		bool abstractions::IValidator::Validate(void* value) override;
	};

}