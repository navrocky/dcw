#pragma once

#include <CLI/App.hpp>
#include <memory>

class BaseCommand {
public:
    virtual ~BaseCommand() { }
    virtual void reg(CLI::App& app) = 0;
};

using CommandPtr = std::shared_ptr<BaseCommand>;
