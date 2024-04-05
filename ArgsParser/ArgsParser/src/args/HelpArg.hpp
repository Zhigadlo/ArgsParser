#pragma once

#include <abstractions/Arg.hpp>

namespace args
{
    class HelpArg : public abstractions::Arg
    {
    public:
        HelpArg(char shortName, const std::vector<abstractions::Arg*>& args);
        HelpArg(std::string fullName, const std::vector<abstractions::Arg*>& args);
        HelpArg(char shortName, std::string fullName, const std::vector<abstractions::Arg*>& args);

        std::string GetInfo() override;

        results::Result Handle(const std::string& value) override;
    private:
        const std::vector<abstractions::Arg*>& allArgs;
    };
}