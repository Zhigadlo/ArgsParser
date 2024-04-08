#pragma once

#include <abstractions/Arg.hpp>

namespace args
{
	class EmptyArg : public abstractions::Arg
	{
	public:
		EmptyArg(char shortName);
		EmptyArg(std::string fullName);
		EmptyArg(char shortName, std::string fullName);

		results::Result Handle(const std::string& value) override;
	};

	class HelpArg : public abstractions::Arg
	{
	public:
		HelpArg(char shortName, const std::vector<abstractions::Arg*>& args);
		HelpArg(std::string fullName, const std::vector<abstractions::Arg*>& args);
		HelpArg(char shortName, std::string fullName, const std::vector<abstractions::Arg*>& args);

		std::string GetInfo() override;

		results::Result Handle(const std::string& value) override;
	private:
		const std::vector<abstractions::Arg*>& allArgs;
	};

	class BoolArg : public abstractions::Arg
	{
	public:
		BoolArg(char shortName);
		BoolArg(std::string fullName);
		BoolArg(char shortName, std::string fullName);

		void SetValue(bool value);
		results::Result Handle(const std::string& value) override;
		std::string GetInfo() override;
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

	class IntArg : public abstractions::Arg
	{
	public:
		IntArg(char shortName, abstractions::IValidator* validator = nullptr);
		IntArg(std::string fullName, abstractions::IValidator* validator = nullptr);
		IntArg(char shortName, std::string fullName, abstractions::IValidator* validator = nullptr);

		std::string GetInfo() override;
		void SetValue(int value);
		results::Result Handle(const std::string& value) override;
		[[nodiscard]] int GetValue() const;
	private:
		int value = INT_MAX;
	};

	class MultiEmptyArg : public abstractions::Arg
	{
	public:
		MultiEmptyArg(char shortName);
		MultiEmptyArg(std::string fullName);
		MultiEmptyArg(char shortName, std::string fullName);

		std::string GetInfo() override;
		results::Result Handle(const std::string& value) override;
		[[nodiscard]] int GetHandleCount() const;
	private:
		int handleCount = 0;
	};

	class MultiIntArg : public abstractions::Arg
	{
	public:
		MultiIntArg(char shortName, abstractions::IValidator* validator = nullptr);
		MultiIntArg(std::string fullName, abstractions::IValidator* validator = nullptr);
		MultiIntArg(char shortName, std::string fullName, abstractions::IValidator* validator = nullptr);

		std::string GetInfo() override;
		void SetValue(int value);

		results::Result Handle(const std::string& value) override;
		[[nodiscard]] std::vector<int> GetValues() const;
	private:
		std::vector<int> values;
	};

	class MultiStringArg : public abstractions::Arg
	{
	public:
		MultiStringArg(char shortName, abstractions::IValidator* validator = nullptr);
		MultiStringArg(std::string fullName, abstractions::IValidator* validator = nullptr);
		MultiStringArg(char shortName, std::string fullName, abstractions::IValidator* validator = nullptr);

		std::string GetInfo() override;
		void SetValue(std::string value);

		results::Result Handle(const std::string& value) override;
		[[nodiscard]] std::vector<std::string> GetValues() const;
	private:
		std::vector<std::string> values;
	};

	class StringArg : public abstractions::Arg
	{
	public:
		StringArg(char shortName, abstractions::IValidator* validator = nullptr);
		StringArg(std::string fullName, abstractions::IValidator* validator = nullptr);
		StringArg(char shortName, std::string fullName, abstractions::IValidator* validator = nullptr);

		std::string GetInfo() override;
		void SetValue(std::string value);

		results::Result Handle(const std::string& value) override;
		[[nodiscard]] std::string GetValue() const;
	private:
		std::string value;
	};
}