#include "../abstractions/ValueArg.hpp"

namespace args
{
	class IntArg : public abstractions::ValueArg
	{
	public:
		IntArg(char shortName) : abstractions::ValueArg(shortName) { }
		IntArg(std::string fullName) : abstractions::ValueArg(fullName) { }
		IntArg(char shortName, std::string fullName) : abstractions::ValueArg(shortName, fullName) { }

		std::string GetInfo() override
		{
			std::string info = Arg::GetInfo();
			if(IsValueSet())
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
	private: 
		int value = INT_MAX;
	};

	
}