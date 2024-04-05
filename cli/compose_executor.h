#pragma once

#include "process_executor.h"

class ComposeExecutor {
public:
    virtual void up(const std::string& file, bool detach) = 0;
    virtual void down(const std::string& file, bool withVolumes) = 0;
};

using ComposeExecutorPtr = std::shared_ptr<ComposeExecutor>;

class ComposeExecutorImpl : public ComposeExecutor {
public:
    ComposeExecutorImpl(ProcessExecutorPtr processExecutor);

    void up(const std::string& file, bool detach);
    void down(const std::string& file, bool withVolumes);

private:
    ProcessExecutorPtr processExecutor;
    std::string composeCommand;
};
