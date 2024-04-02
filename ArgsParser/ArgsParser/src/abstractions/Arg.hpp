#pragma once

#include <abstractions/IValidator.hpp>
#include <results/HandleResult.hpp>
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

		char GetShortName();
		std::string GetFullName();
		IValidator* GetValidator();

		bool IsShortNameExist();
		bool IsFullNameExist();
		/**
		* @warning Make sure to call this fuction after argument defined
		**/
		void Define();
		bool IsDefined();
		bool IsReusable();
		bool IsParamArg();
		/**
		* @brief Handles string value
		* @return true if value successfuly handled and set to the object, false if value is not valid
		**/
		virtual results::HandleResult Handle(const std::string& value) = 0;
		virtual std::string GetInfo();
	private:
		char shortName = CHAR_MAX;
		std::string fullName;
		bool isDefined = false;
		bool isReusable;
		bool isParamArg;
		abstractions::IValidator* validator;
	};
}