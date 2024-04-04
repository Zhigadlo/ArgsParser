#pragma once

#include <abstractions/Arg.hpp>
#include <vector>

namespace parser
{
	class ArgsParser
	{
	private:
		std::vector<abstractions::Arg*> args;
		[[nodiscard]] abstractions::Arg* FindByShortName(const char shortName) const;
		[[nodiscard]] std::vector<abstractions::Arg*> FindByFullName(const std::string_view& fullName) const;
		/**
		* @brief Handles concat short arguments like -hb=1, -hsValue, -thk=5
		**/
		[[nodiscard]] results::HandleResult ConcatArgsHandle(std::string_view concatArgs);
		/**
		* @brief Handles single arguments like -h, --int 123, -b True
		**/
		[[nodiscard]] results::HandleResult SingleArgHandle(abstractions::Arg* arg, int* index, const char* argV[]);
		/**
		* @brief Finds and handles arguments by short names(like -h, -k=3, -t)
		**/
		[[nodiscard]] results::HandleResult ShortArgHandle(const char shortName, int* index, const char* argV[]);
		/**
		* @brief Finds and handles arguments by long names(like --test, --int 3, --string_val example_string, --bool 1)
		**/
		[[nodiscard]] results::HandleResult LongArgHandle(std::string_view longName, int* index, const char* argV[]);
	public:
		[[nodiscard]] results::HandleResult Parse(int argC, const char* argV[]);
		void Add(abstractions::Arg& arg);
		void Show();
	};
}