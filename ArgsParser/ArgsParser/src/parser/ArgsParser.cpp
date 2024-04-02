#include "ArgsParser.hpp"
#include <constants/constants.hpp>
#include <iostream>
#include <string_view>
#include <algorithm>

namespace parser
{
	abstractions::Arg* ArgsParser::FindByShortName(char shortName)
	{
		auto it = std::find_if(args.begin(), args.end(), [&shortName](abstractions::Arg* obj) { return (*obj).GetShortName() == shortName; });
		if (it == args.end()) return nullptr;
		return *it;
	}
	std::vector<abstractions::Arg*> ArgsParser::FindByFullName(std::string_view fullName)
	{
		std::vector<abstractions::Arg*> matchingArgs;
		std::copy_if(args.begin(), args.end(), std::back_inserter(matchingArgs),
			[&fullName](abstractions::Arg* obj)
			{
				std::string findedFullName = (*obj).GetFullName();
				std::string_view realFullNameView = std::string_view(findedFullName);
				return realFullNameView.substr(0, fullName.length()).compare(fullName) == 0; // check for string begining match
			});
		return matchingArgs;
	}
	results::HandleResult IsOneValaeArg(abstractions::Arg* arg)
	{
		if (!arg->IsReusable() && arg->IsDefined())
			return results::HandleResult("Can't define one value arg more than once.");
		return results::HandleResult();
	}
	results::HandleResult ArgsParser::Parse(int argC, const char* argV[])
	{
		// i = 1 because first argument is ArgsParser.exe with 0 index
		for (int i = 1; i < argC; i++)
		{
			abstractions::Arg* arg = nullptr;
			std::string_view stringViewArg(argV[i]);
			size_t argLength = stringViewArg.length();
			std::string param;

			if (argLength < 2) return results::HandleResult("Argument is too short");

			if (stringViewArg[0] == ShortArgumentPrefix)
			{
				if (argLength == 2)
				{
					char shortName = stringViewArg[1];
					arg = FindByShortName(shortName);
				}
				else // -hb0 || -hb=1 || -hb
				{
					//std::string_view shortNames = stringViewArg.substr(1);
					//for (int j = 0; j < shortNames.length(); j++)
					//{
					//	char shortName = shortNames[j];
					//	abstractions::Arg* shortArg = FindByShortName(shortName);
					//	if (shortArg == nullptr) return results::HandleResult(shortName + ": There is no such argument");
					//	// one value arg check
					//	if (!arg->IsReusable() && arg->IsDefined())
					//		return results::HandleResult("Can't define one value arg more than once.");

					//	// when arg requires param we need to take it, 
					//	if (arg->IsParamArg())
					//	{
					//		if (!arg->IsReusable() && arg->IsDefined())
					//			return results::HandleResult("Not reusable argument is already defined.");

					//		j++;
					//		if (shortNames[j] == '=')
					//			param = shortNames.substr(j);
					//		else
					//			param = shortNames.substr(j-1);
					//	}
					//	// else we pass to Handle method empty string
					//	results::HandleResult result = arg->Handle(param);
					//	if (!result.IsSucceded()) return result;
					//}
				}
			}

			if (arg == nullptr && stringViewArg.compare(0, 2, LongArgumentPrefix) == 0)
			{
				std::string_view fullName = stringViewArg.substr(2);
				std::vector<abstractions::Arg*> findedArgs = FindByFullName(fullName);
				if (findedArgs.size() > 1) return results::HandleResult("Can't choose right argument");
				if (findedArgs.size() == 0) return results::HandleResult("There is no such argument");
				arg = findedArgs.front();
			}

			if (arg == nullptr) return results::HandleResult("There is no such argument");

			// one value arg check
			if (!arg->IsReusable() && arg->IsDefined())
				return results::HandleResult("Can't define one value arg more than once.");

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
			if (arg->IsDefined())
				std::cout << arg->GetInfo() << std::endl;
		}
	}
}

