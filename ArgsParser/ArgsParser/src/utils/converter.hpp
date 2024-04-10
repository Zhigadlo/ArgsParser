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
	inline const std::string& ValueToString(const T& value)
	{
		static std::ostringstream oss;
		oss.clear();
		oss << value;
		return oss.str();
	}
	template<>
	inline const std::string& ValueToString<std::string>(const std::string& value)
	{
		return value;
	}
}
