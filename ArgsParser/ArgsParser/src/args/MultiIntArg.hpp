#pragma once

#include <abstractions/Arg.hpp>

namespace args
{
	class MultiIntArg : public abstractions::Arg
	{
	public:
		MultiIntArg(char shortName, abstractions::IValidator* validator = nullptr);
		MultiIntArg(std::string fullName, abstractions::IValidator* validator = nullptr);
		MultiIntArg(char shortName, std::string fullName, abstractions::IValidator* validator = nullptr);

		std::string GetInfo() override;
		void SetValue(int value);
		
		results::HandleResult Handle(const std::string& value) override;
		[[nodiscard]] std::vector<int> GetValues() const;
	private:
		std::vector<int> values;
	};
}