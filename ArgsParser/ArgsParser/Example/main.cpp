#include <iostream>
#include "../source/parser/ArgsParser.hpp"
#include "../Source/Args/IntArg.cpp"


int main(int argC, const char** argV)
{
	//parser::ArgsParser parser;
	
	//parser.Add();
	/*for (int i = 0; i < argC; i++)
	{
		std::cout << argV[i] << std::endl;
	}*/

	args::IntArg intArg("int_value", 3);
	std::cout << intArg.GetInfo() << std::endl;
}

