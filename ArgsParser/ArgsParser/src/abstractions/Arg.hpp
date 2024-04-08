#pragma once

#include <abstractions/IValidator.hpp>
#include <results/Result.hpp>
#include <vector>

namespace abstractions
{
	/**
	* @brief Class for arguments without parameters
	**/
	class Arg
	{
	public:
		Arg(char shortName, bool isReusable, bool isParamArg, abstractions::IValidator* validator);
		Arg(std::string fullName, bool isReusable, bool isParamArg, abstractions::IValidator* validator);
		Arg(char shortName, std::string fullName, bool isReusable, bool isParamArg, abstractions::IValidator* validator);

		[[nodiscard]] char GetShortName() const;
		[[nodiscard]] const std::string& GetFullName() const;
		[[nodiscard]] IValidator* GetValidator() const;

		[[nodiscard]] bool IsShortNameExist() const;
		[[nodiscard]] bool IsFullNameExist() const;
		/**
		* @warning Make sure to call this fuction after argument defined
		**/
		void Define();
		[[nodiscard]] bool IsDefined();
		[[nodiscard]] bool IsReusable();
		[[nodiscard]] bool IsParamArg();
		/**
		* @brief Handles string value
		* @return true if value successfuly handled and set to the object, false if value is not valid
		**/
		[[nodiscard]] virtual results::Result Handle(const std::string& value) = 0;
		[[nodiscard]] virtual std::string GetInfo();
	private:
		char shortName = CHAR_MAX;
		std::string fullName;
		bool isDefined = false;
		bool isReusable;
		bool isParamArg;
		abstractions::IValidator* validator;
	};
}