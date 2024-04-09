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
}

results::Result ConfigureParser(parser::ArgsParser& parser)
{
	std::unique_ptr<validators::PositiveIntValidator> posValidator(new validators::PositiveIntValidator());
	std::unique_ptr<validators::StringLengthValidator> lenValidator(new validators::StringLengthValidator(5));
	std::unique_ptr<validators::IntRangeValidator> rangeValidator(new validators::IntRangeValidator(-5, 5));
	std::unique_ptr<validators::StringLengthValidator> multiStringLenValidator(new validators::StringLengthValidator(8));
	
	std::unique_ptr<args::HelpArg> helpArg(new args::HelpArg('h', "help", arguments));
	std::unique_ptr<args::EmptyArg> testArg(new args::EmptyArg('t', "test"));
	std::unique_ptr<args::IntArg> intArg(new args::IntArg("int_value"));
	std::unique_ptr<args::IntArg> shortIntArg(new args::IntArg('k', std::move(rangeValidator)));
	std::unique_ptr<args::IntArg> positiveIntArg(new args::IntArg("positive_int", std::move(posValidator)));
	std::unique_ptr<args::BoolArg> boolArg(new args::BoolArg('b', "bool_value"));
	std::unique_ptr<args::MultiStringArg> multiStringArg(new args::MultiStringArg('s', "m_string", std::move(multiStringLenValidator)));
	std::unique_ptr<args::MultiIntArg> multiIntArg(new args::MultiIntArg('i', "m_int"));
	std::unique_ptr<args::MultiEmptyArg> multiEmptyArg(new args::MultiEmptyArg('e', "m_empty"));
	std::unique_ptr<args::StringArg> stringArg(new args::StringArg("string", std::move(lenValidator)));

	arguments.push_back(helpArg.get());
	arguments.push_back(testArg.get());
	arguments.push_back(intArg.get());
	arguments.push_back(shortIntArg.get());
	arguments.push_back(positiveIntArg.get());
	arguments.push_back(boolArg.get());
	arguments.push_back(multiStringArg.get());
	arguments.push_back(multiEmptyArg.get());
	arguments.push_back(multiIntArg.get());
	arguments.push_back(stringArg.get());

	for (int i = 0; i < arguments.size(); i++)
	{
		results::Result result = parser.Add(*arguments[i]);
		if (!result.IsSucceded()) return result;
	}

	return results::Result::Success();
}