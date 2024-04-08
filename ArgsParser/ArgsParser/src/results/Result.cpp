#include "Result.hpp";

namespace results
{
	Result::Result() {}
	Result::Result(std::string error) : error(std::move(error)) {}

	bool Result::IsSucceded()
	{
		if (error.empty()) return true;
		
		return false;
	}

	std::string& Result::GetError()
	{
		return error;
	}
	const Result& Result::NotValid(std::string value)
	{
		return Result(value + ": Value is not valid");
	}
	const Result& Result::NoSuchArgument(std::string argName)
	{
		return Result(argName + ": No such argument");
	}
	const Result& Result::MissingParameter(std::string argName)
	{
		return Result(argName + ": Parameter is missing");
	}
	const Result& Result::ArgumentIsAlreadyDefined(std::string argName)
	{
		return Result(argName + ": Argument is already defined");
	}
	const Result& Result::ArgumentWithoutPrefix(std::string argName)
	{
		return Result(argName + ": Argument without prefix");
	}
	const Result& Result::ConvertFail(std::string from, std::string to)
	{
		return Result("Failed to convert " + from + " to " + to);
	}
	const Result& Result::StringValueIsEmpty()
	{
		return Result("String value is empty");
	}
	const Result& Result::Success()
	{
		return Result();
	}

}