#pragma once 

#include "constants.hpp"
#include <results/Result.hpp>
#include <string>
#include <sstream>
#include <optional>
#include <tuple>

namespace utils
{
	template <typename T>
	inline std::tuple<results::Result, std::optional<T>> StringToValue(const std::string_view& str)
	{
		std::optional<T> value;
		if (str.empty()) return std::make_tuple(results::Result::StringValueIsEmpty(), value);
		std::istringstream iss{ std::string(str) };
		T temp;
		iss >> temp;
		if (iss.fail() || !(iss >> std::ws).eof())
			return std::make_tuple(results::Result::ConvertFail("string", typeid(T).name()), value);
		value = temp;
		return std::make_tuple(results::Result::Success(), value);
	}
	template <>
	inline std::tuple<results::Result, std::optional<std::string>> StringToValue<std::string>(const std::string_view& str)
	{
		std::optional<std::string> value{ str };
		if (str.empty()) return std::make_tuple(results::Result::StringValueIsEmpty(), value);

		return std::make_tuple(results::Result::Success(), value);
	}
	template<>
	inline std::tuple<results::Result, std::optional<unsigned int>> StringToValue<unsigned int>(const std::string_view& str)
	{
		std::optional<unsigned int> value;
		if (str.empty()) return std::make_tuple(results::Result::StringValueIsEmpty(), value);
		if (str[0] == ShortArgumentPrefix) return std::make_tuple(results::Result::ConvertFail("string", "unsigned int"), value);
		std::istringstream iss{ std::string(str) };
		unsigned int temp;
		iss >> temp;
		if (iss.fail() || !(iss >> std::ws).eof())
			return std::make_tuple(results::Result::ConvertFail("string", "unsigned int"), value);
		value = temp;
		return std::make_tuple(results::Result::Success(), value);
	}
	template <>
	inline std::tuple<results::Result, std::optional<bool>> StringToValue<bool>(const std::string_view& str)
	{
		std::optional<bool> value;
		if (str.empty()) return std::make_tuple(results::Result::StringValueIsEmpty(), value);
		std::string trimmed_str;
		trimmed_str.reserve(str.size());

		for (char c : str)
			trimmed_str.push_back(std::tolower(c));

		if (trimmed_str == TrueString || trimmed_str == TrueIntString)
			value = true;
		
		if (trimmed_str == FalseString || trimmed_str == FalseIntString)
			value = false;

		if (value.has_value())
			return std::make_tuple(results::Result::Success(), value);

		return std::make_tuple(results::Result::ConvertFail("string", "bool"), value);
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
