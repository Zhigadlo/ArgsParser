#include "ArgsParser.hpp"
#include <results/Result.hpp>
#include <constants/constants.hpp>
#include <iostream>
#include <string_view>
#include <algorithm>

namespace parser
{
	abstractions::Arg* ArgsParser::FindByShortName(const char shortName) const
	{
		auto it = std::find_if(args.begin(), args.end(), [&shortName](abstractions::Arg* obj) { return obj->GetShortName() == shortName; });
		if (it == args.end()) return nullptr;
		return *it;
	}
	std::vector<abstractions::Arg*> ArgsParser::FindByFullName(const std::string_view& fullName) const
	{
		std::vector<abstractions::Arg*> matchingArgs;
		std::copy_if(args.begin(), args.end(), std::back_inserter(matchingArgs),
			[&fullName](abstractions::Arg* obj)
			{
				std::string_view realFullNameView = std::string_view(obj->GetFullName());
				return realFullNameView.substr(0, fullName.length()).compare(fullName) == 0; // check for string begining match
			});

		return matchingArgs;
	}
	results::Result ArgsParser::SingleArgHandle(abstractions::Arg* arg, int* index, const char* argV[], int argC)
	{
		// one value arg check
		if (!arg->IsReusable() && arg->IsDefined())
			return results::Result::ArgumentIsAlreadyDefined(arg->GetInfo());
		std::string param;
		// when arg requires param we need to take it, 
		if (arg->IsParamArg() && (*index)+1 < argC)
			param = std::string(argV[++(*index)]);

		// else we pass to Handle method empty string
		return arg->Handle(param);
	}
	results::Result ArgsParser::ConcatArgsHandle(std::string_view concatArgs)
	{
		for (int j = 0; j < concatArgs.length(); j++)
		{
			const char shortName = concatArgs[j];
			abstractions::Arg* shortArg = FindByShortName(shortName);
			if (shortArg == nullptr) return results::Result::NoSuchArgument(std::to_string(shortName));
			// one value arg check
			if (!shortArg->IsReusable() && shortArg->IsDefined())
				return results::Result::ArgumentIsAlreadyDefined(shortArg->GetInfo());

			std::string param;
			// when arg requires param we need to take it, 
			if (shortArg->IsParamArg())
			{
				j++; // go to next char and if it's = then go to another one
				if (j < concatArgs.length() && concatArgs[j] == EqualsChar) j++;

				if (j >= concatArgs.length()) // if there is no param after value arg return 
					return results::Result::MissingParameter(shortArg->GetInfo());
				// get all chars after last argument or after =
				param = concatArgs.substr(j, concatArgs.length() - j);

				return shortArg->Handle(param);
			}
			// else we pass to Handle method empty string
			results::Result result = shortArg->Handle(param);
			if (!result.IsSucceded()) return result;
		}

		return results::Result::Success();
	}
	results::Result ArgsParser::LongArgHandle(std::string_view longName, int* index, const char* argV[], int argC)
	{
		std::vector<abstractions::Arg*> findedArgs = FindByFullName(longName);
		if (findedArgs.size() != 1) return results::Result::NoSuchArgument(std::string(longName));
		abstractions::Arg* arg = findedArgs.front();
		return SingleArgHandle(arg, index, argV, argC);
	}
	results::Result ArgsParser::ShortArgHandle(const char shortName, int* index, const char* argV[], int argC)
	{
		abstractions::Arg* arg = FindByShortName(shortName);
		if (arg == nullptr) return results::Result::NoSuchArgument(std::string(argV[*index]));
		return SingleArgHandle(arg, index, argV, argC);
	}
	results::Result ArgsParser::Parse(int argC, const char* argV[])
	{
		// i = 1 because first argument is ArgsParser.exe with 0 index
		for (int i = 1; i < argC; i++)
		{
			abstractions::Arg* arg = nullptr;
			std::string_view stringViewArg(argV[i]);
			size_t argLength = stringViewArg.length();
			std::string param;

			// if < 2 then in stringViewArg only one char
			if (argLength < 2) return results::Result::NoSuchArgument(std::string(stringViewArg));
			// --string --out - long args
			if (stringViewArg.compare(0, 2, LongArgumentPrefix) == 0)
			{
				std::string_view fullName = stringViewArg.substr(2);
				results::Result result = LongArgHandle(fullName, &i, argV, argC);
				if (result.IsSucceded()) continue;
				return result;
			}
			// -h -hcv=3 -jh -hc23 - short and concat args
			if (stringViewArg[0] != ShortArgumentPrefix) return results::Result::ArgumentWithoutPrefix(std::string(stringViewArg));

			//concat argument -hb0 -hb=1 -hb
			if (argLength == 2)
			{
				//short argument -h -k -t
				char shortName = stringViewArg[1];
				results::Result result = ShortArgHandle(shortName, &i, argV, argC);
				if (!result.IsSucceded()) return result;
			}
			else
			{
				std::string_view shortNames = stringViewArg.substr(1); // get all chars after - like this -htk=4 -> htk=4
				results::Result result = ConcatArgsHandle(shortNames);
				if (!result.IsSucceded()) return result;
			}
		}
		return results::Result::Success();
	}

	results::Result ArgsParser::Add(abstractions::Arg& arg)
	{
		// Check if an argument with the same name already exists
		auto it = std::find_if(args.begin(), args.end(),[&arg](abstractions::Arg* a) 
			{
				if (a->IsFullNameExist() && arg.IsFullNameExist())
					return a->GetFullName() == arg.GetFullName();

				if (a->IsShortNameExist() && arg.IsShortNameExist())
					return a->GetShortName() == arg.GetShortName();

				return false; 
			});
		if (it != args.end())
			return results::Result(arg.GetInfo() + ": Argument with such name is already exist");
		
		args.push_back(&arg);

		return results::Result::Success();
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

