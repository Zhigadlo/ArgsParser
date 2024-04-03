#include <parser/ArgsParser.hpp>
#include <args/IntArg.hpp>
#include <args/MultiStringArg.hpp>
#include <args/BoolArg.hpp>
#include <args/EmptyArg.hpp>
#include <validators/PositiveIntValidator.hpp>
#include <validators/StringLengthValidator.hpp>
#include <iostream>

int main(/*int argC, const char* argV[] */)
{
	int argC = 12;
	const char* argV[] = { "ArgsParser.exe", "--pos", "5", "-hk=2", "-b", "true", "--int_", "1", "--str", "0123", "-s", "another" };

	parser::ArgsParser parser;

	validators::PositiveIntValidator* posValidator = new validators::PositiveIntValidator();
	validators::StringLengthValidator* lenValidator = new validators::StringLengthValidator(5);
	
	args::EmptyArg helpArg('h');
	args::EmptyArg testArg('t', "test");
	args::IntArg intArg("int_value");
	args::IntArg shortIntArg('k');
	args::IntArg positiveIntArg("positive_int", posValidator);
	args::BoolArg boolArg('b', "bool_value");
	args::MultiStringArg multiStringArg('s', "string_value", lenValidator);

	parser.Add(helpArg);
	parser.Add(testArg);
	parser.Add(intArg);
	parser.Add(shortIntArg);
	parser.Add(positiveIntArg);
	parser.Add(boolArg);
	parser.Add(multiStringArg);

	results::HandleResult result = parser.Parse(argC, argV);
	if (result.IsSucceded())
		parser.Show();
	else
		std::cout << result.GetError() << std::endl;
}

