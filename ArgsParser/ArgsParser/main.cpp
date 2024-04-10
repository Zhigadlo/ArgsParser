#include <parser/ArgsParser.hpp>
#include <args/BaseArg.hpp>
#include <results/Result.hpp>
#include <validators/Validators.hpp>
#include <iostream>

results::Result ConfigureParser(parser::ArgsParser& parser);
std::vector<args::BaseArg*> arguments;

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
}

results::Result ConfigureParser(parser::ArgsParser& parser)
{
	validators::PositiveIntValidator posValidator;
	validators::StringLengthValidator lenValidator(5);
	validators::IntRangeValidator rangeValidator(-5, 5);
	validators::StringLengthValidator multiStringLenValidator(8);
	
	args::HelpArg helpArg('h', "help", arguments);
	args::EmptyArg testArg('t', "test");
	args::ValueArg<int> intArg("int_value");
	args::ValueArg<int> shortIntArg('k', &rangeValidator);
	args::ValueArg<int> positiveIntArg("positive_int", &posValidator);
	args::ValueArg<bool> boolArg('b', "bool_value");
	/*args::MultiStringArg multiStringArg('s', "m_string", &multiStringLenValidator);
	args::MultiIntArg multiIntArg('i', "m_int");
	args::MultiEmptyArg multiEmptyArg('e', "m_empty");
	args::StringArg stringArg("string", &lenValidator);*/

	arguments.push_back(&helpArg);
	arguments.push_back(&testArg);
	arguments.push_back(&intArg);
	arguments.push_back(&shortIntArg);
	arguments.push_back(&positiveIntArg);
	arguments.push_back(&boolArg);
	/*arguments.push_back(&multiStringArg);
	arguments.push_back(&multiEmptyArg);
	arguments.push_back(&multiIntArg);
	arguments.push_back(&stringArg);*/

	for (int i = 0; i < arguments.size(); i++)
	{
		results::Result result = parser.Add(*arguments[i]);
		if (!result.IsSucceded()) return result;
	}

	return results::Result::Success();
}