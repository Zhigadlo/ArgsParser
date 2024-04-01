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
		abstractions::Arg* FindByFullName(std::string_view fullName);
	public:
		results::HandleResult Parse(int argC, const char* argV[]);
		void Add(abstractions::Arg& arg);
		void Show();
	};
}