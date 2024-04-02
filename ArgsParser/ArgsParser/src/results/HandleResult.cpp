#include "HandleResult.hpp";

namespace results
{
	HandleResult::HandleResult() {}
	HandleResult::HandleResult(std::string error) : error(error) {}

	bool HandleResult::IsSucceded()
	{
		if (error.empty()) return true;
		
		return false;
	}

	std::string& HandleResult::GetError()
	{
		return error;
	}
}