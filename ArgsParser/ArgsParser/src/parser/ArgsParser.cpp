#include "ArgsParser.hpp"
#include <utils/constants.hpp>
#include <iostream>
#include <string_view>
#include <algorithm>

namespace parser
{
	args::BaseArg* ArgsParser::FindByShortName(const char shortName) const
	{
		auto it = std::find_if(args.begin(), args.end(), [&shortName](args::BaseArg* obj) { return obj->GetShortName() == shortName; });
		if (it == args.end()) return nullptr;
		return *it;
	}
	std::vector<args::BaseArg*> ArgsParser::FindByFullName(const std::string_view& fullName) const
	{
		std::vector<args::BaseArg*> matchingArgs;
		std::copy_if(args.begin(), args.end(), std::back_inserter(matchingArgs),
			[&fullName](args::BaseArg* obj)
			{
				std::string_view realFullNameView = std::string_view(obj->GetFullName());
				return realFullNameView.substr(0, fullName.length()).compare(fullName) == 0; // check for string begining match
			});

		return matchingArgs;
	}
	std::tuple<results::Result, int> ArgsParser::SingleArgHandle(args::BaseArg* arg, int index, const char* argV[], int argC)
	{
		// one value arg check
		if (!arg->IsReusable() && arg->IsDefined())
			return std::make_tuple(results::Result::ArgumentIsAlreadyDefined(arg->GetInfo()), index);
		std::string_view param;
		// when arg requires param we need to take it, 
		if (arg->IsParamArg() && index + 1 < argC)
			param = std::string_view(argV[++index]);

		// else we pass to Handle method empty string
		return std::make_tuple(arg->Handle(param), index);
	}
	results::Result ArgsParser::ConcatArgsHandle(std::string_view concatArgs)
	{
		for (size_t j = 0; j < concatArgs.length(); j++)
		{
			const char shortName = concatArgs[j];
			args::BaseArg* shortArg = FindByShortName(shortName);
			if (shortArg == nullptr) return results::Result::NoSuchArgument(std::to_string(shortName));
			// one value arg check
			if (!shortArg->IsReusable() && shortArg->IsDefined())
				return results::Result::ArgumentIsAlreadyDefined(shortArg->GetInfo());

			std::string_view param;
			// when arg requires param we need to take it, 
			if (shortArg->IsParamArg())
			{
				j++; // go to next char and if it's = then go to another one
				if (j < concatArgs.length() && concatArgs[j] == utils::EqualsChar) j++;

				if (j >= concatArgs.length()) // if there is no param after value arg return 
					return results::Result::MissingParameter(shortArg->GetInfo());
				// get all chars after last argument or after =
				param = concatArgs.substr(j, concatArgs.length() - j);

				return shortArg->Handle(param);
			}
			// else we pass to Handle method empty string
			const results::Result& result = shortArg->Handle(param);
			if (!result.IsSucceded()) return result;
		}

		return results::Result::Success();
	}
	// ptr to link fix, don't use out param
	std::tuple<results::Result, int> ArgsParser::LongArgHandle(std::string_view longName, int index, const char* argV[], int argC)
	{
		std::vector<args::BaseArg*> findedArgs = FindByFullName(longName);
		if (findedArgs.empty()) return std::make_tuple(results::Result::NoSuchArgument(std::string(longName)), index);
		if (findedArgs.size() == 1)
		{
			args::BaseArg* arg = findedArgs.front();
			return SingleArgHandle(arg, index, argV, argC);
		}
		std::string argMatches;
		for (size_t i = 0; i < findedArgs.size(); i++)
			argMatches += utils::LongArgumentPrefix + findedArgs[i]->GetFullName() + "\n";
		return std::make_tuple(results::Result::MoreThanOneMatch(argMatches), index);
	}
	std::tuple<results::Result, int> ArgsParser::ShortArgHandle(const char shortName, int index, const char* argV[], int argC)
	{
		args::BaseArg* arg = FindByShortName(shortName);
		if (arg == nullptr) return std::make_tuple(results::Result::NoSuchArgument(argV[index]), index);
		return SingleArgHandle(arg, index, argV, argC);
	}
	results::Result ArgsParser::Parse(int argC, const char* argV[])
	{
		// i = 1 because first argument is ArgsParser.exe with 0 index
		for (int i = 1; i < argC; i++)
		{
			std::string_view stringViewArg(argV[i]);
			size_t argLength = stringViewArg.length();

			// if < 2 then in stringViewArg only one char
			if (argLength < 2) return results::Result::NoSuchArgument(std::string(stringViewArg));
			// --string --out - long args
			if (stringViewArg.compare(0, 2, utils::LongArgumentPrefix) == 0)
			{
				std::string_view fullName = stringViewArg.substr(2);
				std::tuple<results::Result, int> resultWithIndex = LongArgHandle(fullName, i, argV, argC);
				results::Result result = std::get<results::Result>(resultWithIndex);
				i = std::get<int>(resultWithIndex);
				if (result.IsSucceded()) continue;
				return result;
			}
			// -h -hcv=3 -jh -hc23 - short and concat args
			if (stringViewArg[0] != utils::ShortArgumentPrefix) return results::Result::ArgumentWithoutPrefix(std::string(stringViewArg));

			//concat argument -hb0 -hb=1 -hb
			if (argLength == 2)
			{
				//short argument -h -k -t
				char shortName = stringViewArg[1];
				std::tuple<results::Result, int> resultWithIndex = ShortArgHandle(shortName, i, argV, argC);
				results::Result result = std::get<results::Result>(resultWithIndex);
				i = std::get<int>(resultWithIndex);
				if (!result.IsSucceded()) return result;
			}
			else
			{
				// get all chars after - like this -htk=4 -> htk=4
				std::string_view shortNames = stringViewArg.substr(1); 
				results::Result result = ConcatArgsHandle(shortNames);
				if (!result.IsSucceded()) return result;
			}
		}
		return results::Result::Success();
	}

	results::Result ArgsParser::Add(args::BaseArg& arg)
	{
		// Check if an argument with the same name already exists
		auto it = std::find_if(args.begin(), args.end(), [&arg](args::BaseArg* a)
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
	void ArgsParser::AddWithoutResult(args::BaseArg& arg)
	{
		results::Result addResult = Add(arg);
		if (addResult.IsSucceded()) return;

		std::cout << addResult.GetError() << std::endl;
		std::cout << arg.GetInfo() << ": Argument was not added to parser" << std::endl;
	}

	void ArgsParser::Show() const
	{
		if (args.empty())
		{
			std::cout << "There is no arguments in parser" << std::endl;
			return;
		}

		std::cout << "Argument values" << std::endl;
		std::cout << "--------------------" << std::endl;
		for (size_t i = 0; i < args.size(); i++)
		{
			auto arg = args[i];

			if (arg->IsDefined())
				std::cout << arg->GetInfo() << std::endl;
		}
		std::cout << "--------------------" << std::endl;
	}
	void ArgsParser::ShowHelp() const
	{
		std::cout << "Arguments info" << std::endl;
		std::cout << "--------------------" << std::endl;
		for (size_t i = 0; i < args.size(); i++)
		{
			auto arg = args[i];
			if (arg->IsShortNameExist())
				std::cout << utils::ShortArgumentPrefix << arg->GetShortName() << utils::SpaceChar;
			if (arg->IsFullNameExist())
				std::cout << utils::LongArgumentPrefix << arg->GetFullName() << utils::SpaceChar;
			std::cout << std::endl;
		}
		std::cout << "--------------------" << std::endl;
	}
}

