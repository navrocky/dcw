#pragma once

#include <memory>
#include <string>

class ProcessExecutor {
public:
    void exec(const std::string& cmdLine);
};

using ProcessExecutorPtr = std::shared_ptr<ProcessExecutor>;
