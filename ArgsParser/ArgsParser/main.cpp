#include <iostream>
#include <parser/ArgsParser.hpp>
#include <args/IntArg.cpp>
#include <args/MultiStringArg.cpp>
#include <args/BoolArg.cpp>

int main(int argC, const char* argV[])
{
	parser::ArgsParser parser;

	abstractions::Arg helpArg('h');
	args::IntArg intArg("int_value");
	args::BoolArg boolArg('b', "bool_value");
	args::MultiStringArg multiStringArg('s', "string_value");

	parser.Add(&helpArg);
	parser.Add(&intArg);
	parser.Add(&boolArg);
	parser.Add(&multiStringArg);

	if (parser.Parse(argC, argV))
		parser.Show();
	else
		std::cout << "Fail to parse arguments :(" << std::endl;
}

