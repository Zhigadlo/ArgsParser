#pragma once

#include <abstractions/Arg.hpp>
#include <vector>

namespace parser
{
	class ArgsParser
	{
	private:
		std::vector<abstractions::Arg*> args;
		[[nodiscard]] abstractions::Arg* FindByShortName(char shortName);
		[[nodiscard]] std::vector<abstractions::Arg*> FindByFullName(std::string_view fullName);
		[[nodiscard]] results::HandleResult ConcatArgsHandle(std::string_view concatArgs);
	public:
		[[nodiscard]] results::HandleResult Parse(int argC, const char* argV[]);
		void Add(abstractions::Arg& arg);
		void Show();
	};
}