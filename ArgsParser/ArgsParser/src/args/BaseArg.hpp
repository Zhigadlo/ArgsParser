#pragma once

#include <validators/Validators.hpp>
#include <results/Result.hpp>
#include <utils/converter.hpp>
#include <vector>
#include <optional>

namespace args
{
	/**
	* @brief Abstract class for arguments
	**/
	class BaseArg
	{
	public:
		BaseArg(char shortName, bool isReusable, bool isParamArg);
		BaseArg(std::string fullName, bool isReusable, bool isParamArg);
		BaseArg(char shortName, std::string fullName, bool isReusable, bool isParamArg);

		[[nodiscard]] char GetShortName() const;
		[[nodiscard]] const std::string& GetFullName() const;

		[[nodiscard]] bool IsShortNameExist() const;
		[[nodiscard]] bool IsFullNameExist() const;
		/**
		* @warning If you use basic IsDefined realisation make sure 
		* to call this fuction after argument defined 
		**/
		void Define();
		[[nodiscard]] virtual bool IsDefined() const;
		[[nodiscard]] bool IsReusable() const;
		[[nodiscard]] bool IsParamArg() const;
		/**
		* @brief Handles string value
		* @return true if value successfuly handled and set to the object, false if value is not valid
		**/
		[[nodiscard]] virtual bool IsValidatorExist() const = 0;
		[[nodiscard]] virtual results::Result Handle(const std::string_view& value) = 0;
		[[nodiscard]] virtual std::string GetInfo() const;
	private:
		char shortName = CHAR_MAX;
		std::string fullName;
		bool isDefined = false;
		bool isReusable;
		bool isParamArg;
	};
#pragma region Empty args realisation
	class EmptyArg : public BaseArg
	{
	public:
		EmptyArg(char shortName, bool isReusable = false);
		EmptyArg(std::string fullName, bool isReusable = false);
		EmptyArg(char shortName, std::string fullName, bool isReusable = false);

		virtual results::Result Handle(const std::string_view& value) override;
		bool IsValidatorExist() const override;
		std::string GetInfo() const override;
		[[nodiscard]] int GetHandleCount() const;
	private:
		int handleCount = 0;
	};
#pragma endregion
#pragma region Value args realisation
	template<typename T>
	class ValueArg : public BaseArg
	{
	public:
		ValueArg(char shortName, validators::Validator<T>* validator = nullptr)
			: BaseArg(shortName, false, true), validator(validator) {}
		ValueArg(std::string fullName, validators::Validator<T>* validator = nullptr)
			: BaseArg(fullName, false, true), validator(validator) {}
		ValueArg(char shortName, std::string fullName, validators::Validator<T>* validator = nullptr)
			: BaseArg(shortName, fullName, false, true), validator(validator) {}

		bool IsDefined() const override
		{
			if (value.has_value()) return true;
			return false;
		}

		bool IsValidatorExist() const override
		{
			if (validator == nullptr) return false;
			return true;
		}
		virtual results::Result Handle(const std::string_view& value) override
		{
			std::tuple<results::Result, std::optional<T>> convertResultWithValue = utils::StringToValue<T>(value);
			results::Result convertResult = std::get<results::Result>(convertResultWithValue);
			std::optional<T> result = std::get<std::optional<T>>(convertResultWithValue);
			
			if (!convertResult.IsSucceded()) return convertResult;

			if (IsValidatorExist() && result.has_value() && !validator->Validate(result.value()))
				return results::Result::NotValid(utils::ValueToString(result.value()));

			SetValue(std::move(result));
			return results::Result::Success();
		}
		virtual std::string GetInfo() const override
		{
			std::string info = BaseArg::GetInfo();
			if (IsDefined())
				info += utils::ValueToString(GetValue());

			return info;
		}
		T GetValue() const
		{
			return value.value();
		}
	private:
		void SetValue(std::optional<T> value)
		{
			this->value = value;
		}
		std::optional<T> value;
		validators::Validator<T>* validator;
	};
	template<typename T>
	class MultiValueArg : public BaseArg
	{
	public:
		MultiValueArg(char shortName, validators::Validator<T>* validator = nullptr)
			: BaseArg(shortName, true, true), validator(validator) {}
		MultiValueArg(std::string fullName, validators::Validator<T>* validator = nullptr)
			: BaseArg(fullName, true, true), validator(validator) {}
		MultiValueArg(char shortName, std::string fullName, validators::Validator<T>* validator = nullptr)
			: BaseArg(shortName, fullName, true, true), validator(validator) {}
		bool IsDefined() const override
		{
			return values.size() > 0;
		}
		bool IsValidatorExist() const override
		{
			if (validator == nullptr) return false;
			return true;
		}
		virtual results::Result Handle(const std::string_view& value) override
		{
			std::tuple<results::Result, std::optional<T>> convertResultWithValue = utils::StringToValue<T>(value);
			results::Result convertResult = std::get<results::Result>(convertResultWithValue);
			std::optional<T> result = std::get<std::optional<T>>(convertResultWithValue);
			if (!convertResult.IsSucceded()) return convertResult;
			if (!result.has_value()) return results::Result::StringValueIsEmpty();

			if (IsValidatorExist() && !validator->Validate(result.value()))
				return results::Result::NotValid(utils::ValueToString(result.value()));

			SetValue(result.value());
			return results::Result::Success();
		}
		virtual std::string GetInfo() const override
		{
			std::string info = BaseArg::GetInfo();
			if (!IsDefined()) return info;

			for (int i = 0; i < values.size(); i++)
			{
				info += utils::ValueToString(values[i]);
				info += utils::SpaceChar;
			}

			return info;
		}
		[[nodiscard]] const std::vector<T>& GetValues() const
		{
			return values;
		}
	private:
		void SetValue(T value)
		{
			values.push_back(value);
		}
		std::vector<T> values;
		validators::Validator<T>* validator;
	};
#pragma endregion
}