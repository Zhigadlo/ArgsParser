#pragma once

#include <string>

namespace results
{
	class Result
	{
	public:
		Result();
		Result(std::string error);

		[[nodiscard]] bool IsSucceded();
		/**
		* @brief returns nullptr if there is no errors
		*/
		std::string& GetError();
	private:
		std::string error;
	};
}