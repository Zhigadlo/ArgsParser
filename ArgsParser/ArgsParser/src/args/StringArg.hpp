#pragma once

#include <abstractions/Arg.hpp>
namespace args
{
	class StringArg : public abstractions::Arg
	{
	public:
		StringArg(char shortName, abstractions::IValidator* validator = nullptr);
		StringArg(std::string fullName, abstractions::IValidator* validator = nullptr);
		StringArg(char shortName, std::string fullName, abstractions::IValidator* validator = nullptr);

		std::string GetInfo() override;
		void SetValue(std::string value);

		results::HandleResult Handle(const std::string& value) override;
		[[nodiscard]] std::string GetValue() const;
	private:
		std::string value;
	};
}

