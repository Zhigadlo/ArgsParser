#include "../abstractions/ValueArg.hpp"
#include <stdexcept>
#include <iostream>

namespace args
{
	class IntArg : public abstractions::ValueArg
	{
	public:
		IntArg(char shortName) : abstractions::ValueArg(shortName) {}
		IntArg(std::string fullName) : abstractions::ValueArg(fullName) {}
		IntArg(char shortName, std::string fullName) : abstractions::ValueArg(shortName, fullName) {}

		std::string GetInfo() override
		{
			std::string info = Arg::GetInfo();
			if (IsValueSet())
				info += std::to_string(value);
			return info;
		}
		void SetValue(int value)
		{
			this->value = value;
		}
		bool IsValueSet() override
		{
			if (value == INT_MAX) return false;

			return true;
		}
		Arg* GetCopy() override
		{
			IntArg* copy;

			if (IsShortNameExist() && IsFullNameExist())
				copy = new IntArg(GetShortName(), GetFullName());
			else if (IsShortNameExist())
				copy = new IntArg(GetShortName());
			else 
				copy = new IntArg(GetFullName());

			if(IsValueSet()) copy->SetValue(this->value);

			return copy;
		}

		bool ValueHandling(std::string value) override
		{
			int result;

			try
			{
				result = std::stoi(value);
				SetValue(result);
				return true;
			}
			catch (const std::invalid_argument& e)
			{
				std::cerr << "Error: Invalid integer string value - " << value << std::endl;
			}
			catch (const std::out_of_range& e)
			{
				std::cerr << "Error: The integer value is out of range - " << value << std::endl;
			}

			return false;
		}

	private:
		int value = INT_MAX;
	};
}