#pragma once

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
		results::HandleResult Handle(const std::string& value) override;
		std::string GetInfo() override;
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
}