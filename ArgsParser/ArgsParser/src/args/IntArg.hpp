#pragma once

#include <abstractions/IValidator.hpp>
#include <abstractions/Arg.hpp>

namespace args
{
	class IntArg : public abstractions::Arg
	{
	public:
		IntArg(char shortName, abstractions::IValidator* validator = nullptr);
		IntArg(std::string fullName, abstractions::IValidator* validator = nullptr);
		IntArg(char shortName, std::string fullName, abstractions::IValidator* validator = nullptr);

		std::string GetInfo() override;
		void SetValue(int value);
		results::Result Handle(const std::string& value) override;
		[[nodiscard]] int GetValue() const;
	private:
		int value = INT_MAX;
	};
}