#pragma once

#include <args/Args.hpp>
#include <results/Result.hpp>
#include <vector>

namespace parser
{
	class ArgsParser
	{
	private:
		std::vector<args::Arg*> args;
		[[nodiscard]] args::Arg* FindByShortName(const char shortName) const;
		[[nodiscard]] std::vector<args::Arg*> FindByFullName(const std::string_view& fullName) const;
		/**
		* @brief Handles concat short arguments like -hb=1, -hsValue, -thk=5
		**/
		[[nodiscard]] results::Result ConcatArgsHandle(std::string_view concatArgs);
		/**
		* @brief Handles single arguments like -h, --int 123, -b True
		**/
		[[nodiscard]] results::Result SingleArgHandle(args::Arg* arg, int* index, const char* argV[], int argC);
		/**
		* @brief Finds and handles arguments by short names(like -h, -k=3, -t)
		**/
		[[nodiscard]] results::Result ShortArgHandle(const char shortName, int* index, const char* argV[], int argC);
		/**
		* @brief Finds and handles arguments by long names(like --test, --int 3, --string_val example_string, --bool 1)
		**/
		[[nodiscard]] results::Result LongArgHandle(std::string_view longName, int* index, const char* argV[], int argC);
	public:
		[[nodiscard]] results::Result Parse(int argC, const char* argV[]);
		results::Result Add(args::Arg& arg);
		/**
		* @brief Shows in console info about all defined arguments
		**/
		void Show() const;
	};
}