#pragma once 

namespace abstractions
{
	class IValidator
	{
	public:
		[[nodiscard]] virtual bool Validate(const void* value) const = 0;
	};
}