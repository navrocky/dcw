#include "process_executor.h"

#include <cstdlib>
#include <format>
#include <stdexcept>

void ProcessExecutor::exec(const std::string& cmdLine)
{
    auto res = std::system(cmdLine.c_str());
    if (res != 0)
        throw std::runtime_error(std::format("Command exited with status {}: {}", res, cmdLine));
}
