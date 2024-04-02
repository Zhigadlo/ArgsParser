#include <parser/ArgsParser.hpp>
#include <args/IntArg.hpp>
#include <args/MultiStringArg.hpp>
#include <args/BoolArg.hpp>
#include <args/EmptyArg.hpp>
#include <iostream>

int main(int argC, const char* argV[])
{
	parser::ArgsParser parser;

	args::EmptyArg helpArg('h');
	args::EmptyArg testArg('t', "test");
	args::IntArg intArg("int_value");
	args::IntArg shortIntArg('k');
	args::BoolArg boolArg('b', "bool_value");
	args::MultiStringArg multiStringArg('s', "string_value");

	parser.Add(helpArg);
	parser.Add(testArg);
	parser.Add(intArg);
	parser.Add(shortIntArg);
	parser.Add(boolArg);
	parser.Add(multiStringArg);

	results::HandleResult result = parser.Parse(argC, argV);
	if (result.IsSucceded())
		parser.Show();
	else
		std::cout << result.GetError() << std::endl;
}

