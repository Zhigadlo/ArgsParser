#include "HandleResult.hpp";

namespace results
{
	Result::Result() {}
	Result::Result(std::string error) : error(error) {}

	bool Result::IsSucceded()
	{
		if (error.empty()) return true;
		
		return false;
	}

	std::string& Result::GetError()
	{
		return error;
	}
}