#include <parser/ArgsParser.hpp>
#include <args/BaseArg.hpp>
#include <results/Result.hpp>
#include <validators/Validators.hpp>
#include <iostream>

results::Result ConfigureParser(parser::ArgsParser& parser);
std::vector<args::BaseArg*> arguments;

validators::PositiveIntValidator posValidator;
validators::StringLengthValidator lenValidator(5);
validators::IntRangeValidator rangeValidator(-5, 5);
validators::StringLengthValidator multiStringLenValidator(8);
validators::IPValidator ipValidator;

args::HelpArg helpArg('h', "help", arguments);
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
args::MultiValueArg<std::string> multiIntArg('i', "m_int");
args::ValueArg<std::string> ipArg("ip_address", &ipValidator);

int main(/*int argC, const char* argV[]*/)
{
	int argC = 23;
	const char* argV[] = { "ArgsParser.exe", "-l9223372036855", "--ip", "198.162.0.1", "-f=5.3213", "--ui",
		"6", "-hteek5", "-eei=123", "-s=test1", "--m_s", "test2", "--help", "--int", "45", "-ei=-54", "--pos", "1",
		"-eeeeb=false", "--m_e", "--m_in", "120", "new"};
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
	arguments.push_back(&helpArg);
	arguments.push_back(&testArg);
	arguments.push_back(&intArg);
	arguments.push_back(&shortIntArg);
	arguments.push_back(&positiveIntArg);
	arguments.push_back(&uintArg);
	arguments.push_back(&floatArg);
	arguments.push_back(&boolArg);
	arguments.push_back(&multiStringArg);
	arguments.push_back(&multiEmptyArg);
	arguments.push_back(&multiIntArg);
	arguments.push_back(&stringArg);
	arguments.push_back(&ipArg);
	arguments.push_back(&longLong);

	for (int i = 0; i < arguments.size(); i++)
	{
		results::Result result = parser.Add(*arguments[i]);
		if (!result.IsSucceded()) return result;
	}

	return results::Result::Success();
}