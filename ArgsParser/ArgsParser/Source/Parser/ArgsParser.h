#pragma once

#include "../Abstractions/Arg.cpp";
#include <vector>

namespace Parser
{
	class ArgsParser
	{
	public:
		bool Parse(int argC, const char** argV);
		void Add(Abstractions::Arg& arg);
		void Show();
	};
}