#pragma once 

#include <abstractions/IValidator.hpp>

namespace validators
{
	class PositiveIntValidator : public abstractions::IValidator
	{
	public:
		virtual bool Validate(const void* value) const override;
	};
}