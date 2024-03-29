#pragma once

#include <iostream>
#include <abstractions/Arg.hpp>

namespace args
{
	class BoolArg : public abstractions::Arg
	{
	public:
		BoolArg(char shortName);
		BoolArg(std::string fullName);
		BoolArg(char shortName, std::string fullName);

		void SetValue(bool value);
		bool Handle(std::string value) override;
		std::string GetInfo() override;
	private:
		bool value = false;
		const std::string& TrueString = "true";
		const std::string& FalseString = "false";
		/**
		* @brief Converts string value to bool value
		* @param str string value for converting
		* @param out pointer to variable for result
		* @return true if converting is successfull otherwise returns false
		**/
		bool StringToBool(const std::string& str, bool& out);
	};
}