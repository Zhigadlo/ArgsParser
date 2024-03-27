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
			if (IsDefined())
				info += std::to_string(value);
			return info;
		}
		void SetValue(int value)
		{
			this->value = value;
		}
		bool ValueHandling(std::string value) override
		{
			int result;

			try
			{
				result = std::stoi(value);
				SetValue(result);
				Define();
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
		bool IsOneValueArg() override
		{
			return true;
		}
	private:
		int value = INT_MAX;
	};
}