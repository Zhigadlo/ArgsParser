#include <string>

namespace Abstractions 
{
	class Arg 
	{
	public:
		virtual void AddDescription() = 0;
		Arg(std::string shortName, std::string fullName)
		{
			this->shortName = shortName;
			this->fullName = fullName;
		}
	protected:
		std::string shortName;
		std::string fullName;
	};

}