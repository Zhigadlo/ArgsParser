#include "../abstractions/ValueArg.hpp"
#include <iostream>

namespace args
{
	class BoolArg : public abstractions::ValueArg
	{
	public:
		BoolArg(char shortName) : abstractions::ValueArg(shortName) {}
		BoolArg(std::string fullName) : abstractions::ValueArg(fullName) {}
		BoolArg(char shortName, std::string fullName) : abstractions::ValueArg(shortName, fullName) {}

		std::string GetInfo() override
		{
			std::string info = Arg::GetInfo();
			if (IsDefined())
				info += value ? "true" : "false";

			return info;
		}
		void SetValue(bool value)
		{
			this->value = value;
		}
		bool ValueHandling(std::string value) override
		{
			bool boolResult;
			if (!StringToBool(value, boolResult)) return false;

			SetValue(boolResult);
			Define();
			return true;
		}
		bool IsOneValueArg() override
		{
			return true;
		}
	private:
		bool value = false;
		/**
		* @brief Converts string value to bool value
		* @param str string value for converting
		* @param out pointer to variable for result
		* @return true if converting is successfull otherwise returns false
		**/
		bool StringToBool(const std::string& str, bool& out)
		{
			std::string trimmed_str;
			trimmed_str.reserve(str.size());

			for (char c : str)
			{
				trimmed_str.push_back(std::tolower(c));
			}

			if (trimmed_str == "true" || trimmed_str == "1")
			{
				out = true;
				return true;
			}
			if (trimmed_str == "false" || trimmed_str == "0")
			{
				out = false;
				return true;
			}
			std::cerr << "Error: invalid bool string value." << std::endl;
			return false;
		}
	};
}