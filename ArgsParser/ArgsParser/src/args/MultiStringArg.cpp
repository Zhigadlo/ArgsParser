#include <abstractions/ValueArg.hpp>
#include <vector>
#include <iostream>
namespace args
{
	class MultiStringArg : public abstractions::ValueArg
	{
	public:
		MultiStringArg(char shortName) : abstractions::ValueArg(shortName) {}
		MultiStringArg(std::string fullName) : abstractions::ValueArg(fullName) {}
		MultiStringArg(char shortName, std::string fullName) : abstractions::ValueArg(shortName, fullName) {}

		std::string GetInfo() override
		{
			std::string info = Arg::GetInfo();
			if (IsDefined())
			{
				for (int i = 0; i < values.size(); i++)
				{
					info += values[i];
					info += ' ';
				}
			}
			return info;
		}
		void SetValue(std::string value)
		{
			this->values.push_back(value);
		}

		bool ValueHandling(std::string value) override
		{
			if (value.empty())
			{
				std::cerr << "Error: string value is empty." << std::endl;
				return false;
			}
			SetValue(value);
			Define();
			return true;
		}

		bool IsOneValueArg() override
		{
			return false;
		}
	private:
		std::vector<std::string> values;
	};
}