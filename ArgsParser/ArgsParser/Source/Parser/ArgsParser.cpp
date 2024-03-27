#include "ArgsParser.hpp"
#include <iostream>
#include "../abstractions/Arg.hpp"
#include "../abstractions/ValueArg.hpp"

namespace parser
{
	abstractions::Arg* ArgsParser::FindByShortName(char shortName)
	{
		auto it = std::find_if(args.begin(), args.end(), [&shortName](abstractions::Arg* obj) { return (*obj).GetShortName() == shortName; });
		if (it == args.end()) return nullptr;

		int index = std::distance(args.begin(), it);
		return args[index];
	}
	abstractions::Arg* ArgsParser::FindByFullName(std::string fullName)
	{
		auto it = std::find_if(args.begin(), args.end(), [&fullName](abstractions::Arg* obj) { return (*obj).GetFullName() == fullName; });
		if (it == args.end()) return nullptr;

		int index = std::distance(args.begin(), it);
		return args[index];
	}
	bool ArgsParser::Parse(int argC, const char* argV[])
	{
		for(int i = 0; i < argC; i++)
		{
			abstractions::Arg* arg = nullptr;
			std::string strArg(argV[i]);
			int argLength = strArg.length();
			if (argLength < 2) return false;

			if (strArg[0] == '-' && argLength == 2)
			{
				char shortName = strArg[1];
				arg = FindByShortName(shortName);
			}

			if (arg == nullptr && strArg.substr(0, 2) == "--")
			{
				std::string fullName = strArg.substr(2);
				arg = FindByFullName(fullName);
			}
			
			if (arg == nullptr) return false;
			abstractions::ValueArg* valueArg = dynamic_cast<abstractions::ValueArg*>(arg);

			// arg without value
			if (valueArg == nullptr)
			{
				if (arg->IsDefined()) return false;

				arg->Define();
				continue;
			}

			// one value arg check
			if (valueArg->IsOneValueArg() && valueArg->IsDefined())
			{
				std::cerr << "Error: can't define one value arg more than once." << std::endl;
				return false;
			}

			i++;
			std::string param = std::string(argV[i]);

			if (!valueArg->ValueHandling(param)) return false;
		}
		return true;
	}

	void ArgsParser::Add(abstractions::Arg* arg)
	{
		args.push_back(arg);
	}
	void ArgsParser::Show()
	{
		for (int i = 0; i < args.size(); i++)
		{
			auto arg = args[i];
			if(arg->IsDefined())
				std::cout << arg->GetInfo() << std::endl;
		}
	}
}

