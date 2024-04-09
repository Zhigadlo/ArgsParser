#pragma once

namespace validators
{
	template<typename T>
	class Validator
	{
		[[nodiscard]] virtual bool Validate(T value) const = 0;
	};
	class IntRangeValidator : public Validator<int>
	{
	public:
		IntRangeValidator(int minValue, int maxValue);
		virtual bool Validate(int value) const override;
	private:
		int minValue;
		int maxValue;
	};

	class PositiveIntValidator : public Validator<int>
	{
	public:
		virtual bool Validate(int value) const override;
	};

	class StringLengthValidator : public Validator<std::string>
	{
	public:
		StringLengthValidator(unsigned int maxStringLength);

		virtual bool Validate(std::string value) const override;

	private:
		unsigned int maxStringLength;
	};
}