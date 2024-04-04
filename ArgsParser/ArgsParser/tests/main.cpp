#include <parser/ArgsParser.hpp>
#include <args/IntArg.hpp>
#include <args/BoolArg.hpp>
#include <args/EmptyArg.hpp>
#include <args/MultiStringArg.hpp>
#include <results/HandleResult.hpp>
#include <results/MissingParameter.hpp>
#include <validators/PositiveIntValidator.hpp>
#include <validators/StringLengthValidator.hpp>
#include <validators/IntRangeValidator.hpp>

#include <catch2/catch_all.hpp>

#include <iostream>
#include <memory>

TEST_CASE("args test", "[args]")
{
	validators::PositiveIntValidator positiveValidator;

	int minVal = -10;
	int maxVal = 76;
	validators::IntRangeValidator rangeValidator{ minVal, maxVal };

	unsigned int maxLen = 7;
	validators::StringLengthValidator lengthValidator(maxLen);
	parser::ArgsParser parser;

	args::EmptyArg testEmptyArg('e');
	args::IntArg intRangeArg("test_int_range", &rangeValidator);
	args::IntArg intPositiveArg('p', &positiveValidator);
	args::BoolArg boolArg('b', "bool_test");
	args::MultiStringArg multiStringLengthArg('s', "string_test", &lengthValidator);

	parser.Add(testEmptyArg);
	parser.Add(intRangeArg);
	parser.Add(intPositiveArg);
	parser.Add(boolArg);
	parser.Add(multiStringLengthArg);
	SECTION("empty arg test")
	{
		int argC = 2;
		const char* argV[] = { "ArgsParser.exe", "-e" };

		results::HandleResult result = parser.Parse(argC, argV);
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
				results::HandleResult result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the not int section: " << argV[2] << std::endl;
				REQUIRE_FALSE(successful);
			}
			SECTION("The positive section")
			{
				argV[2] = "432";
				results::HandleResult result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the positive section: " << argV[2] << std::endl;
				REQUIRE(successful);
			}
			SECTION("The negative section")
			{
				argV[2] = "-6748";
				results::HandleResult result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the negative section: " << argV[2] << std::endl;
				REQUIRE_FALSE(successful);
			}
			SECTION("The more than max length section")
			{
				argV[2] = "0";
				results::HandleResult result = parser.Parse(argC, argV);
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
				results::HandleResult result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the in ragne section: " << argV[2] << std::endl;
				REQUIRE(successful);
			}
			SECTION("The in max value section")
			{
				argV[2] = "76";
				results::HandleResult result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the in max value section: " << argV[2] << std::endl;
				REQUIRE(successful);
			}
			SECTION("The in min value section")
			{
				argV[2] = "-10";
				results::HandleResult result = parser.Parse(argC, argV);
				bool successful = result.IsSucceded();
				std::cout << "inside the in min value section: " << argV[2] << std::endl;
				REQUIRE(successful);
			}
			SECTION("The not in range section")
			{
				argV[2] = "-6789";
				results::HandleResult result = parser.Parse(argC, argV);
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
			results::HandleResult result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the too long section: " << argV[2] << " " << argV[4] << std::endl;
			REQUIRE_FALSE(successful);
		}
		SECTION("The valid strings section")
		{
			argV[4] = "_VaLiD_";
			results::HandleResult result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid strings section: " << argV[2] << " " << argV[4] << std::endl;
			REQUIRE(successful);
		}
		SECTION("The missing parameter section")
		{
			argV[4] = "";
			results::HandleResult result = parser.Parse(argC, argV);
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
			results::HandleResult result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid true section: " << argV[2] << std::endl;
			REQUIRE(successful);
		}
		SECTION("valid false section")
		{
			argV[2] = "false";
			results::HandleResult result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid false section: " << argV[2] << std::endl;
			REQUIRE(successful);
		}
		SECTION("valid int true section")
		{
			argV[2] = "0";
			results::HandleResult result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid int true section: " << argV[2] << std::endl;
			REQUIRE(successful);
		}
		SECTION("valid int false section")
		{
			argV[2] = "0";
			results::HandleResult result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the valid int false section: " << argV[2] << std::endl;
			REQUIRE(successful);
		}
		SECTION("not valid bool section")
		{
			argV[2] = "not_valid_string";
			results::HandleResult result = parser.Parse(argC, argV);
			bool successful = result.IsSucceded();
			std::cout << "inside the not valid bool section: " << argV[2] << std::endl;
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
	args::IntArg intRangeArg("test_int_range");
	args::IntArg intPositiveArg('p');
	args::BoolArg boolArg('b', "bool_test");
	args::MultiStringArg multiStringLengthArg('s', "string_test");

	parser.Add(testEmptyArg);
	parser.Add(testEmptyLongArg);
	parser.Add(intRangeArg);
	parser.Add(intPositiveArg);
	parser.Add(boolArg);
	parser.Add(multiStringLengthArg);
	int argC = 2;
	const char* argV[] = { "ArgsParser.exe", "-ep=5" };
	SECTION("valid concat arg section")
	{
		results::HandleResult result = parser.Parse(argC, argV);
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
		results::HandleResult result = parser.Parse(argC, argV);
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
	}
}

TEST_CASE("multiple args test", "[multiple args]")
{
	parser::ArgsParser parser;

	args::EmptyArg testEmptyArg('e');
	args::EmptyArg testEmptyArg2('v');
	args::EmptyArg testEmptyLongArg('l', "long_empty");
	args::IntArg intRangeArg("test_int_range");
	args::IntArg intPositiveArg('p');
	args::BoolArg boolArg('b', "bool_test");
	args::MultiStringArg multiStringLengthArg('s', "string_test");

	parser.Add(testEmptyArg);
	parser.Add(testEmptyArg2);
	parser.Add(testEmptyLongArg);
	parser.Add(intRangeArg);
	parser.Add(intPositiveArg);
	parser.Add(boolArg);
	parser.Add(multiStringLengthArg);

	SECTION("valid multi args section")
	{
		int argC = 8;
		const char* argV[] = { "ArgsParser.exe", "-ep=5", "--stri", "some_word", "--test_int", "-123", "-vb1", "-ls=-54" };
		results::HandleResult result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << successful << std::endl;
		REQUIRE(successful);
	}

	SECTION("not valid multi args section")
	{
		int argC = 8;
		const char* argV[] = { "ArgsParser.exe", "-evp=5", "--stri", "some_word", "--int_value", "-123", "-vb1", "-lp=-54" };
		results::HandleResult result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << successful << std::endl;
		REQUIRE_FALSE(successful);
	}

	SECTION("not valid multi args section")
	{
		int argC = 7;
		const char* argV[] = { "ArgsParser.exe", "-p=5", "-s=something", "-s=to", "-s", "say", "-p" };
		results::HandleResult result = parser.Parse(argC, argV);
		bool successful = result.IsSucceded();
		std::cout << "inside the already defined args section: " << successful << std::endl;
		REQUIRE_FALSE(successful);
	}
}
