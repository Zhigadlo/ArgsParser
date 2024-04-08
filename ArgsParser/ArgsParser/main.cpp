#include <parser/ArgsParser.hpp>
#include <args/Args.hpp>
#include <results/Result.hpp>
#include <validators/Validators.hpp>
#include <iostream>

results::Result ConfigureParser(parser::ArgsParser& parser);
std::vector<args::Arg*> arguments;

int main(int argC, const char* argV[])
{
	parser::ArgsParser parser;
	results::Result configureResult = ConfigureParser(parser);
	if (configureResult.IsSucceded())
	{
		results::Result result = parser.Parse(argC, argV);
		if (result.IsSucceded())
			parser.Show();
		else
			std::cout << result.GetError() << std::endl;
	}
	else
		std::cout << configureResult.GetError() << std::endl;

	for (int i = 0; i < arguments.size(); i++)
		delete arguments[i];
}

results::Result ConfigureParser(parser::ArgsParser& parser)
{
	validators::PositiveIntValidator* posValidator = new validators::PositiveIntValidator();
	validators::StringLengthValidator* lenValidator = new validators::StringLengthValidator(5);
	validators::IntRangeValidator* rangeValidator = new validators::IntRangeValidator(-5, 5);
	validators::StringLengthValidator* multiStringLenValidator = new validators::StringLengthValidator(8);
	
	args::HelpArg* helpArg = new args::HelpArg('h', "help", arguments);
	args::EmptyArg* testArg = new args::EmptyArg('t', "test");
	args::IntArg* intArg = new args::IntArg("int_value");
	args::IntArg* shortIntArg = new args::IntArg('k', rangeValidator);
	args::IntArg* positiveIntArg = new args::IntArg("positive_int", posValidator);
	args::BoolArg* boolArg = new args::BoolArg('b', "bool_value");
	args::MultiStringArg* multiStringArg = new args::MultiStringArg('s', "m_string", multiStringLenValidator);
	args::MultiIntArg* multiIntArg = new args::MultiIntArg('i', "m_int");
	args::MultiEmptyArg* multiEmptyArg = new args::MultiEmptyArg('e', "m_empty");

	arguments.push_back(helpArg);
	arguments.push_back(testArg);
	arguments.push_back(intArg);
	arguments.push_back(shortIntArg);
	arguments.push_back(positiveIntArg);
	arguments.push_back(boolArg);
	arguments.push_back(multiStringArg);
	arguments.push_back(multiEmptyArg);
	arguments.push_back(multiIntArg);

	for (int i = 0; i < arguments.size(); i++)
	{
		results::Result result = parser.Add(*arguments[i]);
		if (!result.IsSucceded()) return result;
	}

	return results::Result::Success();
}