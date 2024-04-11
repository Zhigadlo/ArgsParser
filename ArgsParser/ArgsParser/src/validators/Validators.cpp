#include "Validators.hpp"
#include <string>
#include <sstream>
#include <vector>

namespace validators
{
	IntRangeValidator::IntRangeValidator(int minValue, int maxValue) : minValue(minValue), maxValue(maxValue) {}

	bool IntRangeValidator::Validate(int value) const
	{
		return value >= minValue && value <= maxValue;
	}

	bool PositiveIntValidator::Validate(int value) const
	{
		return value > 0;
	}

	StringLengthValidator::StringLengthValidator(unsigned int maxStringLength) : maxStringLength(maxStringLength) {}

	bool StringLengthValidator::Validate(std::string value) const
	{
		return value.length() <= maxStringLength;
	}

	IPValidator::IPValidator() {}
	bool IPValidator::Validate(std::string ip) const
	{
        std::vector<std::string> parts;
        std::istringstream iss(ip);
        std::string part;

        while (std::getline(iss, part, '.')) parts.push_back(part);
        
        if (parts.size() != 4) return false;
        
        for (const auto& part : parts)
        {
            try
            {
                unsigned int num = std::stoul(part);
                if (num > 255) return false;
            }
            catch (const std::invalid_argument&)
            {
                return false;
            }
            catch (const std::out_of_range&)
            {
                return false;
            }
        }

        return true;
	}
}