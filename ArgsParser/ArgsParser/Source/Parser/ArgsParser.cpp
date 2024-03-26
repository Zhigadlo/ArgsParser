#include "ArgsParser.hpp"
#include <iostream>
#include "../abstractions/Arg.hpp"
#include "../Abstractions/ValueArg.hpp"

namespace parser
{
	abstractions::Arg* ArgsParser::FindByShortName(char shortName)
	{
		auto it = std::find_if(definedArgs.begin(), definedArgs.end(), [&shortName](abstractions::Arg* obj) { return (*obj).GetShortName() == shortName; });
		if(it == definedArgs.end()) return nullptr;

		int index = std::distance(definedArgs.begin(), it);
		return definedArgs[index];
	}
	abstractions::Arg* ArgsParser::FindByFullName(std::string fullName)
	{
		auto it = std::find_if(definedArgs.begin(), definedArgs.end(), [&fullName](abstractions::Arg* obj) { return (*obj).GetFullName() == fullName; });
		if (it == definedArgs.end()) return nullptr;

		int index = std::distance(definedArgs.begin(), it);
		return definedArgs[index];
	}
	bool ArgsParser::Parse(int argC, const char** argV)
	{
		int i = 0;
		while (i < argC)
		{
			abstractions::Arg* arg = nullptr;
			std::string strArg(argV[i]);
			int argLength = strArg.length();
			if (argLength < 2) return false;

			if (strArg[0] == '-' && argLength == 2)
			{
				char shortName = strArg[1];
				abstractions::Arg* arg = FindByShortName(shortName); 
			}
			if (arg == nullptr && strArg.substr(0, 2) == "--")
			{
				std::string fullName = strArg.substr(2);
				abstractions::Arg* arg = FindByFullName(fullName);
			}

			if (arg == nullptr) return false;

			abstractions::ValueArg* valueArg = dynamic_cast<abstractions::ValueArg*>(arg);
			if (valueArg != nullptr)
			{
				i++;
				std::string param = std::string(argV[i]);

				if (!valueArg->ValueHandling(param)) return false;
			}

			i++;
		}
		return true;
	}

	void ArgsParser::Add(abstractions::Arg* arg)
	{
		definedArgs.push_back(arg);
	}
	void ArgsParser::Show()
	{
		for (int i = 0; i < passedArgs.size(); i++)
		{
			std::cout << (*passedArgs[i]).GetInfo() << std::endl;
		}
	}
}

