#pragma once

#include <args-parser/all.hpp>
#include <memory>

class BaseCommand {
public:
    virtual ~BaseCommand() { }
    virtual void reg(Args::CmdLine& cmdLine) = 0;
    virtual bool process(const Args::CmdLine& cmdLine) = 0;
};

using CommandPtr = std::shared_ptr<BaseCommand>;
