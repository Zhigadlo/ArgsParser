#pragma once

namespace validators
{
	class IValidator
	{
	public:
		/**
		* @todo remake on templates
		**/
		[[nodiscard]] virtual bool Validate(const void* value) const = 0;
	};
	class IntRangeValidator : public IValidator
	{
	public:
		IntRangeValidator(int minValue, int maxValue);

		virtual bool Validate(const void* value) const override;
	private:
		int minValue;
		int maxValue;
	};

	class PositiveIntValidator : public IValidator
	{
	public:
		virtual bool Validate(const void* value) const override;
	};

	class StringLengthValidator : public IValidator
	{
	public:
		StringLengthValidator(unsigned int maxStringLength);

		virtual bool Validate(const void* value) const override;

	private:
		unsigned int maxStringLength;
	};
}