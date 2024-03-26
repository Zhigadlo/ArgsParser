#include "../abstractions/ValueArg.hpp"

namespace args
{
	class BoolArg : public abstractions::ValueArg
	{
	public:
		BoolArg(char shortName) : abstractions::ValueArg(shortName) { }
		BoolArg(std::string fullName) : abstractions::ValueArg(fullName) { }
		BoolArg(char shortName, std::string fullName) : abstractions::ValueArg(shortName, fullName) { }
		
		std::string GetInfo() override
		{
			std::string info = Arg::GetInfo();
			if(IsValueSet())
				info += std::to_string(value);

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
		bool ValueHandling(std::string values) override
		{

		}

	private:
		bool value = false;
		bool isValueSet = false;
	};
}