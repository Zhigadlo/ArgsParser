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
	class Arg
	{
	public:
		Arg(char shortName, bool isReusable, bool isParamArg, std::unique_ptr<validators::IValidator> validator = nullptr);
		Arg(std::string fullName, bool isReusable, bool isParamArg, std::unique_ptr<validators::IValidator> validator = nullptr);
		Arg(char shortName, std::string fullName, bool isReusable, bool isParamArg, std::unique_ptr<validators::IValidator> validator = nullptr);

		[[nodiscard]] char GetShortName() const;
		[[nodiscard]] const std::string& GetFullName() const;
		[[nodiscard]] validators::IValidator* GetValidator() const;

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
		[[nodiscard]] virtual results::Result Handle(const std::string& value) = 0;
		[[nodiscard]] virtual std::string GetInfo() const;
	private:
		char shortName = CHAR_MAX;
		std::string fullName;
		bool isDefined = false;
		bool isReusable;
		bool isParamArg;
		std::unique_ptr<validators::IValidator> validator{};
	};
	class EmptyArg : public Arg
	{
	public:
		EmptyArg(char shortName);
		EmptyArg(std::string fullName);
		EmptyArg(char shortName, std::string fullName);

		results::Result Handle(const std::string& value) override;
	};

	class HelpArg : public Arg
	{
	public:
		HelpArg(char shortName, const std::vector<Arg*>& args);
		HelpArg(std::string fullName, const std::vector<Arg*>& args);
		HelpArg(char shortName, std::string fullName, const std::vector<Arg*>& args);

		std::string GetInfo() const override;

		results::Result Handle(const std::string& value) override;
	private:
		const std::vector<Arg*>& allArgs;
	};

	class BoolArg : public Arg
	{
	public:
		BoolArg(char shortName);
		BoolArg(std::string fullName);
		BoolArg(char shortName, std::string fullName);

		void SetValue(bool value);
		results::Result Handle(const std::string& value) override;
		std::string GetInfo() const override;
		/**
		* Before calling this function make sure to check if value is defined
		* @return argument defined value, if not defined returns false
		**/
		[[nodiscard]] bool GetValue() const;
	private:
		bool value = false;
		/**
		* @brief Converts string value to bool value
		* @param str string value for converting
		* @param out pointer to variable for result
		* @return true if converting is successfull otherwise returns false
		**/
		[[nodiscard]] static bool StringToBool(const std::string& str, bool& out);
	};

	class IntArg : public Arg
	{
	public:
		IntArg(char shortName, std::unique_ptr<validators::IValidator> validator = nullptr);
		IntArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);
		IntArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);

		std::string GetInfo() const override;
		void SetValue(int value);
		results::Result Handle(const std::string& value) override;
		[[nodiscard]] int GetValue() const;
	private:
		int value = INT_MAX;
	};

	class MultiEmptyArg : public Arg
	{
	public:
		MultiEmptyArg(char shortName);
		MultiEmptyArg(std::string fullName);
		MultiEmptyArg(char shortName, std::string fullName);

		std::string GetInfo() const override;
		results::Result Handle(const std::string& value) override;
		[[nodiscard]] int GetHandleCount() const;
	private:
		int handleCount = 0;
	};

	class MultiIntArg : public Arg
	{
	public:
		MultiIntArg(char shortName, std::unique_ptr<validators::IValidator> validator = nullptr);
		MultiIntArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);
		MultiIntArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);

		std::string GetInfo() const override;
		void SetValue(int value);

		results::Result Handle(const std::string& value) override;
		[[nodiscard]] const std::vector<int>& GetValues() const;
	private:
		std::vector<int> values;
	};

	class MultiStringArg : public Arg
	{
	public:
		MultiStringArg(char shortName, std::unique_ptr<validators::IValidator> validator = nullptr);
		MultiStringArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);
		MultiStringArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);

		std::string GetInfo() const override;
		void SetValue(std::string value);

		results::Result Handle(const std::string& value) override;
		[[nodiscard]] std::vector<std::string> GetValues() const;
	private:
		std::vector<std::string> values;
	};

	class StringArg : public Arg
	{
	public:
		StringArg(char shortName, std::unique_ptr<validators::IValidator> validator = nullptr);
		StringArg(std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);
		StringArg(char shortName, std::string fullName, std::unique_ptr<validators::IValidator> validator = nullptr);

		std::string GetInfo() const override;
		void SetValue(std::string value);

		results::Result Handle(const std::string& value) override;
		[[nodiscard]] const std::string& GetValue() const;
	private:
		std::string value;
	};
}