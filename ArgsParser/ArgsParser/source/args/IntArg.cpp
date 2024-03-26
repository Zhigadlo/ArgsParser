#include "../abstractions/Arg.hpp"
#include <format>

namespace args
{
	class IntArg : public abstractions::Arg
	{
	public:
		IntArg(char shortName, int value) : abstractions::Arg(shortName)
		{
			this->value = value;
		}
		IntArg(std::string fullName, int value) : abstractions::Arg(fullName)
		{
			this->value = value;
		}
		IntArg(char shortName, std::string fullName, int value) : abstractions::Arg(shortName, fullName)
		{
			this->value = value;
		}
		std::string GetInfo() override
		{
			std::string info;
			if (IsShortNameExist())
			{
				info += '-';
				info += GetShortName();
			}
			
			if (IsFullNameExist())
			{
				info += ' ';
				info += GetFullName();
			}
			info += ' ';
			info += std::to_string(value);
			return info;
		}

		bool abstractions::Arg::IsValueExist()
		{
			return true;
		}
	private: 
		int value;
	};

	
}