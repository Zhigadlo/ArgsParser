#pragma once

#include "Arg.hpp"

namespace abstractions
{
	/**
	* @brief Class for arguments with parameters
	**/
	class ValueArg : public Arg
	{
	public:
		ValueArg(char shortName);
		ValueArg(std::string fullName);
		ValueArg(char shortName, std::string fullName);
		/**
		* @brief Handles string value
		* @return true if value successfuly handled and set to the object, false if value is not valid
		**/
		virtual bool ValueHandling(std::string value) = 0;
		virtual bool IsOneValueArg() = 0;
	};
}