#include <parser/ArgsParser.hpp>
#include <args/BaseArg.hpp>
#include <results/Result.hpp>
#include <validators/Validators.hpp>
#include <iostream>

void AddArgToParser(parser::ArgsParser& parser, args::BaseArg& arg);

int main(int argC, const char* argV[])
{
	validators::PositiveIntValidator posValidator;
	validators::StringLengthValidator lenValidator(5);
	validators::IntRangeValidator rangeValidator(-5, 5);
	validators::StringLengthValidator multiStringLenValidator(8);
	validators::IPValidator ipValidator;

	args::EmptyArg testArg('t', "test");
	args::EmptyArg multiEmptyArg('e', "m_empty", true);
	args::ValueArg<int> intArg("int_value");
	args::ValueArg<int> shortIntArg('k', &rangeValidator);
	args::ValueArg<int> positiveIntArg("positive_int", &posValidator);
	args::ValueArg<unsigned int> uintArg("uint");
	args::ValueArg<long long> longLong('l', "long_long");
	args::ValueArg<float> floatArg('f', "float_value");
	args::ValueArg<bool> boolArg('b', "bool_value");
	args::ValueArg<std::string> stringArg("string", &lenValidator);
	args::MultiValueArg<std::string> multiStringArg('s', "m_string", &multiStringLenValidator);
	args::MultiValueArg<int> multiIntArg('i', "m_int");
	args::ValueArg<std::string> ipArg("ip_address", &ipValidator);

	parser::ArgsParser parser;
	AddArgToParser(parser, testArg);
	AddArgToParser(parser, intArg);
	AddArgToParser(parser, shortIntArg);
	AddArgToParser(parser, positiveIntArg);
	AddArgToParser(parser, uintArg);
	AddArgToParser(parser, floatArg);
	AddArgToParser(parser, boolArg);
	AddArgToParser(parser, multiStringArg);
	AddArgToParser(parser, multiEmptyArg);
	AddArgToParser(parser, multiIntArg);
	AddArgToParser(parser, stringArg);
	AddArgToParser(parser, ipArg);
	AddArgToParser(parser, longLong);
	parser.ShowHelp();
	results::Result result = parser.Parse(argC, argV);
	if (result.IsSucceded())
		parser.Show();
	else
		std::cout << result.GetError() << std::endl;

}
void AddArgToParser(parser::ArgsParser& parser, args::BaseArg& arg)
{
	results::Result addResult = parser.Add(arg);
	if (addResult.IsSucceded()) return;

	std::cout << addResult.GetError() << std::endl;
	std::cout << arg.GetInfo() << ": Argument was not added to parser" << std::endl;
}