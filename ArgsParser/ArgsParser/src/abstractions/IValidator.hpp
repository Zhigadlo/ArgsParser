#pragma once 

namespace abstractions
{
	class IValidator
	{
	public:
		virtual bool Validate(void* value) = 0;
	};
}