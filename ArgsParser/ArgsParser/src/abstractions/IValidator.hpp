#pragma once 

namespace abstractions
{
	class IValidator
	{
	public:
		virtual bool Validate(const void* value) const = 0;
	};
}