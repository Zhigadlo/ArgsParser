#include <parser/ArgsParser.hpp>
#include <args/BaseArg.hpp>
#include <validators/Validators.hpp>
#include <results/Result.hpp>

#include <catch2/catch_all.hpp>

#include <iostream>

TEST_CASE("args test", "[args]")
{
	validators::PositiveIntValidator positiveValidator;

	int minVal = -10;
	int maxVal = 76;
	validators::IntRangeValidator rangeValidator{ minVal, maxVal };

	unsigned int maxLen = 7;
	validators::StringLengthValidator lengthValidator{ maxLen };
	parser::ArgsParser parser;

	args::EmptyArg testEmptyArg('e');
	args::EmptyArg multiEmptyArg('m', "multi_empty", true);
	args::ValueArg<int> intRangeArg("test_int_range", &rangeValidator);
	args::ValueArg<int> intPositiveArg('p', &positiveValidator);
	args::ValueArg<bool> boolArg('b', "bool_test");
	args::ValueArg<std::string> stringArg('S');
	args::MultiValueArg<std::string> multiStringLengthArg('s', "string_test", &lengthValidator);
	args::MultiValueArg<int> multiIntArg('i', "multi_int");

	results::Result testAddResult = parser.Add(testEmptyArg);
	results::Result intRangeAddResult = parser.Add(intRangeArg);
	results::Result intPosAddResult = parser.Add(intPositiveArg);
	results::Result boolAddResult = parser.Add(boolArg);
	results::Result strAddResult = parser.Add(stringArg);
	results::Result multiStrAddResult = parser.Add(multiStringLengthArg);
	results::Result multiEmptyAddResult = parser.Add(multiEmptyArg);
	results::Result multiIntAddResult = parser.Add(multiIntArg);

	REQUIRE(testAddResult.IsSucceded());
	REQUIRE(intRangeAddResult.IsSucceded());
	REQUIRE(intPosAddResult.IsSucceded());
	REQUIRE(boolAddResult.IsSucceded());
	REQUIRE(strAddResult.IsSucceded());
	REQUIRE(multiStrAddResult.IsSucceded());
	REQUIRE(multiEmptyAddResult.IsSucceded());
	REQUIRE(multiIntAddResult.IsSucceded());

	SECTION("empty arg test")
	{
		int argC = 2;
		const char* argV[] = { "ArgsParser.exe", "-e" };

		results::Result result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside empty arg section: " << successful << std::endl;
		REQUIRE(successful);
	}
	SECTION("int arg test")
	{
		SECTION("int positive arg test")
		{
			int argC = 3;
			const char* argV[] = { "ArgsParser.exe", "-p", "value" };
			SECTION("The not int section")
			{
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the not int section: " << argV[2] << std::endl;
				REQUIRE_FALSE(successful);
			}
			SECTION("The positive section")
			{
				argV[2] = "432";
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the positive section: " << argV[2] << std::endl;
				REQUIRE(successful);
				REQUIRE(intPositiveArg.GetValue() == 432);
			}
			SECTION("The negative section")
			{
				argV[2] = "-6748";
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the negative section: " << argV[2] << std::endl;
				REQUIRE_FALSE(successful);
			}
			SECTION("The more than max length section")
			{
				argV[2] = "0";
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the zero section: " << argV[2] << std::endl;
				REQUIRE_FALSE(successful);
			}
		}
		SECTION("range int arg test")
		{
			int argC = 3;
			const char* argV[] = { "ArgsParser.exe", "--test_int_", "43" };
			SECTION("The in range section")
			{
				argV[2] = "43";
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the in ragne section: " << argV[2] << std::endl;
				REQUIRE(successful);
				REQUIRE(intRangeArg.GetValue() == 43);
			}
			SECTION("The in max value section")
			{
				argV[2] = "76";
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the in max value section: " << argV[2] << std::endl;
				REQUIRE(successful);
				REQUIRE(intRangeArg.GetValue() == 76);
			}
			SECTION("The in min value section")
			{
				argV[2] = "-10";
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the in min value section: " << argV[2] << std::endl;
				REQUIRE(successful);
				REQUIRE(intRangeArg.GetValue() == -10);
			}
			SECTION("The not in range section")
			{
				argV[2] = "-6789";
				results::Result result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the not in range section: " << argV[2] << std::endl;
				REQUIRE_FALSE(successful);
			}
		}
	}
	SECTION("multi length string arg test")
	{
		int argC = 5;
		const char* argV[] = { "ArgsParser.exe", "-s", "valid", "--str", "not_valid" };
		SECTION("The too long section")
		{
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the too long section: " << argV[2] << " " << argV[4] << std::endl;
			REQUIRE_FALSE(successful);
		}
		SECTION("The valid strings section")
		{
			argV[4] = "_VaLiD_";
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid strings section: " << argV[2] << " " << argV[4] << std::endl;
			REQUIRE(successful);
			std::vector<std::string> values = multiStringLengthArg.GetValues();
			REQUIRE(values[0] == "valid");
			REQUIRE(values[1] == "_VaLiD_");
		}
		SECTION("The missing parameter section")
		{
			argV[4] = "";
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the missing parameter section: " << successful << std::endl;
			REQUIRE_FALSE(successful);
		}
	}
	SECTION("bool arg test")
	{
		int argC = 3;
		const char* argV[] = { "ArgsParser.exe", "--bool", "true" };
		SECTION("valid true section")
		{
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid true section: " << argV[2] << std::endl;
			REQUIRE(successful);
			REQUIRE(boolArg.GetValue() == true);
		}
		SECTION("valid false section")
		{
			argV[2] = "false";
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid false section: " << argV[2] << std::endl;
			REQUIRE(successful);
			REQUIRE(boolArg.GetValue() == false);
		}
		SECTION("valid int true section")
		{
			argV[2] = "1";
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid int true section: " << argV[2] << std::endl;
			REQUIRE(successful);
			REQUIRE(boolArg.GetValue() == true);
		}
		SECTION("valid int false section")
		{
			argV[2] = "0";
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid int false section: " << argV[2] << std::endl;
			REQUIRE(successful);
			REQUIRE(boolArg.GetValue() == false);
		}
		SECTION("not valid bool section")
		{
			argV[2] = "not_valid_string";
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the not valid bool section: " << argV[2] << std::endl;
			REQUIRE_FALSE(successful);
		}
	}
	SECTION("multi empty arg test")
	{
		int argC = 5;
		const char* argV[] = { "ArgsParser.exe", "-m", "--multi_e", "--multi_emp", "-mmmm" };
		SECTION("The valid count section")
		{
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid count section: " << multiEmptyArg.GetInfo() << std::endl;
			REQUIRE(successful);
			REQUIRE(multiEmptyArg.GetHandleCount() == 7);
		}
	}
	SECTION("multi int arg test")
	{
		int argC = 5;
		const char* argV[] = { "ArgsParser.exe", "-i=5", "--multi_i", "123", "-mmmi500" };
		SECTION("The valid int values section")
		{
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid int values section: " << multiIntArg.GetInfo() << std::endl;
			REQUIRE(successful);
			std::vector<int> values = multiIntArg.GetValues();
			REQUIRE(values[0] == 5);
			REQUIRE(values[1] == 123);
			REQUIRE(values[2] == 500);
		}
	}
	SECTION("Argument prefix test")
	{
		int argC = 2;
		const char* argV[] = { "ArgsParser.exe", "--multi_" };

		results::Result result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the argument prefix section: " << successful << std::endl;
		REQUIRE_FALSE(successful);
	}
	SECTION("String arg test")
	{
		int argC = 3;
		const char* argV[] = { "ArgsParser.exe", "-s=5", "-S=500" };
		SECTION("The valid string value section")
		{
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid int values section: " << stringArg.GetInfo() << std::endl;
			REQUIRE(successful);
			std::string value = stringArg.GetValue();
			REQUIRE(value == "500");
		}
		SECTION("The not valid string value section")
		{
			argV[1] = "-S=5";
			results::Result result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the not valid int values section: " << stringArg.GetInfo() << std::endl;
			REQUIRE_FALSE(successful);
		}
	}
}

TEST_CASE("concat args test", "[concat args]")
{
	parser::ArgsParser parser;

	args::EmptyArg testEmptyArg('e');
	args::EmptyArg testEmptyArg2('v');
	args::EmptyArg testEmptyLongArg('l', "long_empty");
	args::ValueArg<int> intRangeArg("test_int_range");
	args::ValueArg<int> intPositiveArg('p');
	args::ValueArg<bool> boolArg('b', "bool_test");
	args::MultiValueArg<std::string> multiStringLengthArg('s', "string_test");

	results::Result testAddResult = parser.Add(testEmptyArg);
	results::Result testEmptyAddResult = parser.Add(testEmptyLongArg);
	results::Result intRangeAddResult = parser.Add(intRangeArg);
	results::Result intPosAddResult = parser.Add(intPositiveArg);
	results::Result boolAddResult = parser.Add(boolArg);
	results::Result multiStrAddResult = parser.Add(multiStringLengthArg);

	REQUIRE(testAddResult.IsSucceded());
	REQUIRE(intRangeAddResult.IsSucceded());
	REQUIRE(intPosAddResult.IsSucceded());
	REQUIRE(testEmptyAddResult.IsSucceded());
	REQUIRE(boolAddResult.IsSucceded());
	REQUIRE(multiStrAddResult.IsSucceded());
	int argC = 2;
	const char* argV[] = { "ArgsParser.exe", "-ep=5" };
	SECTION("valid concat arg section")
	{
		results::Result result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the valid concat arg section: " << argV[1] << std::endl;
		REQUIRE(successful);

		argV[1] = "-lbTRUE";
		result = parser.Parse(argC, argV);
		successful = result.IsSucceded();
		std::cout << "inside the valid concat arg section: " << argV[1] << std::endl;
		REQUIRE(successful);
	}
	SECTION("already defined args section")
	{
		argV[1] = "-es12fpk";
		results::Result result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << argV[1] << std::endl;
		REQUIRE(successful);

		argV[1] = "-es3";
		result = parser.Parse(argC, argV);
		successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << argV[1] << std::endl;
		REQUIRE_FALSE(successful);

		argV[1] = "-vs=123";
		result = parser.Parse(argC, argV);
		successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << argV[1] << std::endl;
		REQUIRE_FALSE(successful);
		auto values = multiStringLengthArg.GetValues();
		REQUIRE(values[0] == "12fpk");
	}
}

TEST_CASE("multiple args test", "[multiple args]")
{
	parser::ArgsParser parser;

	args::EmptyArg testEmptyArg('e');
	args::EmptyArg testEmptyArg2('v');
	args::EmptyArg testEmptyLongArg('l', "long_empty");
	args::ValueArg<int> intRangeArg("test_int_range");
	args::ValueArg<int> intPositiveArg('p');
	args::ValueArg<bool> boolArg('b', "bool_test");
	args::MultiValueArg<std::string> multiStringLengthArg('s', "string_test");

	results::Result testAddResult = parser.Add(testEmptyArg);
	results::Result test2AddResult = parser.Add(testEmptyArg2);
	results::Result testLongAddResult = parser.Add(testEmptyLongArg);
	results::Result intRangeAddResult = parser.Add(intRangeArg);
	results::Result intPosAddResult = parser.Add(intPositiveArg);
	results::Result boolAddResult = parser.Add(boolArg);
	results::Result multiStrAddResult = parser.Add(multiStringLengthArg);

	REQUIRE(testAddResult.IsSucceded());
	REQUIRE(test2AddResult.IsSucceded());
	REQUIRE(testLongAddResult.IsSucceded());
	REQUIRE(intRangeAddResult.IsSucceded());
	REQUIRE(multiStrAddResult.IsSucceded());
	REQUIRE(intPosAddResult.IsSucceded());
	REQUIRE(boolAddResult.IsSucceded());

	SECTION("valid multi args section")
	{
		int argC = 8;
		const char* argV[] = { "ArgsParser.exe", "-ep=5", "--stri", "some_word", "--test_int", "-123", "-vb1", "-ls=-54" };
		results::Result result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << successful << std::endl;
		REQUIRE(successful);
	}

	SECTION("not valid multi args section")
	{
		int argC = 8;
		const char* argV[] = { "ArgsParser.exe", "-evp=5", "--stri", "some_word", "--int_value", "-123", "-vb1", "-lp=-54" };
		results::Result result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << successful << std::endl;
		REQUIRE_FALSE(successful);
	}

	SECTION("not valid multi args section")
	{
		int argC = 7;
		const char* argV[] = { "ArgsParser.exe", "-p=5", "-s=something", "-s=to", "-s", "say", "-p" };
		results::Result result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << successful << std::endl;
		REQUIRE_FALSE(successful);
	}
}
