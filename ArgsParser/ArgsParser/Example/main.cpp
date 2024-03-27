#include <iostream>
#include "../source/abstractions/Arg.hpp"
#include "../source/parser/ArgsParser.hpp"
#include "../source/Args/IntArg.cpp"
#include "../source/Args/BoolArg.cpp"

int main(int argC)
{
	argC = 7;
	const char* argV[] = { "-b", "true", "--int_value", "1", "-h", "--bool_value", "0" };

	parser::ArgsParser parser;

	abstractions::Arg helpArg('h');
	args::IntArg intArg("int_value");
	args::BoolArg boolArg('b', "bool_value");

	parser.Add(&helpArg);
	parser.Add(&intArg);
	parser.Add(&boolArg);

	if (parser.Parse(argC, argV)) parser.Show();
}

