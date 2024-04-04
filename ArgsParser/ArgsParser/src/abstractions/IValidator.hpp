#pragma once 

namespace abstractions
{
	class IValidator
	{
	public:
		/**
		* @todo remake on templates
		**/
		[[nodiscard]] virtual bool Validate(const void* value) const = 0;
	};
}