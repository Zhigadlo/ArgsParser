#include "ArgsParser.hpp"
#include <results/Success.hpp>
#include <results/ArgumentIsAlreadyDefined.hpp>
#include <results/MissingParameter.hpp>
#include <results/NoSuchArgument.hpp>
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
				std::string findedFullName = obj->GetFullName();
				std::string_view realFullNameView = std::string_view(findedFullName);
				return realFullNameView.substr(0, fullName.length()).compare(fullName) == 0; // check for string begining match
			});

		return matchingArgs;
	}
	results::HandleResult ArgsParser::SingleArgHandle(abstractions::Arg* arg, int* index, const char* argV[])
	{
		// one value arg check
		if (!arg->IsReusable() && arg->IsDefined())
			return results::ArgumentIsAlreadyDefined(arg->GetInfo());
		std::string param;
		// when arg requires param we need to take it, 
		if (arg->IsParamArg()) param = std::string(argV[++(*index)]);

		// else we pass to Handle method empty string
		return arg->Handle(param);
	}
	results::HandleResult ArgsParser::ConcatArgsHandle(std::string_view concatArgs)
	{
		for (int j = 0; j < concatArgs.length(); j++)
		{
			const char shortName = concatArgs[j];
			abstractions::Arg* shortArg = FindByShortName(shortName);
			if (shortArg == nullptr) return results::NoSuchArgument(std::to_string(shortName));
			// one value arg check
			if (!shortArg->IsReusable() && shortArg->IsDefined())
				return results::ArgumentIsAlreadyDefined(shortArg->GetInfo());

			std::string param;
			// when arg requires param we need to take it, 
			if (shortArg->IsParamArg())
			{
				j++; // go to next char and if it's = then go to another one
				if (j < concatArgs.length() && concatArgs[j] == EqualsChar) j++;

				if (j >= concatArgs.length()) // if there is no param after value arg return 
					return results::MissingParameter(shortArg->GetInfo());
				// get all chars after last argument or after =
				param = concatArgs.substr(j, concatArgs.length() - j);

				return shortArg->Handle(param);
			}
			// else we pass to Handle method empty string
			results::HandleResult result = shortArg->Handle(param);
			if (!result.IsSucceded()) return result;
		}

		return results::Success();
	}
	results::HandleResult ArgsParser::LongArgHandle(std::string_view longName, int* index, const char* argV[])
	{
		std::vector<abstractions::Arg*> findedArgs = FindByFullName(longName);
		if (findedArgs.size() != 1) return results::NoSuchArgument(std::string(longName));
		abstractions::Arg* arg = findedArgs.front();
		return SingleArgHandle(arg, index, argV);
	}
	results::HandleResult ArgsParser::ShortArgHandle(const char shortName, int* index, const char* argV[])
	{
		abstractions::Arg* arg = FindByShortName(shortName);
		if (arg == nullptr) return results::NoSuchArgument(std::string(argV[*index]));
		return SingleArgHandle(arg, index, argV);
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

			// if < 2 then in stringViewArg only one char
			if (argLength < 2) return results::NoSuchArgument(std::string(stringViewArg));
			// --string --out - long args
			if (stringViewArg.compare(0, 2, LongArgumentPrefix) == 0)
			{
				std::string_view fullName = stringViewArg.substr(2);
				results::HandleResult result = LongArgHandle(fullName, &i, argV);
				if (result.IsSucceded()) continue;
			}
			// -h -hcv=3 -jh -hc23 - short and concat args
			if (stringViewArg[0] != ShortArgumentPrefix) return results::HandleResult(std::string(stringViewArg) + ": Argument without prefix");

			//concat argument -hb0 -hb=1 -hb
			if (argLength == 2)
			{
				//short argument -h -k -t
				char shortName = stringViewArg[1];
				results::HandleResult result = ShortArgHandle(shortName, &i, argV);
				if (!result.IsSucceded()) return result;
			}
			else
			{
				std::string_view shortNames = stringViewArg.substr(1); // get all chars after - like this -htk=4 -> htk=4
				results::HandleResult result = ConcatArgsHandle(shortNames);
				if (!result.IsSucceded()) return result;
			}
		}
		return results::Success();
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

