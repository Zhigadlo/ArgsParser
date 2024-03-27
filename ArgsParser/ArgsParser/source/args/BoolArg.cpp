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
			if (IsValueSet())
				info += value ? "true" : "false";

			return info;
		}
		void SetValue(bool value)
		{
			this->isValueSet = true;
			this->value = value;
		}
		bool IsValueSet() override
		{
			return isValueSet;
		}
		bool ValueHandling(std::string value) override
		{
			bool boolResult;
			if (!StringToBool(value, boolResult)) return false;

			SetValue(boolResult);
			return true;
		}
		Arg* GetCopy() override
		{
			BoolArg* copy;

			if (IsShortNameExist() && IsFullNameExist()) 
				copy = new BoolArg(GetShortName(), GetFullName());
			else if (!IsShortNameExist()) 
				copy = new BoolArg(GetFullName());
			else
				copy = new BoolArg(GetShortName());
			
			if(IsValueSet()) copy->SetValue(this->value);

			return copy;
		}
	private:
		bool value = false;
		bool isValueSet = false;

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