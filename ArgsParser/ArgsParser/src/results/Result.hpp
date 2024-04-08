#pragma once

#include <string>

namespace results
{
	class Result
	{
	public:
		Result();
		Result(std::string error);

		[[nodiscard]] bool IsSucceded() const;
		/**
		* @brief returns nullptr if there is no errors
		*/
		[[nodiscard]] const std::string& GetError() const;
		[[nodiscard]] static const Result NotValid(std::string value);
		[[nodiscard]] static const Result NoSuchArgument(std::string argName);
		[[nodiscard]] static const Result MissingParameter(std::string argName);
		[[nodiscard]] static const Result ArgumentIsAlreadyDefined(std::string argName);
		[[nodiscard]] static const Result ArgumentWithoutPrefix(std::string argName);
		[[nodiscard]] static const Result ConvertFail(std::string from, std::string to);
		[[nodiscard]] static const Result StringValueIsEmpty();
		[[nodiscard]] static const Result Success();
	private:
		std::string error;
	};
}