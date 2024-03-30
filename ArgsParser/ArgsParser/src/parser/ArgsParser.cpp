#include "ArgsParser.hpp"
#include <constants/constants.hpp>
#include <iostream>

namespace parser
{
	abstractions::Arg* ArgsParser::FindByShortName(char shortName)
	{
		auto it = std::find_if(args.begin(), args.end(), [&shortName](abstractions::Arg* obj) { return (*obj).GetShortName() == shortName; });
		if (it == args.end()) return nullptr;
		return *it;
	}
	abstractions::Arg* ArgsParser::FindByFullName(std::string fullName)
	{
		auto it = std::find_if(args.begin(), args.end(), [&fullName](abstractions::Arg* obj) { return (*obj).GetFullName() == fullName; });
		if (it == args.end()) return nullptr;
		return *it;
	}
	results::HandleResult ArgsParser::Parse(int argC, const char* argV[])
	{
		// i = 1 because first argument is ArgsParser.exe with 0 index
		for(int i = 1; i < argC; i++)
		{
			abstractions::Arg* arg = nullptr;
			std::string strArg(argV[i]);
			size_t argLength = strArg.length();
			if (argLength < 2) return results::HandleResult("Argument is too short");

			if (strArg[0] == ShortArgumentPrefix && argLength == 2)
			{
				char shortName = strArg[1];
				arg = FindByShortName(shortName);
			}

			if (arg == nullptr && strArg.substr(0, 2) == LongArgumentPrefix)
			{
				std::string fullName = strArg.substr(2);
				arg = FindByFullName(fullName);
			}
			
			if (arg == nullptr) return results::HandleResult("There is no such argument");

			// one value arg check
			if (!arg->IsReusable() && arg->IsDefined()) 
				return results::HandleResult("Can't define one value arg more than once.");

			std::string param;
			// when arg requires param we need to take it, 
			if (arg->IsParamArg())
			{
				if (!arg->IsReusable() && arg->IsDefined())
					return results::HandleResult("Not reusable argument is already defined.");
				
				param = std::string(argV[++i]);
			}
			// else we pass to Handle method empty string
			results::HandleResult result = arg->Handle(param);
			if (!result.IsSucceded()) return result;
		}
		return results::HandleResult();
	}

	void ArgsParser::Add(abstractions::Arg& arg)
	{
		args.push_back(&arg);
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

