#include "ArgsParser.hpp"
#include <iostream>
#include "../abstractions/Arg.hpp"

namespace parser
{
	bool ArgsParser::Parse(int argC, const char** argV)
	{
		for (int i = 0; i < argC; i += 2)
		{

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
			std::cout << (*args[i]).GetInfo() << std::endl;
		}
	}
}

