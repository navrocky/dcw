#pragma once

#include <memory>
#include <string>

class ProcessExecutor {
public:
    int exec(const std::string& cmdLine);
    void execOrThrow(const std::string& cmdLine);
};

using ProcessExecutorPtr = std::shared_ptr<ProcessExecutor>;
