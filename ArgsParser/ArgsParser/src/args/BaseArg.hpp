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
		* @warning Make sure to call this fuction after argument defined
		**/
		void Define();
		[[nodiscard]] bool IsDefined() const;
		[[nodiscard]] bool IsReusable() const;
		[[nodiscard]] bool IsParamArg() const;
		/**
		* @brief Handles string value
		* @return true if value successfuly handled and set to the object, false if value is not valid
		**/
		[[nodiscard]] virtual bool IsValidatorExist() const = 0;
		[[nodiscard]] virtual results::Result Handle(const std::string& value) = 0;
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

		virtual results::Result Handle(const std::string& value) override;
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

		bool IsValidatorExist() const override
		{
			if (validator == nullptr) return false;
			return true;
		}
		virtual results::Result Handle(const std::string& value) override
		{
			T result{};
			
			results::Result convertResult = utils::StringToValue(value, result);
			if (!convertResult.IsSucceded()) return convertResult;

			if (IsValidatorExist() && !validator->Validate(result))
				return results::Result::NotValid(utils::ValueToString(result));

			SetValue(result);
			Define();
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
			return value;
		}
	private:
		void SetValue(T value)
		{
			this->value = value;
		}
		T value;
		//std::optional<T> value;
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

		bool IsValidatorExist() const override
		{
			if (validator == nullptr) return false;
			return true;
		}
		virtual results::Result Handle(const std::string& value) override
		{
			T result{};

			results::Result convertResult = utils::StringToValue(value, result);
			if (!convertResult.IsSucceded()) return convertResult;

			if (IsValidatorExist() && !validator->Validate(result))
				return results::Result::NotValid(utils::ValueToString(result));

			SetValue(result);
			Define();
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