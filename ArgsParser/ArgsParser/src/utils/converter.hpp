#pragma once 

#include "constants.hpp"
#include <results/Result.hpp>
#include <string>
#include <sstream>

namespace utils
{
	template <typename T>
	inline results::Result StringToValue(const std::string& str, T& out)
	{
		if (str.empty()) return results::Result::StringValueIsEmpty();
		std::istringstream iss(str);
		T temp;
		iss >> temp;
		if (iss.fail() || !(iss >> std::ws).eof())
			return results::Result::ConvertFail("string", typeid(T).name());

		out = temp;
		return results::Result::Success();
	}
	template <>
	inline results::Result StringToValue<std::string>(const std::string& str, std::string& out)
	{
		if (str.empty()) return results::Result::StringValueIsEmpty();
		out = str;
		return results::Result::Success();
	}
	template<>
	inline results::Result StringToValue<unsigned int>(const std::string& str, unsigned int& out)
	{
		if (str.empty()) return results::Result::StringValueIsEmpty();
		if (str[0] == ShortArgumentPrefix) return results::Result::ConvertFail("string", "unsigned int");
		std::istringstream iss(str);
		unsigned int temp;
		iss >> temp;
		if (iss.fail() || !(iss >> std::ws).eof())
			return results::Result::ConvertFail("string", "unsigned int");

		out = temp;
		return results::Result::Success();
	}
	template <>
	inline results::Result StringToValue<bool>(const std::string& str, bool& out)
	{
		if (str.empty()) return results::Result::StringValueIsEmpty();
		std::string trimmed_str;
		trimmed_str.reserve(str.size());

		for (char c : str)
			trimmed_str.push_back(std::tolower(c));

		if (trimmed_str == TrueString || trimmed_str == TrueIntString)
		{
			out = true;
			return results::Result::Success();
		}
		if (trimmed_str == FalseString || trimmed_str == FalseIntString)
		{
			out = false;
			return results::Result::Success();
		}

		return results::Result::ConvertFail("string", "bool");
	}

	template<typename T>
	inline std::string ValueToString(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}
	template<>
	inline std::string ValueToString<std::string>(const std::string& value)
	{
		return value;
	}
	template<>
	inline std::string ValueToString<bool>(const bool& value)
	{
		return value ? TrueString : FalseString;
	}
}
