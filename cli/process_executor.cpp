#include "process_executor.h"

#include <cstdlib>
#include <format>
#include <stdexcept>

int ProcessExecutor::exec(const std::string &cmdLine)
{
    return std::system(cmdLine.c_str());
}

void ProcessExecutor::execOrThrow(const std::string& cmdLine)
{
    auto res = exec(cmdLine);
    if (res != 0)
        throw std::runtime_error(std::format("Command exited with status {}: {}", res, cmdLine));
}
