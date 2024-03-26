#include <iostream>
#include "../source/parser/ArgsParser.hpp"
#include "../Source/Args/IntArg.cpp"
#include "../Source/Args/BoolArg.cpp"


int main(int argC, const char** argV)
{
	parser::ArgsParser parser;

	args::IntArg intArg("int_value");
	std::cout << intArg.GetInfo() << std::endl;

	args::BoolArg boolArg('b', "bool_value");
	std::cout << boolArg.GetInfo() << std::endl;

	parser.Add(&intArg);
	parser.Add(&boolArg);
	parser.Show();
}

