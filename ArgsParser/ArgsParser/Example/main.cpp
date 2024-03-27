#include <iostream>
#include "../source/abstractions/Arg.hpp"
#include "../source/parser/ArgsParser.hpp"
#include "../source/Args/IntArg.cpp"
#include "../source/Args/BoolArg.cpp"
#include "../source/Args/MultiStringArg.cpp"

int main(int argC/*, const char* argV[]*/)
{
	argC = 11;
	const char* argV[] = { "-b", "true", "-s", "can", "--string_value", "you", "--int_value", "1", "-h", "-s", "say" };

	parser::ArgsParser parser;

	abstractions::Arg helpArg('h');
	args::IntArg intArg("int_value");
	args::BoolArg boolArg('b', "bool_value");
	args::MultiStringArg multiStringArg('s', "string_value");

	parser.Add(&helpArg);
	parser.Add(&intArg);
	parser.Add(&boolArg);
	parser.Add(&multiStringArg);

	if (parser.Parse(argC, argV)) parser.Show();
}

