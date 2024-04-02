#pragma once

#include <abstractions/Arg.hpp>
#include <vector>

namespace parser
{
	class ArgsParser
	{
	private:
		std::vector<abstractions::Arg*> args;
		abstractions::Arg* FindByShortName(char shortName);
		std::vector<abstractions::Arg*> FindByFullName(std::string_view fullName);
		results::HandleResult ConcatArgsHandle(std::string_view concatArgs);
	public:
		results::HandleResult Parse(int argC, const char* argV[]);
		void Add(abstractions::Arg& arg);
		void Show();
	};
}