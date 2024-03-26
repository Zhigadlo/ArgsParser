#pragma once

#include "../abstractions/Arg.hpp";
#include <vector>

namespace parser
{
	class ArgsParser
	{
	private:
		std::vector<abstractions::Arg*> args;
	public:
		bool Parse(int argC, const char** argV);
		void Add(abstractions::Arg* arg);
		void Show();
	};
}