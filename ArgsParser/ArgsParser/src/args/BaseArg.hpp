#pragma once

#include <validators/Validators.hpp>
#include <results/Result.hpp>
#include <string>
#include <vector>

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

	class EmptyArg : public BaseArg
	{
	public:
		EmptyArg(char shortName);
		EmptyArg(std::string fullName);
		EmptyArg(char shortName, std::string fullName);

		virtual results::Result Handle(const std::string& value) override;
		bool IsValidatorExist() const override;
	};

	class HelpArg : public EmptyArg
	{
	public:
		HelpArg(char shortName, const std::vector<BaseArg*>& args);
		HelpArg(std::string fullName, const std::vector<BaseArg*>& args);
		HelpArg(char shortName, std::string fullName, const std::vector<BaseArg*>& args);

		std::string GetInfo() const override;
	private:
		const std::vector<BaseArg*>& allArgs;
	};

	template<typename T>
	class ValueArg : public BaseArg
	{
	public:
		ValueArg(char shortName, bool isReusable, bool isParamArg, validators::Validator<T>* validator = nullptr);
		ValueArg(std::string fullName, bool isReusable, bool isParamArg, validators::Validator<T>* validator = nullptr);
		ValueArg(char shortName, std::string fullName, bool isReusable, bool isParamArg, validators::Validator<T>* validator = nullptr);

		bool IsValidatorExist() const override;
		virtual results::Result Handle(const std::string& value) override;
		virtual std::string GetInfo() const override;
		T GetValue() const;
	private:
		T value;
	};
}